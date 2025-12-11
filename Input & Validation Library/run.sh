#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get source file from argument or ask for it
SOURCE_FILE="$1"

if [ -z "$SOURCE_FILE" ]; then
    read -p "Enter the source file name (e.g., main.cpp): " SOURCE_FILE
    
    # If still empty, use default
    if [ -z "$SOURCE_FILE" ]; then
        SOURCE_FILE="main.cpp"
        echo -e "${YELLOW}No file specified, using default: $SOURCE_FILE${NC}"
    fi
fi

# Check if source file exists
if [ ! -f "$SOURCE_FILE" ]; then
    echo -e "${RED}Error: Source file '$SOURCE_FILE' not found!${NC}"
    exit 1
fi

# Extract filename without extension for executable name
BASE_NAME=$(basename "$SOURCE_FILE" .cpp)
EXE_NAME="$BASE_NAME"

echo -e "${YELLOW}Compiling $SOURCE_FILE...${NC}"

# Compile the C++ file
if ! g++ -o "$EXE_NAME" "$SOURCE_FILE" 2>&1; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation successful!${NC}"
echo -e "${CYAN}Running $EXE_NAME...${NC}"
echo -e "${BLUE}==================================================${NC}"

# Run the executable
./"$EXE_NAME"

echo -e "${BLUE}==================================================${NC}"
echo -e "${GREEN}Program finished.${NC}"