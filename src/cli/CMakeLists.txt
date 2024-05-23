
add_library(cli 
    STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/AnomalyDetection.cpp
)
target_include_directories(cli 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
        ${OpenCV_INCLUDE_DIRS}
        ${onnxruntime_DIR}/include
        ${sobjectizer_INCLUDE_DIRS}
)
target_link_libraries(cli
    config
)