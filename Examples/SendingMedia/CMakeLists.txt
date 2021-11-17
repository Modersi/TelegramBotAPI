##### Simple example of sending different types of media
add_executable(Example_SendingMedia
                  main.cpp
                  TestBot.cpp
                  TestBot.h)

set_target_properties(Example_SendingMedia
                          PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED ON)

# Linking with Qt5 #
find_package(Qt5 REQUIRED Core Network)
target_link_libraries(Example_SendingMedia
                        PRIVATE Qt5::Core
                        PRIVATE Qt5::Network)

# Linking with OpenSSL #
find_package(OpenSSL REQUIRED)			
target_link_libraries(Example_SendingMedia PRIVATE OpenSSL::SSL)

# Linking with TelegramBotAPI #
target_include_directories(Example_SendingMedia PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/include)
target_link_libraries(Example_SendingMedia PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/TelegramBotAPI.lib)