##### A simple example of launching your bot
add_executable(Example_BotStartup main.cpp)

target_link_libraries(Example_BotStartup PRIVATE ${PROJECT_NAME})
get_target_property(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)
target_include_directories(Example_BotStartup PRIVATE ${${PROJECT_NAME}_INCLUDE_DIR})

target_link_libraries(Example_BotStartup PRIVATE Qt6::Core PRIVATE Qt6::Network)
target_link_libraries(Example_BotStartup PRIVATE OpenSSL::SSL)