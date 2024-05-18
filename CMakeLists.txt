cmake_minimum_required(VERSION 3.2)

#Set project name and version
project(artificialy_anomaly_detection VERSION 2.5)

#Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set the directory in which to store built libraries 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#Find required system packages
find_package(OpenCV REQUIRED )
find_package(nlohmann_json 3.10 REQUIRED)
find_package(onnxruntime REQUIRED)
find_package(xtensor REQUIRED)

find_library(onnxruntime_LIBRARY onnxruntime
    PATHS "${onnxruntime_DIR}/lib"
)

#Add subdirectories 
#Targets are specified within the subdirectories
add_executable(artificialy_anomaly_detection)
add_subdirectory(src)

# Include dirs
target_include_directories(artificialy_anomaly_detection
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${onnxruntime_DIR}/include
)

target_link_libraries(artificialy_anomaly_detection
    cli
    core
    config
)

#Export targets and package
target_link_libraries (artificialy_anomaly_detection  
                        sobjectizer::SharedLib 
                        ${OpenCV_LIBS}
                        nlohmann_json::nlohmann_json
                        ${onnxruntime_LIBRARY}
                        xtensor xtensor::optimize)
