cmake_minimum_required (VERSION 3.8)
project ("SkiaPainter")

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_BUILD_TYPE"Release" CACHE STRING"" FORCE)


include_directories("C:/Users/Treecat/.jdks/corretto-16.0.2/include", "C:/Users/Treecat/.jdks/corretto-16.0.2/include/win32")
include_directories("./third/skia", "./third/v8/include")

add_executable (SkiaPainter "SkiaPainter.cpp" "canvas/CanvasContainer.h")

# add_library(SkiaPainterLib SHARED "jni.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SkiaPainter PROPERTY CXX_STANDARD 20)
endif()

target_link_directories(SkiaPainter PUBLIC "./third/skia" "./third/v8")
# target_link_directories(SkiaPainterLib PUBLIC "./third/skia" "./third/v8")


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

