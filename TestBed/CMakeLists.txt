add_executable(TestBed main.cpp TestBot.h TestBot.cpp)

target_link_libraries(TestBed PRIVATE ${PROJECT_NAME})
get_target_property(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)
target_include_directories(TestBed PRIVATE ${${PROJECT_NAME}_INCLUDE_DIR})

target_link_libraries(TestBed PRIVATE Qt6::Core PRIVATE Qt6::Network)
target_link_libraries(TestBed PRIVATE OpenSSL::SSL)


