cmake_minimum_required (VERSION 2.8.11)

project(string_art_annealer)

include(ExternalProject)
ExternalProject_Add(simanneal_cpp
    GIT_REPOSITORY https://github.com/SergeyKrivohatskiy/simanneal_cpp.git
    TIMEOUT 10
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    DOWNLOAD_DIR 
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
ExternalProject_Get_Property (simanneal_cpp source_dir)
set(SIMANNEAL_CPP_INCLUDE_DIR ${source_dir}/simanneal_cpp)

if(WIN32)
  set(OpenCV_DIR "C:/opencv/build")
else()
  set(OpenCV_DIR "/usr/lib/opencv")
endif()
find_package(OpenCV)


file (GLOB SOURCE_FILES "*.cpp" "*.hpp")

add_executable (string_art_annealer ${SOURCE_FILES})
include_directories (${SIMANNEAL_CPP_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(string_art_annealer ${OpenCV_LIBS})
#add_dependencies (string_art_annealer simanneal_cpp)