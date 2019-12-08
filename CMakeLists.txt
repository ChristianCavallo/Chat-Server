cmake_minimum_required(VERSION 3.15)
project(Chat_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chat_Server main.cpp Socket/Server.cpp Socket/Server.h Socket/Client.cpp Socket/Client.h Commands/Command.h)