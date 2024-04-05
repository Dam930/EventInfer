#ifndef ANOMALY_DETECTION_BASE_COMPONENT
#define ANOMALY_DETECTION_BASE_COMPONENT

#include <so_5/all.hpp>

#include "components/DataContainers.h"
#include "config/ConfigContainers.h"

namespace anomaly_detection {
namespace components {
class BaseComponent : public so_5::agent_t {
public:
  using ConfigType = config::BaseConfig;

  BaseComponent(context_t ctx, so_5::mbox_t channel,
                std::shared_ptr<config::BaseConfig> config)
      : so_5::agent_t{std::move(ctx)}, m_channel{std::move(channel)} {}
  virtual ~BaseComponent(){};

protected:
  std::thread m_thread;
  const so_5::mbox_t m_channel;
};

} // namespace components
} // namespace anomaly_detection

#endif