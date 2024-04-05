#define _GLIBCXX_USE_CXX11_ABI 0

#include <fstream>
#include <iostream>
#include <string>

#include "cli/AnomalyDetection.h"
#include "core/ApplicationManager.h"
#include "utils/DynamicImporter.h"

namespace anomaly_detection {

namespace cli {

void display_help() {
  std::cout << "Usage: config file" << std::endl;
  std::cout << "Arguments:" << std::endl;
  std::cout << "  config-file   : Path to the config file." << std::endl;
}

std::string elaborate_parameters(int argc, char *argv[]) {
  // Check the number of arguments
  if (argc < 2) {
    std::cerr << "You must provide arguments" << std::endl;
    display_help();
    return "";
  }

  // Extract the first argument
  std::string input_file_path = argv[1];

  // Check if help is requested
  if (input_file_path == "-h" || input_file_path == "--help") {
    display_help();
    return "";
  }

  // Check the number of arguments
  if (argc != 2) {
    std::cerr << "Error: Invalid number of arguments." << std::endl;
    display_help();
    return "";
  }

  // Extract command-line arguments
  std::string config_path = argv[1];

  return config_path;
}

int main(int argc, char *argv[]) {

  // Elaborate parameters
  std::string config_file_path = elaborate_parameters(argc, argv);

  if (config_file_path == "")
    return 0;

  // Initialize and run app
  core::ApplicationManager application_manager(config_file_path);
  application_manager.run_app();

  return 0;
}
} // namespace cli
} // namespace anomaly_detection