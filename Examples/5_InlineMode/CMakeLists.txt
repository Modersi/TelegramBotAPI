##### A simple example of handling inline mode
add_executable(Example_InlineMode main.cpp)

target_link_libraries(Example_InlineMode PRIVATE ${PROJECT_NAME})
get_target_property(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)
target_include_directories(Example_InlineMode PRIVATE ${${PROJECT_NAME}_INCLUDE_DIR})

target_link_libraries(Example_InlineMode PRIVATE Qt6::Core PRIVATE Qt6::Network)
target_link_libraries(Example_InlineMode PRIVATE OpenSSL::SSL)