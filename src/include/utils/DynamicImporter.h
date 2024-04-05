#ifndef ANOMALY_DETECTION_DYNAMIC_IMPORTER
#define ANOMALY_DETECTION_DYNAMIC_IMPORTER

#include <functional>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

#include "components/BaseComponent.h"

namespace anomaly_detection {
namespace utils {
class DynamicImporter {
public:
  // Define a type alias for a function object that creates unique pointers to
  // BaseComponent objects.
  using CreatorFunctionObj =
      std::function<std::unique_ptr<components::BaseComponent>(
          so_5::agent_t::context_t, so_5::mbox_t,
          std::shared_ptr<config::BaseConfig>)>;

  // Define a type alias for a function object that creates unique pointers to
  // BaseConfig objects.
  using CreatorFunctionConf = std::function<std::unique_ptr<config::BaseConfig>(
      const nlohmann::json &)>;

  static std::unique_ptr<components::BaseComponent>
  createInstance(const std::string &className, so_5::agent_t::context_t ctx,
                 so_5::mbox_t channel, const nlohmann::json &json_config_obj) {

    // Declare a pointer to hold the configuration.
    std::unique_ptr<config::BaseConfig> config = nullptr;
    // Attempt to find the creator function for the config based on className.
    if (auto it_conf = creators_conf().find(className);
        it_conf != creators_conf().end()) {
      config = it_conf->second(json_config_obj);
    }

    if (config == nullptr)
      throw std::runtime_error("Class not correctly registered: " + className);

    // Attempt to find the creator function for the object based on className.
    if (auto it_obj = creators_obj().find(className);
        it_obj != creators_obj().end()) {
      return it_obj->second(ctx, channel, std::move(config));
    }
    throw std::runtime_error("Class not correctly registered: " + className);
  }

  template <typename T>
  static void registerClass(const std::string &className) {
    // Register creator function for Config using JSON.
    creators_conf()[className] = [](const nlohmann::json &json_config)
        -> std::unique_ptr<config::BaseConfig> {
      // Construct and return a unique pointer to a new ConfigType object.
      return std::unique_ptr<config::BaseConfig>(
          new typename T::ConfigType(json_config));
    };
    // Register creator function for the Component object.
    creators_obj()[className] = [](so_5::agent_t::context_t ctx,
                                   so_5::mbox_t channel,
                                   std::shared_ptr<config::BaseConfig> config)
        -> std::unique_ptr<components::BaseComponent> {
      // Dynamic cast the BaseConfig reference to the derived ConfigType
      // reference.
      const typename T::ConfigType &derivedConfig =
          dynamic_cast<const typename T::ConfigType &>(*config);
      return std::unique_ptr<components::BaseComponent>(
          new T(ctx, channel,
                std::make_shared<typename T::ConfigType>(derivedConfig)));
    };
  }

private:
  static std::map<std::string, CreatorFunctionObj> &creators_obj() {
    static std::map<std::string, CreatorFunctionObj> instance;
    return instance;
  }

  static std::map<std::string, CreatorFunctionConf> &creators_conf() {
    static std::map<std::string, CreatorFunctionConf> configs;
    return configs;
  }
};

} // namespace utils
} // namespace anomaly_detection

#endif