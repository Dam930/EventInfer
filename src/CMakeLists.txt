# Include
set(ARTIFICIALY_ARTIFICIALY_ANOMALY_INCLUDE_DIR  ${ARTIFICIALY_ARTIFICIALY_ANOMALY_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

# sub dir
add_subdirectory(cli)
add_subdirectory(utils)
add_subdirectory(components)
add_subdirectory(config)
add_subdirectory(core)

# third-parties projects
add_subdirectory(third_parties)

# Sources
set(ARTIFICIALY_ARTIFICIALY_ANOMALY_TARGETS ${ARTIFICIALY_ARTIFICIALY_ANOMALY_TARGETS} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp PARENT_SCOPE )