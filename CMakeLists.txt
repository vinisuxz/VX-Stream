cmake_minimum_required(VERSION 3.25)
project(VXStream C)

add_executable(VXStream
    src/main.c
    src/ui.c
)

set_target_properties(VXStream PROPERTIES
    C_STANDARD 17
    C_EXTENSIONS ON
)

target_include_directories(VXStream PRIVATE include)
target_compile_options(VXStream PRIVATE -Wall -Wextra -Werror)

# XSDK turns the linked title into VXStream.xex.
xsdk_add_xex(VXStream TITLE_ID 0x56585331 NAME "VX Stream" VERSION 1.0.0.0)
