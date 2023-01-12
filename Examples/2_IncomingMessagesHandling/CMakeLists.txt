##### An example of how to handle all incoming types of updates
add_executable(Example_IncomingMessagesHandling main.cpp)

target_link_libraries(Example_IncomingMessagesHandling PRIVATE ${PROJECT_NAME})
get_target_property(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)
target_include_directories(Example_IncomingMessagesHandling PRIVATE ${${PROJECT_NAME}_INCLUDE_DIR})

target_link_libraries(Example_IncomingMessagesHandling PRIVATE Qt6::Core PRIVATE Qt6::Network)
target_link_libraries(Example_IncomingMessagesHandling PRIVATE OpenSSL::SSL)