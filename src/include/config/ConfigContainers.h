#ifndef ANOMALY_DETECTION_CONFIGCONTAINERS
#define ANOMALY_DETECTION_CONFIGCONTAINERS

#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

namespace anomaly_detection {
namespace config {
struct BaseConfig {
  BaseConfig(const nlohmann::json &json_config_obj){};
  virtual ~BaseConfig() = default;
};

struct ReaderConfig : BaseConfig {
  uint max_queue_element;

  ReaderConfig(const nlohmann::json &json_config_obj)
      : BaseConfig(json_config_obj) {
    max_queue_element = json_config_obj["max_queue_element"];
  };
};

struct CameraReaderConfig : BaseConfig {
  CameraReaderConfig(const nlohmann::json &json_config_obj)
      : BaseConfig(json_config_obj){};
};

struct PatchFeatsCalculatorConfig : ReaderConfig {
  std::string onnx_model_path;
  PatchFeatsCalculatorConfig(const nlohmann::json &json_config_obj)
      : ReaderConfig(json_config_obj) {
    onnx_model_path = json_config_obj["onnx_model_path"];
  };
};
} // namespace config
} // namespace anomaly_detection

#endif