cmake_minimum_required(VERSION 3.10)
project (postProcess)

SET (API_INCLUDE ${PROJECT_SOURCE_DIR}/include)
SET (API_SRC_ROOT ${PROJECT_SOURCE_DIR}/src)
SET (SDK_SRC ${API_SRC_ROOT}/postProcessAPI.cpp)

include_directories(${API_INCLUDE})



add_library(postProcess SHARED ${SDK_SRC})

add_executable(main ${API_SRC_ROOT}/main.cpp ${API_SRC_ROOT}/tools.cpp)

target_link_libraries(main ${PROJECT_SOURCE_DIR}/build/libpostProcess.so)