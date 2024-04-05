#ifndef ANOMALY_DETECTION_APP_MANAGER
#define ANOMALY_DETECTION_APP_MANAGER

#include "components/BaseComponent.h"
#include "config/Reader.h"
#include <memory>
#include <vector>

namespace anomaly_detection {
namespace core {
class ApplicationManager {
public:
  ApplicationManager(const std::filesystem::path &config_file);
  void run_app();

private:
  typedef std::unique_ptr<components::BaseComponent> ComponentRef;

  const so_5::wrapped_env_t m_env;
  so_5::mbox_t m_main_channel;
  so_5::disp::active_obj::dispatcher_handle_t m_dispatcher;

  config::Reader m_config_reader;
};

} // namespace core
} // namespace anomaly_detection

#endif