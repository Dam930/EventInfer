#ifndef ANOMALY_DETECTION_DATACONTAINERS
#define ANOMALY_DETECTION_DATACONTAINERS

#include <opencv2/opencv.hpp>

namespace anomaly_detection {
namespace components {
struct RawFrame {
  uint64 idx;
  cv::Mat frame;
  std::chrono::system_clock::time_point frame_time;

  RawFrame(uint64 idx, const cv::Mat &frame,
           std::chrono::system_clock::time_point frame_time)
      : idx(idx), frame(frame), frame_time(frame_time) {}
};
} // namespace components
} // namespace anomaly_detection

#endif