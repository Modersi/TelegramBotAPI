![Logo](https://user-images.githubusercontent.com/79378703/144682250-04bcc3a1-8ac8-4173-8f23-dca6b0f0850f.png)



# QTelegramBotAPI
QTelegramBotAPI is a library for developing bots for the Telegram messenger.



# Description
Bot in Telegram is something like a built-in program that users can interact with by buttons, commands, simple text messages, etc...
You can create any bot you want! It can be a simple [weather bot](https://telegram.me/weatherman_bot?ref=thereisabotforthat.com) or a much more complicated [Bitcoin exchanger bot](https://t.me/BTC_CHANGE_BOT?start=botostore).



# Getting started
This library was made following the [official Telegram Bot API manual](https://core.telegram.org/bots/api), so you can use it as documentation for all bot methods and all data structures that the library provides. Also, every header file contains a detailed self-description, so you don't always need to look in the official documentation. 

You can find well-documented examples of the bot's abilities in the [Examples](/Examples) directory. Further, we will talk about the most important classes in QTelegramBotAPI that are used to startup and use your bot.

## _[Telegram::BotSettings](Sources/Headers/BotSettings.h)_
**Telegram::BotSettings** is a class that represents your bot settings and contains all required data to launch your bot. Used to construct Telegram::Bot, set up encryption, API key, host address, port, and more.

**BotSettings** can be constructed in 2 ways:
- Using a file with bot settings. This file should contain JSON-formatted settings of your bot. By default, [BotSettings.json](BotSettings.json) file is located in the project root directory but you can specify another directory and file name in arguments.
```c#
// Will initialize bot with settings from the file "BotSettings.json" located in the project root directory
auto settings_from_file = Telegram::BotSettings::makeFromFile();
// Will initialize the bot with settings from file "SpecificFileName.json" in "Specific/Directory"
auto settings_from_custom_file = Telegram::BotSettings::makeFromFile(QDir("Specific/File/Directory"), QStringLiteral("SpecificFileName.json"));
```
##### **BotSettings JSON object key-value pairs** :
| Key | Required | Value |
| - | - | - | 
| bot_token   | Yes | Your bot token |
| webhook_url | Optional | Your HTTPS URL for the Telegram to send updates to. Required if you use webhooks, specify your IP address if you use a self-signed certificate or specify null if you want to get updates via getUpdates()  |
| certificate_path | Optional | Path to your SSL certificate file. Required if you use webhooks withan authority-signed certificate, specify null if you want to get updates via getUpdates() or if you use self-signed certificate
| private_key_path | Optional | Path to your SSL private key file. Required if you use a webhooks, specify null if you want to get updates via getUpdates()
| ca_certificates_paths | Optional | The JSON array of paths to your SSL CA certificates files. Required if you use webhooks with an authority-signed certificate, specify null if you want to get updates via getUpdates() 
| public_key_path | Optional | Required only if you use a self-signed certificate, set to null otherwise. Path to your SSL public key. In essence public key it is your self-signed certificate
| webhook_ip_addres | Optional | The fixed IP address that will be used to send webhook requests instead of the IP address resolved through DNS
| max_connections | Optional | Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40
| allowed_updates | Optional | The JSON array with update types you want your bot to receive. For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types
| drop_pending_updates | Optional | Set "true" to drop all pending updates
| host_addres | Optional | Local IP address for webhook server to be listening for incoming connections. Defaults to "127.0.0.1"
| port | Optional | Local port for webhook server to be listening for incoming connections. Defaults to 443
| payment_token | Optional | Your payment token

- By setting its fields. Look [BotSettings.h](Sources/Headers/BotSettings.h) for all fields and their meanings
```c#
// Initializes bot settings "from code". Use this way if you need to set particular settings for your SSL configuration
auto settings_from_code = std::make_shared<Telegram::BotSettings>("BOT_TOKEN", "WEBHOOK_URL");
settings_from_code->ssl_configuration = configureSimpleSSL("Your SSL certificate file path", "Private key file path", { "CA certificate file paths" });
```
> **See [BotStartup](Examples/BotStartup/) example for the details**


## _[Telegram::Bot](Sources/Headers/Bot.h)_
**Telegram::Bot** is a class that represents your bot in Telegram. It contains all available methods such as `sendMessage()`, `sendPhoto()`, etc.. To create an instance of Telegram::Bot you have to pass Telegram::BotSettings object as an argument
```c#
auto bot_settings = Telegram::BotSettings::makeFromFile();
Telegram::Bot telegram_bot(bot_settings);
```
Also, it contains all Qt signals related to updates handling. So you can easily connect the needed signal to your function or slot. For example, there is  `Telegram::Bot::messageReceived(qint32 update_id, Message message)` signal that is emitted every time when your bot receives a text message. You can find all available signals and their description in [Bot.h](Sources/Headers/Bot.h) file
```c#
QObject::connect(&telegram_bot, &Telegram::Bot::messageReceived, [&](qint32 update_id, Telegram::Message message) { 
  telegram_bot.sendMessage(message.chat->id, message.text.value_or("")); 
});
```
> **See [IncomingMessagesHandling](Examples/IncomingMessagesHandling/) example for the details**


# Dependecies
QTelegramBotAPI is written using Qt 6.3.0 and OpenSSL 1.1.1j, so if you want to add the QTelegramBotAPI library to your project firstly you should link these libraries to your project.
```cmake
find_package(Qt6 REQUIRED Core Network)				
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core PRIVATE Qt6::Network)

find_package(OpenSSL REQUIRED)			
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)
```
After compiling your program you should deploy all necessary .dll's to the directory with your program .exe file. You can simplify this process by using [windeployqt](https://doc.qt.io/qt-6/windows-deployment.html) tool
```
cd qt_directory/6.3.0/bin/
wyndeployqt path/to/your/file.exe
```

# Linking to your project
You can easily link QTelegramBotAPI to your project with CMake by including header files located in TelegramBotAPI/include and linking with TelegramBotAPI.lib
```cmake
target_include_directories(${PROJECT_NAME} PRIVATE install/path/TelegramBotAPI/include)
target_link_libraries(${PROJECT_NAME} PRIVATE install/path/TelegramBotAPI/TelegramBotAPI.lib)
```
