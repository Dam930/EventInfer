#include "core/ModelContainer.h"
#include <chrono>
#include <iostream>
#include <xtensor/xadapt.hpp>

namespace anomaly_detection {
namespace core {

ModelContainer::ModelContainer(const std::string &modelPath,
                               AllocatorType allocatorType)
    : m_input_tensor(nullptr), m_output_tensor(nullptr) {
  // Initialize ONNX runtime environment
  m_env = std::make_shared<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "ONNX_Model");

  Ort::SessionOptions sf;
  switch (allocatorType) {
  case CPUAllocator:
    m_memory_info = std::make_shared<Ort::MemoryInfo>(
        Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault));
    break;
  case GPUAllocator:
    throw std::runtime_error("Cuda allocator is not available");
    break;
  }

  // Load the ONNX model
  m_session =
      std::make_unique<Ort::Session>(*m_env.get(), modelPath.c_str(), sf);

  // Define the names
  Ort::AllocatorWithDefaultOptions allocator;
  m_input_names.emplace_back(
      m_session->GetInputNameAllocated(0, allocator).get());
  m_input_shapes =
      m_session->GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
  m_output_names.emplace_back(
      m_session->GetOutputNameAllocated(0, allocator).get());
  m_output_shapes =
      m_session->GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
}

ModelContainer::~ModelContainer() {}

xt::xarray<float> ModelContainer::predict(xt::xarray<float> &input) {
  auto start = std::chrono::system_clock::now();

  // Define input tensor
  m_input_tensor = Ort::Value::CreateTensor<float>(
      *m_memory_info, static_cast<float *>(input.data()), input.size(),
      m_input_shapes.data(), m_input_shapes.size());
  auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start);
  std::cout << "start1 " << delay.count() << std::endl;
  // Define parameters
  Ort::RunOptions run_options;
  Ort::AllocatorWithDefaultOptions allocator;
  std::vector<const char *> input_names_char(m_input_names.size(), nullptr);
  std::transform(std::begin(m_input_names), std::end(m_input_names),
                 std::begin(input_names_char),
                 [&](const std::string &str) { return str.c_str(); });

  std::vector<const char *> output_names_char(m_output_names.size(), nullptr);
  std::transform(std::begin(m_output_names), std::end(m_output_names),
                 std::begin(output_names_char),
                 [&](const std::string &str) { return str.c_str(); });
  auto delay2 = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start);
  std::cout << "start2 " << delay2.count() << std::endl;
  // Run session
  m_session->Run(run_options, input_names_char.data(), &m_input_tensor, 1,
                 output_names_char.data(), &m_output_tensor, 1);

  auto delay3 = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start);
  std::cout << "start3 " << delay3.count() << std::endl;

  const float *float_data = m_output_tensor.GetTensorMutableData<float>();
  Ort::TensorTypeAndShapeInfo info =
      m_output_tensor.GetTensorTypeAndShapeInfo();
  const std::vector<int64_t> int64_shape = info.GetShape();
  std::vector<size_t> shape;
  for (const int64_t &dim : int64_shape)
    shape.push_back(static_cast<size_t>(dim));

  auto delay4 = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start);
  std::cout << "start4 " << delay4.count() << std::endl;
  // Create an xarray<float>
  xt::xarray<float> output =
      xt::adapt(float_data, info.GetElementCount(), xt::no_ownership(), shape);
  auto delay5 = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start);
  std::cout << "start5 " << delay5.count() << std::endl;
  return output;
}

} // namespace core
} // namespace anomaly_detection