cmake_minimum_required(VERSION 3.15)

project(Chat_Server)

set(CMAKE_CXX_STANDARD 14)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

message("LIBMONGOCXX_INCLUDE_DIRS = ${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBMONGOCXX_LIBRARIES = ${LIBMONGOCXX_LIBRARIES}")

message("LIBBSONCXX_INCLUDE_DIRS = ${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES = ${LIBBSONCXX_LIBRARIES}")


find_package(OpenSSL REQUIRED)
message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")


include_directories(${OPENSSL_INCLUDE_DIR})


file(GLOB COMMON_LIBRARIES ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES} ${OPENSSL_LIBRARIES})

add_executable(Chat_Server main.cpp Socket/Server.cpp Socket/Server.h Socket/Client.cpp Socket/Client.h Commands/Command.h Socket/Crypto.h Utils/base64.cpp Utils/base64.h)


target_include_directories(Chat_Server PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})
target_include_directories(Chat_Server PUBLIC ${LIBBSONCXX_INCLUDE_DIRS})
target_include_directories(Chat_Server PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(Chat_Server ${COMMON_LIBRARIES})
