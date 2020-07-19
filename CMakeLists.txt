cmake_minimum_required(VERSION 3.5)
project(RISCV_simulator)

set(CMAKE_CXX_STANDARD 14)

# add_executable(pipeline pipeline.cpp Instruction.cpp)
# add_executable(sequential sequential.cpp Instruction.cpp)
# add_executable(oneFilePipeline oneFilePipeline.cpp Instruction.cpp)
add_executable(main main.cpp Instruction.cpp)