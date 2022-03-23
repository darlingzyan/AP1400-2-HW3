cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
    src/main.cpp
    src/bst.cpp
    src/unit_test.cpp
)

target_link_libraries(main
    GTest::GTest
    GTest::Main
)

# ✅ 自动让 Visual Studio 识别 main.exe 为启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
