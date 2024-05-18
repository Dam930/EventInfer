#include "config/Reader.h"
#include <fstream>

namespace anomaly_detection
{
namespace config
{

nlohmann::json Reader::read_config_from_file(const std::filesystem::path& path_file)
{
    return {};
}

std::vector<Reader::ComponentElement> Reader::get_component_list()
{
    return {};
}

} // namespace config
} // namespace anomaly_detection