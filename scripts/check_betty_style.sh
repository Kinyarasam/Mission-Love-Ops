#!/bin/bash

# Directory to check
SRC_DIR="../src"
INCLUDE_DIR="../include"

# Initialize the result variable
RESULT=0

# Check each C file in src and include directories
for file in $(find "$SRC_DIR" "$INCLUDE_DIR" -name "*.c" -or -name "*.h"); do
    echo "Checking $file for Betty style compliance..."
    betty $file
    # Check if betty failed
    if [ $? -ne 0 ]; then
        RESULT=1
    fi
done

# Exit with status code 1 if any file failed the check
exit $RESULT
