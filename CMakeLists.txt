cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(UniCString C CXX)

option(build_tests "Build testing suites." OFF)

if (MSVC)
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

    include(CheckCCompilerFlag)
    check_c_compiler_flag(-std=c11 HAVE_C11_SUPPORT)

    if (HAVE_C11_SUPPORT)
    set(CMAKE_C_FLAGS "-std=c11 ${CMAKE_C_FLAGS}")
    endif ()

    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(-std=c++11 HAVE_CXX11_SUPPORT)

    if (HAVE_CXX11_SUPPORT)
        set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    endif ()
endif ()

include(CheckIncludeFiles)
check_include_files(stdint.h HAVE_STDINT_H)

configure_file(
    ${CMAKE_SOURCE_DIR}/Config.h.in
    ${CMAKE_BINARY_DIR}/Config.h
    @ONLY
)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}
)

# Core sources
set(
    CORE_HPP
    ${CMAKE_SOURCE_DIR}/Core/Common.hpp
    ${CMAKE_SOURCE_DIR}/Core/Exception.hpp
    ${CMAKE_SOURCE_DIR}/Core/String.hpp
    ${CMAKE_SOURCE_DIR}/Core/Types.hpp
    ${CMAKE_SOURCE_DIR}/Core/Unicode.hpp
    ${CMAKE_SOURCE_DIR}/Core/Utils.hpp
    ${CMAKE_SOURCE_DIR}/Core/Codecs/UTF8.hpp
    ${CMAKE_SOURCE_DIR}/Core/Codecs/UTF16.hpp
    ${CMAKE_SOURCE_DIR}/Core/Codecs/UTF32.hpp
)
set(
    CORE_CPP
    ${CMAKE_SOURCE_DIR}/Core/Exception.cpp
    ${CMAKE_SOURCE_DIR}/Core/String.cpp
    ${CMAKE_SOURCE_DIR}/Core/Unicode.cpp
    ${CMAKE_SOURCE_DIR}/Core/Utils.cpp
    ${CMAKE_SOURCE_DIR}/Core/Codecs/UTF8.cpp
    ${CMAKE_SOURCE_DIR}/Core/Codecs/UTF16.cpp
    ${CMAKE_SOURCE_DIR}/Core/Codecs/UTF32.cpp
)

add_library(CoreUniCString STATIC ${CORE_CPP} ${CORE_HPP})

# API sources
set(
    API_H
    ${CMAKE_SOURCE_DIR}/API/UniCString/C/UniCTypes.h
    ${CMAKE_SOURCE_DIR}/API/UniCString/C/UniCError.h
    ${CMAKE_SOURCE_DIR}/API/UniCString/C/UniCString.h
    ${CMAKE_SOURCE_DIR}/API/UniCString/C/APIUtils.hpp
)
set(
    API_CPP
    ${CMAKE_SOURCE_DIR}/API/UniCString/C/UniCError.cpp
    ${CMAKE_SOURCE_DIR}/API/UniCString/C/UniCString.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/API
)

add_library(UniCString SHARED ${API_CPP} ${API_H})
target_link_libraries(UniCString CoreUniCString)

if (build_tests)
    enable_testing()

    add_executable(UnicodeTest ${CMAKE_SOURCE_DIR}/Tests/Core/UnicodeTest.cpp)
    target_link_libraries(UnicodeTest CoreUniCString)
    add_test(UnicodeTest UnicodeTest)

    add_executable(UTF8CodecTest ${CMAKE_SOURCE_DIR}/Tests/Core/UTF8CodecTest.cpp)
    target_link_libraries(UTF8CodecTest CoreUniCString)
    add_test(UTF8CodecTest UTF8CodecTest)

    add_executable(UTF16CodecTest ${CMAKE_SOURCE_DIR}/Tests/Core/UTF16CodecTest.cpp)
    target_link_libraries(UTF16CodecTest CoreUniCString)
    add_test(UTF16CodecTest UTF16CodecTest)

    add_executable(UTF32CodecTest ${CMAKE_SOURCE_DIR}/Tests/Core/UTF32CodecTest.cpp)
    target_link_libraries(UTF32CodecTest CoreUniCString)
    add_test(UTF32CodecTest UTF32CodecTest)

    add_executable(CoreStringTest ${CMAKE_SOURCE_DIR}/Tests/Core/CoreStringTest.cpp)
    target_link_libraries(CoreStringTest CoreUniCString)
    add_test(CoreStringTest CoreStringTest)

    add_executable(CAPITest ${CMAKE_SOURCE_DIR}/Tests/API/UniCString_C_Test.c)
    target_link_libraries(CAPITest UniCString)
    add_test(CAPITest CAPITest)

    add_executable(CXXAPITest ${CMAKE_SOURCE_DIR}/Tests/API/UniCString_CXX_Test.cc)
    target_link_libraries(CXXAPITest UniCString)
    add_test(CXXAPITest CXXAPITest)
endif ()

install(
    FILES ${CMAKE_SOURCE_DIR}/API/UniCString/UniCString.h
    DESTINATION include/UniCString
)

file(GLOB C_API_HEADERS ${CMAKE_SOURCE_DIR}/API/UniCString/C/*.h)
install(
    FILES ${C_API_HEADERS}
    DESTINATION include/UniCString/C
)

file(GLOB CXX_API_HEADERS ${CMAKE_SOURCE_DIR}/API/UniCString/CXX/*.hxx)
file(GLOB CXX_API_DETAILS ${CMAKE_SOURCE_DIR}/API/UniCString/CXX/*.detail)
install(
    FILES ${CXX_API_HEADERS} ${CXX_API_DETAILS}
    DESTINATION include/UniCString/CXX
)

install(TARGETS UniCString LIBRARY DESTINATION lib)
