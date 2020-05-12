cmake_minimum_required(VERSION 3.1)
project(minumu LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(minimu
    src/main.cpp
    src/text_frame_builder.cpp
)

add_library(minimu_lib
    src/minimu.cpp
    src/lsm6_imu.cpp
    src/lis3mdl_magnetometer.cpp
)
add_library(minimu::minimu_lib ALIAS minimu_lib)

target_include_directories(minimu
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
target_include_directories(minimu_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_compile_features(minimu PUBLIC cxx_std_17)
target_compile_features(minimu_lib PUBLIC cxx_std_17)

set(common_compile_options
    -Wall
    -Wextra
    -Wshadow # Warn if variable overshadows parent context
    -Wnon-virtual-dtor # Warn if class with virtual func has novirt dtor
    -Wold-style-cast # Warn for c-style casts
    -Wcast-align # Warn for potential performance problem casts
    -Wunused # Warn on anything being unused
    -Woverloaded-virtual # Warn if overload a virtual function
    -Wpedantic # Warn if non-standard C++ is used
    -Wconversion # Warn on type conversions that may lose data
    -Wsign-conversion # Warn on sign conversions
    -Wdouble-promotion # Warn if float is implicit promoted to double
)
target_compile_options(minimu PRIVATE
    ${common_compile_options}
)
target_compile_options(minimu_lib PRIVATE
    ${common_compile_options}
)

target_link_libraries(minimu minimu_lib)

# Target for generating documentation
find_package(Doxygen)
add_custom_target(minimu-docs
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
    COMMAND ${DOXYGEN_EXECUTABLE}
)
