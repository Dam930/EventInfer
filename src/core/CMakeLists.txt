
add_library(core 
    STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/ModelContainer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationManager.cpp
)
target_include_directories(core 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
        ${OpenCV_INCLUDE_DIRS}
        ${onnxruntime_DIR}/include
        ${sobjectizer_INCLUDE_DIRS}
)
target_link_libraries(core
    components
)