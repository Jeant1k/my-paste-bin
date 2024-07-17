cmake_minimum_required(VERSION 3.10)
project(hash-service)

set(CMAKE_CXX_STANDARD 17)

# External libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(POSTGRESQL REQUIRED libpqxx)
pkg_check_modules(REDIS REQUIRED hiredis)

include_directories(${POSTGRESQL_INCLUDE_DIRS})
include_directories(${REDIS_INCLUDE_DIRS})
include_directories(${YamlCpp_INCLUDE_DIRS})
include_directories("/usr/local/include/spdlog")
include_directories("/usr/local/include/cpp-httplib")
include_directories("/usr/local/include/redis-plus-plus")
include_directories("/usr/local/include/hiredis")
include_directories("/usr/local/include/yaml-cpp")
include_directories("/usr/local/include/cppcodec")

# Source files
set(SOURCES
    src/main.cpp
    src/hash_service.cpp
    src/database.cpp
)

# Header files
set(HEADERS
    include/hash_service.hpp
    include/database.hpp
)

add_executable(hash-service ${SOURCES} ${HEADERS})

target_link_libraries(hash-service ${POSTGRESQL_LIBRARIES})
target_link_libraries(hash-service ${REDIS_LIBRARIES})
target_link_libraries(hash-service pqxx pq crypto ssl hiredis redis++ spdlog yaml-cpp pthread)
