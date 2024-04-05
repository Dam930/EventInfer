#include "config/Reader.h"
#include <fstream>

namespace anomaly_detection {
namespace config {

nlohmann::json
Reader::read_config_from_file(const std::filesystem::path &path_file) {
  std::ifstream file(path_file);
  if (file.is_open()) {
    // Use nlohmann/json to load JSON from the file
    nlohmann::json json_config;
    file >> json_config;

    return json_config;
  } else {
    throw std::runtime_error("Not able to open the config file");
  }
}

std::vector<Reader::ComponentElement> Reader::get_component_list() {}

} // namespace config
} // namespace anomaly_detection