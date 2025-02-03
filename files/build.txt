#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status

# Define colors for styling output
RED='\e[31m'
DARK_RED='\e[91m'
YELLOW='\e[33m'
GREEN='\e[32m'
RESET='\e[0m'

# Print ASCII banner in dark red
echo -e "${GREEN}"
cat << "EOF"
  _____ ____________  _____  _     _____ 
 /  __ \| ___ \ ___ \/  __ \| |   |_   _|
 | /  \/| |_/ / |_/ /| /  \/| |     | |  
 | |    |  __/|  __/ | |    | |     | |  
 | \__/\| |   | |    | \__/\| |_____| |_ 
  \____/\_|   \_|     \____/\_____/\___/ 
                                         
EOF
echo -e "${RESET}"

BUILD_DIR="build"
BIN_DIR="bin"
EXECUTABLE="main"

# Ensure the build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
    echo -e "${GREEN}Created build directory. 🎉${RESET}"
fi

# Change to the project directory (assuming the script is run from the project root)
PROJECT_DIR="$(dirname "$0")"
cd "$PROJECT_DIR" || { echo -e "${RED}Failed to change directory to project root. 💥${RESET}"; exit 1; }

# Run CMake and Make in the build directory
if cmake -S . -B "$BUILD_DIR" && make -C "$BUILD_DIR"; then
    echo -e "${GREEN}Build completed successfully. 🚀${RESET}"
else
    echo -e "${RED}Build failed. 😱${RESET}"
    exit 1
fi

# Check if the binary exists in the build directory
if [ -f "$BUILD_DIR/$EXECUTABLE" ]; then
    echo -e "${GREEN}Binary '$EXECUTABLE' successfully created. ✅${RESET}"
else
    echo -e "${RED}Binary '$EXECUTABLE' not found. Build might have failed. ⚠️${RESET}"
    exit 1
fi

# Stylish run message
echo -e "${GREEN}===============================${RESET}"
echo -e "${YELLOW}      Running the code... 🚀${RESET}"
echo -e "${GREEN}===============================${RESET}"

# Execute the binary with passed arguments from projectDir/build
"$PROJECT_DIR/$BUILD_DIR/$EXECUTABLE" "$@"

# Ensure the bin directory exists
mkdir -p "$BIN_DIR"

# Move the binary to the bin directory
if mv "$PROJECT_DIR/$BUILD_DIR/$EXECUTABLE" "$PROJECT_DIR/$BIN_DIR/"; then
    echo -e "${GREEN}Binary moved to $BIN_DIR/ 💼${RESET}"
else
    echo -e "${RED}Failed to move the binary to $BIN_DIR/ 😔${RESET}"
fi
