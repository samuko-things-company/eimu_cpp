cmake_minimum_required(VERSION 3.16)
project(eimu_cpp LANGUAGES CXX)



set(INCLUDE_LIB include/eimu.hpp)
add_executable(read_rpy src/read_rpy.cpp ${INCLUDE_LIB})
target_include_directories(read_rpy PUBLIC include)
target_link_libraries(read_rpy serial)

