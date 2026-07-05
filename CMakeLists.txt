# CMakeLists.txt

# --- CMake configuration for the Dash project -------------------

cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Dash)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# --- TinyUSB ----------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    tinyusb
    GIT_REPOSITORY https://github.com/hathach/tinyusb.git
    GIT_TAG        0.17.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(tinyusb)

# Add the tinyusb library to the project
set(TINYUSB_SRC
    ${tinyusb_SOURCE_DIR}/src/tusb.c
    ${tinyusb_SOURCE_DIR}/src/common/tusb_fifo.c
    ${tinyusb_SOURCE_DIR}/src/device/usbd.c
    ${tinyusb_SOURCE_DIR}/src/device/usbd_control.c
    ${tinyusb_SOURCE_DIR}/src/class/cdc/cdc_device.c
    ${tinyusb_SOURCE_DIR}/src/class/msc/msc_device.c
    ${tinyusb_SOURCE_DIR}/src/portable/synopsys/dwc2/dcd_dwc2.c
    )

set(TINYUSB_INC
    ${tinyusb_SOURCE_DIR}/src
    ${tinyusb_SOURCE_DIR}/src/common
    ${tinyusb_SOURCE_DIR}/src/device
    ${tinyusb_SOURCE_DIR}/src/class/cdc
    ${tinyusb_SOURCE_DIR}/src/class/msc
)

# --- End TinyUSB ------------------------------------------------

# --- Project Setup ----------------------------------------------

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Source directories
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    SUFST/Src/bsp_sd_override.c
    Middlewares/TinyUSB/Src/usb_descriptors.c
    Middlewares/TinyUSB/Src/msc_diskio_bridge.c
    Middlewares/TinyUSB/Src/usb_irq.c
    Middlewares/TinyUSB/Src/usb_init.c
    ${TINYUSB_SRC}
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    SUFST/Inc
    Middlewares/TinyUSB/Inc
    ${TINYUSB_INC}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined compile definitions
    CFG_TUSB_MCU=OPT_MCU_STM32F7
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
)
