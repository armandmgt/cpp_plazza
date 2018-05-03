cmake_minimum_required(VERSION 3.6)

project(plazzaui)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(include)
#add_subdirectory(srcs)
add_subdirectory(gui)
add_subdirectory(tests)