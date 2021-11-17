
#[[
    User CMake directories:
	• CMAKE_INSTALL_INCLUDEDIR - directory for all header files for including to your project
    • CMAKE_INSTALL_LIBDIR - directory for builded libraries for including to your project

	Available build options:
	• BUILD_SHARED_LIBS - "off" if you want to build a static library(.lib, .a), "on" if you want to build a dynamic library(.dll, .so). "off" by the default
    • DEBUG_MODE - "on" if you want to see system messages with debug imformation. "off" by the default
]]
 
cmake_minimum_required(VERSION 3.20.0)

# Setting all paths for dependencies of a project, such as Qt5_DIR or OPENSSL_ROOT_DIR #
include(Dependecies.cmake)

set(CMAKE_AUTOMOC ON)

project(TelegramBotAPI
        VERSION 0.1.0
        LANGUAGES CXX
        DESCRIPTION "Telegram Bot API on C++ and QT")

 add_subdirectory(Sources)
 add_subdirectory(TestBed)
 add_subdirectory(Examples)
