##### Simple example launching your bot
add_executable(Example_BotStartup
                  main.cpp)

set_target_properties(Example_BotStartup
                          PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED ON)

# Linking with Qt5 #
find_package(Qt5 REQUIRED Core Network)
target_link_libraries(Example_BotStartup
                        PRIVATE Qt5::Core
                        PRIVATE Qt5::Network)

# Linking with OpenSSL #
find_package(OpenSSL REQUIRED)			
target_link_libraries(Example_BotStartup PRIVATE OpenSSL::SSL)

# Linking with TelegramBotAPI #
target_include_directories(Example_BotStartup PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/include)
target_link_libraries(Example_BotStartup PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/TelegramBotAPI.lib)