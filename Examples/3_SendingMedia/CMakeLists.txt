##### A simple example of sending different types of media
add_executable(Example_SendingMedia main.cpp TestBot.cpp TestBot.h)

target_link_libraries(Example_SendingMedia PRIVATE ${PROJECT_NAME})
get_target_property(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)
target_include_directories(Example_SendingMedia PRIVATE ${${PROJECT_NAME}_INCLUDE_DIR})

target_link_libraries(Example_SendingMedia PRIVATE Qt6::Core PRIVATE Qt6::Network)
target_link_libraries(Example_SendingMedia PRIVATE OpenSSL::SSL)