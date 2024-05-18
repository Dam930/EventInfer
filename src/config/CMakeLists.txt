
add_library(config 
    STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/Reader.cpp
)
target_include_directories(config 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
        ${OpenCV_INCLUDE_DIRS}
        ${onnxruntime_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/third_parties/sobjectizer/dev
)