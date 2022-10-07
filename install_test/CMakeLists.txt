cmake_minimum_required(VERSION 3.20)
project(install_test)

set(CMAKE_CXX_STANDARD 14)

######################################################################################

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "D:\\opencv\\mingw-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(install_test main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(install_test ${OpenCV_LIBS})

######################################################################################





