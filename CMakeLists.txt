cmake_minimum_required(VERSION 3.8)
project("Rasterizer")

# Enable Hot Reload for MSVC compilers if supported
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
    "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,\
    $<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,\
    $<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Include directories ===
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# === Main application (Engine) ===
add_executable(MyEngine WIN32
    "src/main.cpp"
    "include/core/MainWindow.h"
    "src/core/MainWindow.cpp"
    "src/graphics/Framebuffer.cpp"
    "include/core/Engine.h"
    "src/core/Engine.cpp"
    "include/Color.h"
    "include/maths/Vector2.h"
 "include/maths/maths.h" "include/core/FrameTimer.h" "src/core/FrameTimer.cpp" "include/maths/Vector3.h" "_testing/tests/Vector3_test.h" "include/graphics/Model.h" "src/graphics/Model.cpp" "include/graphics/Renderer.h" "src/graphics/Renderer.cpp" "include/graphics/utils/Rectangle.h")

target_include_directories(MyEngine PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/graphics
    ${CMAKE_SOURCE_DIR}/include/maths
)

# === Test executable ===
add_executable(Tests
    "_testing/TestMain.cpp"
    "_testing/TestRunner.cpp"
    "_testing/TestRunner.h"
    "_testing/tests/Vector2_test.h"
    "include/maths/Vector2.h"
 "include/maths/maths.h" "include/maths/Vector3.h" "_testing/tests/Vector3_test.h" "include/graphics/utils/Rectangle.h")

target_include_directories(Tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/maths
)

# Optional: link Tests with MyEngine to reuse some implementation code
# target_link_libraries(Tests PRIVATE MyEngine)