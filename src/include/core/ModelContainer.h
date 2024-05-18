#include <onnxruntime_cxx_api.h>
#include <xtensor/xview.hpp>

namespace anomaly_detection {
namespace core {
class ModelContainer {
public:
  typedef enum { CPUAllocator, GPUAllocator } AllocatorType;

  ModelContainer(const std::string &modelPath, AllocatorType allocatorType);
  ~ModelContainer();

  // Get input info
  uint16_t inline get_img_w() { return m_input_shapes.at(3); }
  uint16_t inline get_img_h() { return m_input_shapes.at(2); }
  uint16_t inline get_total_elements() { return 3 * get_img_w() * get_img_h(); }

  // Function to perform inference using ONNX
  xt::xarray<float> predict(xt::xarray<float> &input);

private:
  std::shared_ptr<Ort::Env> m_env;
  std::shared_ptr<Ort::MemoryInfo> m_memory_info;
  std::unique_ptr<Ort::Session> m_session;
  std::vector<std::string> m_input_names;
  std::vector<std::int64_t> m_input_shapes;
  std::vector<std::string> m_output_names;
  std::vector<std::int64_t> m_output_shapes;
  Ort::Value m_input_tensor;
  Ort::Value m_output_tensor;
};

} // namespace core
} // namespace anomaly_detection