
add_library(components 
    STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CameraReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PatchFeatsCalculator.cpp
)
target_include_directories(components 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
        ${OpenCV_INCLUDE_DIRS}
        ${onnxruntime_DIR}/include
        ${sobjectizer_INCLUDE_DIRS}
)