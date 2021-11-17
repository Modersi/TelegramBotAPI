##### TelegramBotAPI testing application
add_executable(TestBed
                  main.cpp 
                  TestBot.h 
                  TestBot.cpp)

set_target_properties(TestBed
                          PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED ON)


# Linking with Qt5 #
find_package(Qt5 REQUIRED Core Network)
target_link_libraries(TestBed
                        PRIVATE Qt5::Core
                        PRIVATE Qt5::Network)

# Linking with OpenSSL #
find_package(OpenSSL REQUIRED)			
target_link_libraries(TestBed PRIVATE OpenSSL::SSL)

# Linking with TelegramBotAPI #
target_include_directories(TestBed PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/include)
target_link_libraries(TestBed PRIVATE ${PROJECT_SOURCE_DIR}/CompiledBinaries/Windows/x64/Static/TelegramBotAPI.lib)


