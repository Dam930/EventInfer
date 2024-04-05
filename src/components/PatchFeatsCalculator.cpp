#include "components/PatchFeatsCalculator.h"
#include <xtensor/xadapt.hpp>
#include <xtensor/xview.hpp>

namespace anomaly_detection {
namespace components {

void PatchFeatsCalculator::on_frame_receiver(RawFrame raw_frame) {

  // Resize the frame
  cv::Mat resizedFrame =
      resize_frame(raw_frame.frame, m_model->get_img_w(), m_model->get_img_h());
  // Convert uint8 frame to tensor data
  xt::xarray<float> input_tensor_values;
  convert_frame_to_tensor_data(resizedFrame, input_tensor_values);

  xt::xarray<float> output = m_model->predict(input_tensor_values);

  auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - raw_frame.frame_time);
  std::cout << "lett " << delay.count() << " " << m_config->max_queue_element
            << raw_frame.idx << std::endl;
}

cv::Mat PatchFeatsCalculator::resize_frame(const cv::Mat &input_frame,
                                           uint16_t img_w, uint16_t img_h) {
  cv::Mat resized_frame;
  cv::resize(input_frame, resized_frame, cv::Size(img_w, img_h),
             cv::INTER_NEAREST);
  return resized_frame;
}

void PatchFeatsCalculator::convert_frame_to_tensor_data(
    const cv::Mat &frame, xt::xarray<float> &tensor) {

  // Convert frame to normalized xarray matrix
  cv::Mat normalized_image;
  cv::cvtColor(frame, normalized_image, cv::COLOR_BGR2RGB);
  normalized_image.convertTo(normalized_image, CV_32FC3, 1.f / 255.0);
  std::vector<int> shape = {normalized_image.cols, normalized_image.rows,
                            normalized_image.channels()};
  tensor = xt::adapt(
      (float *)normalized_image.data,
      normalized_image.cols * normalized_image.rows *
          normalized_image.channels(),
      xt::no_ownership(),
      std::vector<std::size_t>{(unsigned long)normalized_image.rows,
                               (unsigned long)normalized_image.cols,
                               (unsigned long)normalized_image.channels()});
  tensor = xt::moveaxis(tensor, 2, 0);
}

void PatchFeatsCalculator::so_define_agent() {
  so_subscribe(m_channel).event(&PatchFeatsCalculator::on_frame_receiver);
}
} // namespace components
} // namespace anomaly_detection