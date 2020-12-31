################################################
# \file CmakeLists.txt
# \author Graham Riches
# \brief build for random functional programming experiments
################################################
cmake_minimum_required(VERSION 3.15.3)
project(functional)


# set the language versions
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# set MSVC compiler flags and linker flags
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")
set(MSVC_LINK_FLAGS "/DEBUG")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MSVC_LINK_FLAGS}")



# find any packages
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS}
)

# add subdirectories
add_subdirectory(source/categories)
add_subdirectory(source/types_and_functions)

