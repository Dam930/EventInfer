#ifndef ANOMALY_DETECTION_CAMERAREADER
#define ANOMALY_DETECTION_CAMERAREADER

#include "components/BaseComponent.h"
#include <opencv2/opencv.hpp>

namespace anomaly_detection {
namespace components {
class CameraReader : public BaseComponent {
public:
  using ConfigType = config::CameraReaderConfig;

  CameraReader(context_t ctx, so_5::mbox_t channel,
               std::shared_ptr<config::CameraReaderConfig> config)
      : BaseComponent(ctx, channel, config){};

  void so_define_agent() override;

  void so_evt_start() override;

private:
  std::unique_ptr<cv::VideoCapture> m_camera;
  bool m_stop = false;
};
} // namespace components
} // namespace anomaly_detection

#endif