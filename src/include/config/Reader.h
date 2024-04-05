#ifndef ANOMALY_DETECTION_CONFIG_READER
#define ANOMALY_DETECTION_CONFIG_READER
#include "config/ConfigContainers.h"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace anomaly_detection {
namespace config {
class Reader {
public:
  struct ComponentElement {
    std::string component_name;
    nlohmann::json config;
    ComponentElement(std::string component_name, nlohmann::json config)
        : component_name(component_name), config(config){};
  };

  Reader(const std::filesystem::path &file_path) {
    m_root_config = file_path.parent_path();
    m_config = read_config_from_file(m_root_config);
  }

  std::vector<ComponentElement> get_component_list();

private:
  nlohmann::json read_config_from_file(const std::filesystem::path &path_file);

  std::filesystem::path m_root_config;
  nlohmann::json m_config;
};

} // namespace config
} // namespace anomaly_detection

#endif