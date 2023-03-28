cmake_minimum_required(VERSION 3.2)

project(Mr-Database)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("\n\nThis is a ${CMAKE_SYSTEM_NAME} system\n\n")
elseif(WIN32)
    message("\n\nThis is a Windows System\n\n")
endif()

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
include_directories( include )
add_executable(${PROJECT_NAME} src/api.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Threads::Threads)

# cmake_minimum_required(VERSION 3.2)

# project(Mr-Database)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(THREADS_PREFER_PTHREAD ON)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# # UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
# if(UNIX)
#     message("\n\nThis is a ${CMAKE_SYSTEM_NAME} system\n\n")
# elseif(WIN32)
#     message("\n\nThis is a Windows System\n\n")
# endif()

# include_directories( include )
# add_executable(${PROJECT_NAME} src/api.cpp)

# find_package(Boost REQUIRED COMPONENTS filesystem)
# find_package(Threads)

# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Threads::Threads)