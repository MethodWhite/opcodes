cmake_minimum_required(VERSION 3.14)
project(x86_opcodes VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Monolithic build: code.c includes everything via header chain
add_executable(x86_decode
    code.c
)

target_include_directories(x86_decode PRIVATE .)

option(X86_BUILD_LIB "Build static library" OFF)

if(X86_BUILD_LIB)
    add_library(x86_opcodes STATIC
        code.c
    )
    target_include_directories(x86_opcodes PUBLIC .)
endif()

option(X86_BUILD_TESTS "Build tests" ON)

if(X86_BUILD_TESTS)
    enable_testing()
    add_executable(test_opcodes
        tests/test_opcodes.c
    )
    target_include_directories(test_opcodes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME test_opcodes COMMAND test_opcodes)
endif()
