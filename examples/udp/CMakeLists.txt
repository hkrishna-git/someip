cmake_minimum_required(VERSION 2.8)

set(PRJ_NAME Attributes)

set(CMAKE_VERBOSE_MAKEFILE on)

#add_compile_definitions(_GLIBCXX_USE_NANOSLEEP)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -O0 -std=c++11 -D_GLIBCXX_USE_NANOSLEEP")

find_package(PkgConfig)
pkg_check_modules(DLT REQUIRED automotive-dlt)

include_directories(
      ../../capicxx-core-runtime/include
      ../../capicxx-someip-runtime/include
      ../../vsomeip/interface
      src-gen
      ${DLT_INCLUDE_DIRS}
)

link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../../capicxx-core-runtime/build
        ${CMAKE_CURRENT_SOURCE_DIR}/../../capicxx-someip-runtime/build
        ${CMAKE_CURRENT_SOURCE_DIR}/../../vsomeip/build
        ${DLT_LIBRARY_DIRS}
        ${COMMONAPI_LIBDIR}
        ${COMMONAPI_SOMEIP_CMAKE_DIR}/build
        ${Boost_LIBRARY_DIR}
)

# SOME/IP library
FILE(GLOB SOMEIP_LIB_SRCS src-gen/v1/commonapi/examples/*cpp)
# Build SOME/IP library
add_library (${PRJ_NAME}-someip SHARED ${SOMEIP_LIB_SRCS})
target_link_libraries(${PRJ_NAME}-someip CommonAPI-SomeIP)

add_executable(AttributesClient
               src/AttributesClient.cpp
               src-gen/v1/commonapi/examples/AttributesSomeIPProxy.cpp
               src-gen/v1/commonapi/examples/AttributesSomeIPDeployment.cpp
)

target_link_libraries(AttributesClient
                      CommonAPI
                      CommonAPI-SomeIP
                      vsomeip3
                      pthread
                      ${DLT_LIBRARIES}
)

add_executable(AttributesService
               src/AttributesService.cpp
               src/AttributesStubImpl.cpp
               src-gen/v1/commonapi/examples/AttributesSomeIPStubAdapter.cpp
               src-gen/v1/commonapi/examples/AttributesStubDefault.hpp
               src-gen/v1/commonapi/examples/AttributesSomeIPDeployment.cpp
)

target_link_libraries(AttributesService
                      CommonAPI
                      CommonAPI-SomeIP
                      vsomeip3
                      pthread
                      ${DLT_LIBRARIES}
)
