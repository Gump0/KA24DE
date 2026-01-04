# always run relative to scripts location (placed in project root)
#!/usr/bin/env bash
set -e

BUILD_DIR="build"
EXECUTABLE_NAME="KA24DE"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

cmake -B "$BUILD_DIR"        # run linker
cmake --build "$BUILD_DIR"  # run compiler

cmake --build "$BUILD_DIR"

echo "Running $EXECUTABLE_NAME.."
"./$BUILD_DIR/$EXECUTABLE_NAME"
