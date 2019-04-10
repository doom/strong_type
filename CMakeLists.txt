cmake_minimum_required(VERSION 3.9)

project(strong_type)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpadded -O3")

set(STRONG_TYPE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/st/is_strong_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/st/unwrap.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/st/type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/st/traits.hpp
        )

add_library(strong_type INTERFACE)

target_sources(strong_type INTERFACE ${STRONG_TYPE_SOURCES})

target_include_directories(strong_type INTERFACE include)

option(STRONG_TYPE_BUILD_TESTS "Build tests of the strong_type library" OFF)

if (STRONG_TYPE_BUILD_TESTS)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    add_executable(strong_type-tests
            tests/strong_type-tests.cpp
            )

    target_link_libraries(strong_type-tests strong_type ${CONAN_LIBS})
endif ()
