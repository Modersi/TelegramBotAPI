##### An example of how you can send additional keyboards
add_executable(Example_AdditionalKeyboards main.cpp TestBot.h TestBot.cpp)

target_link_libraries(Example_AdditionalKeyboards PRIVATE ${PROJECT_NAME})
get_target_property(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)
target_include_directories(Example_AdditionalKeyboards PRIVATE ${${PROJECT_NAME}_INCLUDE_DIR})

target_link_libraries(Example_AdditionalKeyboards PRIVATE Qt6::Core PRIVATE Qt6::Network)
target_link_libraries(Example_AdditionalKeyboards PRIVATE OpenSSL::SSL)