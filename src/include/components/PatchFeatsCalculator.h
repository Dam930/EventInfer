#ifndef ANOMALY_DETECTION_PATCHFEATSCALCULATOR
#define ANOMALY_DETECTION_PATCHFEATSCALCULATOR

#include "components/ReaderComponent.h"
#include "core/ModelContainer.h"
#include <opencv2/opencv.hpp>

namespace anomaly_detection {
namespace components {
class PatchFeatsCalculator : public ReaderComponent {

public:
  using ConfigType = config::PatchFeatsCalculatorConfig;

  PatchFeatsCalculator(
      context_t ctx, so_5::mbox_t channel,
      std::shared_ptr<config::PatchFeatsCalculatorConfig> config)
      : ReaderComponent(ctx, channel, config) {
    m_config = config;
    // Initialize the model
    m_model = std::make_unique<core::ModelContainer>(
        m_config->onnx_model_path,
        core::ModelContainer::AllocatorType::CPUAllocator);
  };

  void so_define_agent() override;

private:
  void on_frame_receiver(RawFrame raw_frame);
  static cv::Mat resize_frame(const cv::Mat &input_frame, uint16_t img_w,
                              uint16_t img_h);
  void convert_frame_to_tensor_data(const cv::Mat &frame,
                                    xt::xarray<float> &tensor);
  std::shared_ptr<config::PatchFeatsCalculatorConfig> m_config;
  std::unique_ptr<core::ModelContainer> m_model;
};
} // namespace components
} // namespace anomaly_detection

#endif