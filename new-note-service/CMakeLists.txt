cmake_minimum_required(VERSION 3.10)
project(new-note-service)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(AWSSDK REQUIRED COMPONENTS s3)

pkg_check_modules(POSTGRES REQUIRED libpqxx)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp)
pkg_check_modules(SPDLOG REQUIRED spdlog)


include_directories(${POSTGRES_INCLUDE_DIRS})
include_directories(${YAMLCPP_INCLUDE_DIRS})
include_directories("/usr/local/include/spdlog")
include_directories("/usr/local/include/cpp-httplib")
include_directories("/usr/local/include/yaml-cpp")
include_directories("/usr/local/include/cppcodec")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories("/usr/local/include")

set(SOURCES
    src/main.cpp
    src/new_note_service.cpp
    src/database.cpp
    src/yandex_object_storage.cpp
)

set(HEADERS
    include/new_note_service.hpp
    include/database.hpp
    include/yandex_object_storage.hpp
)

add_executable(new-note-service ${SOURCES} ${HEADERS})

target_link_libraries(new-note-service ${AWSSDK_LINK_LIBRARIES} ${AWSSDK_PLATFORM_DEPS})
target_link_libraries(new-note-service ${POSTGRESQL_LIBRARIES})
target_link_libraries(new-note-service pqxx pq crypto ssl spdlog yaml-cpp pthread)
