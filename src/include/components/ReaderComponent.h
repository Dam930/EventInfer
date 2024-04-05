#ifndef ANOMALY_DETECTION_READERCOMPONENT
#define ANOMALY_DETECTION_READERCOMPONENT

#include "components/BaseComponent.h"
#include <opencv2/opencv.hpp>

namespace anomaly_detection {
namespace components {
class ReaderComponent : public BaseComponent {

public:
  using ConfigType = config::ReaderConfig;

  ReaderComponent(context_t ctx, so_5::mbox_t channel,
                  std::shared_ptr<config::ReaderConfig> config)
      : BaseComponent(ctx +
                          limit_then_drop<RawFrame>(config->max_queue_element),
                      channel, config),
        m_max_queue_element{config->max_queue_element} {};

protected:
  uint m_max_queue_element;
};
} // namespace components
} // namespace anomaly_detection

#endif