##### Example of how to handle all incoming types of updates
add_executable(Example_IncomingMessagesHandling
                  main.cpp)

set_target_properties(Example_IncomingMessagesHandling
                          PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED ON)

# Linking with Qt5 #
find_package(Qt5 REQUIRED Core Network)
target_link_libraries(Example_IncomingMessagesHandling
                        PRIVATE Qt5::Core
                        PRIVATE Qt5::Network)

# Linking with OpenSSL #
find_package(OpenSSL REQUIRED)			
target_link_libraries(Example_IncomingMessagesHandling PRIVATE OpenSSL::SSL)

# Linking with TelegramBotAPI #
target_include_directories(Example_IncomingMessagesHandling PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/include)
target_link_libraries(Example_IncomingMessagesHandling PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/TelegramBotAPI.lib)