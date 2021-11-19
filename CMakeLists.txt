cmake_minimum_required(VERSION 3.8)

project(lemon-wm)

add_executable(
    ${PROJECT_NAME}
    "src/main.cc"
    "src/display.cc"
    "src/manager.cc"
    "src/event.cc"
    "src/client.cc"
)

target_link_libraries(
    ${PROJECT_NAME}
    X11
)