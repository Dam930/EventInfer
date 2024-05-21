#include "core/ApplicationManager.h"

#include "components/RegisterComponents.h"
#include "utils/DynamicImporter.h"
#include <iostream>

namespace anomaly_detection {
namespace core {

ApplicationManager::ApplicationManager(const std::filesystem::path &config_file)
    : m_config_reader(config_file) {
  // Register components
  components::registerComponents();

  // Create env and dispatcher
  m_main_channel = m_env.environment().create_mbox("main");
  m_dispatcher = so_5::disp::active_obj::make_dispatcher(m_env.environment());

  // Get component lists
  m_config_reader.get_component_list();
}

void ApplicationManager::run_app() {
  // Create environment and launch the dispatcher
  m_env.environment().introduce_coop(
      m_dispatcher.binder(), [&](so_5::coop_t &coop) {
        nlohmann::json json_camera_reader = {};
        nlohmann::json json_feats_calculator = {
            {"max_queue_element", 6},
            {"onnx_model_path", "resnet50_v1.onnx"}};

        // Create instances
        std::unique_ptr<components::BaseComponent> agent_1 =
            utils::DynamicImporter::createInstance(
                "CameraReader", coop.environment(), m_main_channel,
                json_camera_reader);
        std::unique_ptr<components::BaseComponent> agent_2 =
            utils::DynamicImporter::createInstance(
                "PatchFeatsCalculator", coop.environment(), m_main_channel,
                json_feats_calculator);

        // Add instances
        coop.add_agent<components::BaseComponent>(std::move(agent_1));
        coop.add_agent<components::BaseComponent>(std::move(agent_2));
      });

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(4));
  }
}
} // namespace core
} // namespace anomaly_detection