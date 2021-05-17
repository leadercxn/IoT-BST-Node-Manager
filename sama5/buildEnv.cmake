
# set(CROSS_PATH /opt/gcc-linaro-arm-linux-gnueabihf-4.9-2014.07_linux)

# Name of C compiler.
set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
# set(CMAKE_C_COMPILER "${CROSS_PATH}/bin/arm-linux-gnueabihf-gcc")
# set(CMAKE_CXX_COMPILER "${CROSS_PATH}/bin/arm-linux-gnueabihf-g++")

# Where to look for the target environment. (More paths can be added here)
# set(CMAKE_FIND_ROOT_PATH "${CROSS_PATH}")

# Adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment only.
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search headers and libraries in the target environment only.
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
