cmake_minimum_required(VERSION 3.13)
project("service")

find_package(PostgreSQL REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cpphttp/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soci/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/jwt-cpp/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cpphttp/src/request.cpp")

add_executable(classroom ${SOURCES})

set_target_properties(classroom PROPERTIES CXX_STANDARD 20)

target_link_libraries(classroom 
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soci/lib/libsoci_postgresql.a
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soci/lib/libsoci_core.a
  ${PostgreSQL_LIBRARIES}
  ${OPENSSL_LIBRARIES}
)

set_property(TARGET classroom PROPERTY CXX_STANDARD 20)