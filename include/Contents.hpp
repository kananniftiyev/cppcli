#ifndef CONTENTS_HPP_
#define CONTENTS_HPP_

#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::string> contents(std::string PROJECT_NAME)
{
    std::unordered_map<std::string, std::string> contents;

    std::string cmakeContent = "cmake_minimum_required(VERSION 3.0.0)\n"
                               "project(" +
                               PROJECT_NAME + " VERSION 0.1.0)\n\n"
                                              "set(CMAKE_CXX_STANDARD 20)\n\n"
                                              "# Print the CMAKE_PREFIX_PATH for debugging\n"
                                              "message(STATUS \"CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}\")\n\n"
                                              "# Include directories\n"
                                              "include_directories(${PROJECT_SOURCE_DIR}/include)\n"
                                              "include_directories(${PROJECT_SOURCE_DIR}/lib)\n"
                                              "# Use file(GLOB ...) to gather all source files in the src directory\n"
                                              "file(GLOB TARGET_SRC \"${PROJECT_SOURCE_DIR}/src/*.cpp\")\n\n"
                                              "# Create the main executable from the source files\n"
                                              "add_executable(main ${TARGET_SRC})\n\n"
                                              "target_link_libraries(main)\n\n"
                                              "# CPack configuration\n"
                                              "set(CPACK_PROJECT_NAME ${PROJECT_NAME})\n"
                                              "set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})\n"
                                              "include(CPack)\n";

    std::string mainContent = "#include <iostream>\n\n"
                              "int main() {\n"
                              "    std::cout << \"Hello, " +
                              PROJECT_NAME + "!\" << std::endl;\n"
                                             "    return 0;\n"
                                             "}\n";
    std::string readmeContent = "# " + PROJECT_NAME + "\n\n"
                                                      "This is a C++ project template.\n\n"
                                                      "## Build Instructions\n\n"
                                                      "To build the project, run the following commands:\n\n"
                                                      "```bash\n"
                                                      "mkdir build\n"
                                                      "cd build\n"
                                                      "cmake ..\n"
                                                      "make\n"
                                                      "```\n";
    std::string ignoreContent = "# Build directory\n"
                                "build/\n\n"
                                "# CMake files\n"
                                "CMakeCache.txt\n"
                                "CMakeFiles/\n\n"
                                "# Executable\n" +
                                PROJECT_NAME + "\n";
    std::string buildContent = R"(
					#!/bin/bash
					# Change to the build directory
					cd build || { echo "Failed to change directory to build"; exit 1; }
					# Run CMake
					cmake .. || { echo "CMake configuration failed"; exit 1; }
					# Build the project
					make || { echo "Build failed"; exit 1; }
					# Check if the binary was created
					if [ -f "./main" ]; then
					    echo "Binary 'main' successfully created."
					else
					    echo "Binary 'main' not found. Build might have failed."
					    exit 1;
					fi
					# Notify that the build is complete
					echo -e "\e[31mBuilt the project\e[0m"
					# Display a stylish running message
					echo -e "${GREEN}==============================="
					echo -e "${YELLOW}      Running the code..."
					echo -e "${GREEN}===============================${RESET}"
					# Run the main executable with any arguments passed to the script
					./main "$@"
					# Create bin directory if it doesn't exist
					mkdir -p ../bin
					# Move the binary to the bin directory
					if mv ./main ../bin; then
					    echo "Binary moved to ../bin"
					else
					    echo "Failed to move the binary to ../bin"
					fi
					)";

    contents["cmake"] = cmakeContent;
    contents["build"] = buildContent;
    contents["ignore"] = ignoreContent;
    contents["readme"] = readmeContent;
    contents["main"] = mainContent;

    return contents;
}

#endif // CONTENTS_HPP_
