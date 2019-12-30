cmake_minimum_required(VERSION 3.15)

project(Chat_Server)
find_package(rapidjson REQUIRED)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

message("LIBMONGOCXX_INCLUDE_DIRS = ${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBMONGOCXX_LIBRARIES = ${LIBMONGOCXX_LIBRARIES}")

message("LIBBSONCXX_INCLUDE_DIRS = ${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES = ${LIBBSONCXX_LIBRARIES}")


find_package(OpenSSL REQUIRED)
message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")

add_executable(Chat_Server main.cpp Socket/Server.cpp Socket/Server.h Socket/Client.cpp Socket/Client.h Commands/Command.h Socket/Security/Crypto.h Utils/base64.cpp Utils/base64.h Database/mongodb.cpp Database/mongodb.h Socket/Security/Crypto.cpp core/Dispatcher.cpp core/Dispatcher.h
        Primitives/User.h Primitives/User.cpp Database/MediaManager.h Database/MediaManager.cpp Managers/Users_Manager.h Managers/Users_Manager.cpp Utils/util.h Managers/Chat_Manager.cpp Managers/Chat_Manager.h Primitives/Chat.cpp Primitives/Chat.h Primitives/Message.cpp Primitives/Message.h)

target_include_directories(Chat_Server PUBLIC ${LIBBSONCXX_INCLUDE_DIRS})
target_include_directories(Chat_Server PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(Chat_Server ${LIBMONGOCXX_LIBRARIES} ${OPENSSL_LIBRARIES})
