# TelegramBotAPI
Telegram Bot REST API realization on C++ and QT

CMAKE_PREFIX_PATH = C:/Non-system/QT/Tools/OpenSSL/Win_x64;C:\Non-system\Qt_5.15\5.15.2\msvc2019_64\lib\cmake

To use this library u should deploy all dependecies. For example Qt5Core.dll Qt5Network.dll libcrypto.dll and another necessary dll's must be installed in directory which is contain ur project executable file.
Partically it can be done by using windeployqt tool. Windeployqt helps to deploy only Qt dependencies, but another dependencies like OpenSSL, VC++ and etc. must be done in manual mode(by ur hands)
