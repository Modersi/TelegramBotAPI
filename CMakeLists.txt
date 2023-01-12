cmake_minimum_required(VERSION 3.20.0)


project(TelegramBotAPI
        VERSION 1.0.0
        LANGUAGES CXX
        DESCRIPTION "Telegram Bot API on C++ and Qt6")

option(BUILD_EXAMPLES "Set \"on\" to build projects with library usage examples" OFF)
option(BUILD_TESTBED "Set \"on\" to build simple test bot project" OFF)


include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Network)		
find_package(OpenSSL REQUIRED)				


add_subdirectory(Sources)

if(BUILD_TESTBED)
    add_subdirectory(TestBed)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()