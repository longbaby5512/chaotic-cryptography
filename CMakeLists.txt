cmake_minimum_required(VERSION 3.0.0)
project(Chaotic VERSION 0.1.0)

add_library(ChaoticCypher STATIC src/ChaoticCypher.cpp src/ChaoticMap.cpp src/Utils.cpp src/Hash.cpp src/AES.cpp src/LFSR.cpp)

target_include_directories(ChaoticCypher PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(Chaotic main.cpp)

target_include_directories(Chaotic PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(Chaotic ChaoticCypher)

