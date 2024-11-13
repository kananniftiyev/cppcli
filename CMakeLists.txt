cmake_minimum_required(VERSION 3.0.0)
project(project_name VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(fmt REQUIRED)

# Use file(GLOB ...) to gather all source files in the src directory
file(GLOB TARGET_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the main executable from the source files
add_executable(main ${TARGET_SRC})

# Link with libgit2
target_link_libraries(main PRIVATE fmt::fmt)

# CPack configuration
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
