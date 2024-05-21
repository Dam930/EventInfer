#include "components/CameraReader.h"

namespace anomaly_detection {
namespace components {

void CameraReader::so_define_agent() {
  // Open the camera
  m_camera = std::make_unique<cv::VideoCapture>(cv::VideoCapture(0));
  m_camera->set(cv::CAP_PROP_FPS, 1);

  // Check if the camera is open
  if (!m_camera->isOpened()) {
    throw std::runtime_error("Not able to open camera " + std::string(0));
  }
}

void CameraReader::so_evt_start() {
  uint64 idx = 0;

  while (!m_stop) {
    cv::Mat frame;

    // Read the frame
    *m_camera >> frame;
    std::chrono::system_clock::time_point creation_time =
        std::chrono::system_clock::now();

    if (frame.empty()) {
      std::cerr << "Frame not captured" << std::endl;
    }

    RawFrame raw_frame(idx, frame, creation_time);

    // Send to threads
    so_5::send<RawFrame>(m_channel, raw_frame);

    std::time_t currentTime_t =
        std::chrono::system_clock::to_time_t(creation_time);

    std::cout << "image "
              << " " << idx << " " << std::ctime(&currentTime_t);
    idx++;
  }
}

} // namespace components
} // namespace anomaly_detection