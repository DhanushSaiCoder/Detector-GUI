# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

# Define the project name and language
project(Detector-GUI LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the OpenCV library on your system
find_package(OpenCV REQUIRED)

# Add your executable target, pointing to the correct source file
add_executable(detector_app src/webcam.cpp)

# Link the OpenCV libraries to your executable
target_link_libraries(detector_app PRIVATE ${OpenCV_LIBS})
