#ifndef ANOMALY_DETECTION_REGISTER
#define ANOMALY_DETECTION_REGISTER

#include "components/CameraReader.h"
#include "components/PatchFeatsCalculator.h"
#include "utils/DynamicImporter.h"
#include <so_5/all.hpp>

namespace anomaly_detection {
namespace components {

void registerComponents() {
  utils::DynamicImporter::registerClass<CameraReader>("CameraReader");
  utils::DynamicImporter::registerClass<PatchFeatsCalculator>(
      "PatchFeatsCalculator");
}
} // namespace components
} // namespace anomaly_detection

#endif