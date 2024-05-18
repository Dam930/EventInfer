# sub dir
add_subdirectory(cli)
add_subdirectory(utils)
add_subdirectory(components)
add_subdirectory(config)
add_subdirectory(core)

# third-parties projects
add_subdirectory(third_parties)

target_sources(artificialy_anomaly_detection
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(artificialy_anomaly_detection
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_parties/sobjectizer/dev
)
