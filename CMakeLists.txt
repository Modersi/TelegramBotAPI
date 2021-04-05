cmake_minimum_required(VERSION 3.20.0)


#################### Declaring a project ####################

project(TelegramBotAPI
        VERSION 0.0.1
        LANGUAGES CXX
        DESCRIPTION "Telegram Bot REST API realization on C++ and QT")


#################### Declaring a C++ requirements ####################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#################### Serching for all "RequestManager" files ####################

# Searching for all .cpp files #
set(${PROJECT_NAME}_RequestManagerSourceFiles
		sources/RequestManager/RequestManager.cpp)

# Searching for all .h files #
set(${PROJECT_NAME}_RequestManagerHeaderFiles 
		headers/RequestManager/RequestManager.h)

# Making variable which includes all "RequestManager" files #
set(${PROJECT_NAME}_RequestManager
		${TelegramBotAPI_RequestManagerSourceFiles}
		${TelegramBotAPI_RequestManagerHeaderFiles})


#################### Serching all "Types" files ####################

# Searching for .cpp files #
set(${PROJECT_NAME}_TypesSourceFiles
		sources/Types/Animation.cpp
		sources/Types/Audio.cpp
		sources/Types/BotCommand.cpp
		sources/Types/CallbackQuery.cpp
		sources/Types/Chat.cpp
		sources/Types/ChatMember.cpp
		sources/Types/ChatPermissions.cpp
		sources/Types/ChatPhoto.cpp
		sources/Types/Contact.cpp
		sources/Types/Dice.cpp
		sources/Types/Document.cpp
		sources/Types/File.cpp
		sources/Types/ForceReply.cpp
		sources/Types/InlineKeyboardButton.cpp
		sources/Types/InlineKeyboardMarkup.cpp
		sources/Types/InputFile.cpp
		sources/Types/InputMedia.cpp
		sources/Types/InputMediaAnimation.cpp
		sources/Types/InputMediaAudio.cpp
		sources/Types/InputMediaDocument.cpp
		sources/Types/InputMediaPhoto.cpp
		sources/Types/InputMediaVideo.cpp
		sources/Types/KeyboardButton.cpp
		sources/Types/KeyboardButtonPollType.cpp
		sources/Types/Location.cpp
		sources/Types/LoginUrl.cpp
		sources/Types/Message.cpp
		sources/Types/MessageEntity.cpp
		sources/Types/PhotoSize.cpp
		sources/Types/Poll.cpp
		sources/Types/PollAnswer.cpp
		sources/Types/PollOption.cpp
		sources/Types/ReplyKeyboardMarkup.cpp
		sources/Types/ReplyKeyboardRemove.cpp
		sources/Types/ResponseParameters.cpp
		sources/Types/Type.cpp
		sources/Types/User.cpp
		sources/Types/UserProfilePhotos.cpp
		sources/Types/Venue.cpp
		sources/Types/Video.cpp
		sources/Types/VideoNote.cpp
		sources/Types/Voice.cpp
		)

# Searching for .h files #
set(${PROJECT_NAME}_TypesHeaderFiles 
		headers/Types/Animation.h
		headers/Types/Audio.h
		headers/Types/BotCommand.h
		headers/Types/CallbackQuery.h
		headers/Types/Chat.h
		headers/Types/ChatMember.h
		headers/Types/ChatPermissions.h
		headers/Types/ChatPhoto.h
		headers/Types/Contact.h
		headers/Types/Dice.h
		headers/Types/Document.h
		headers/Types/File.h
		headers/Types/ForceReply.h
		headers/Types/InlineKeyboardButton.h
		headers/Types/InlineKeyboardMarkup.h
		headers/Types/InputFile.h
		headers/Types/InputMedia.h
		headers/Types/InputMediaAnimation.h
		headers/Types/InputMediaAudio.h
		headers/Types/InputMediaDocument.h
		headers/Types/InputMediaPhoto.h
		headers/Types/InputMediaVideo.h
		headers/Types/KeyboardButton.h
		headers/Types/KeyboardButtonPollType.h
		headers/Types/Location.h
		headers/Types/LoginUrl.h
		headers/Types/Message.h
		headers/Types/MessageEntity.h
		headers/Types/PhotoSize.h
		headers/Types/Poll.h
		headers/Types/PollAnswer.h
		headers/Types/PollOption.h
		headers/Types/ReplyKeyboardMarkup.h
		headers/Types/ReplyKeyboardRemove.h
		headers/Types/ResponseParameters.h
		headers/Types/Type.h
		headers/Types/User.h
		headers/Types/UserProfilePhotos.h
		headers/Types/Venue.h
		headers/Types/Video.h
		headers/Types/VideoNote.h
		headers/Types/Voice.h
		)

# Making variable which includes all "Types" files #
set(${PROJECT_NAME}_Types
		${${PROJECT_NAME}_TypesSourceFiles}
		${${PROJECT_NAME}_TypesHeaderFiles}
   )


#################### Putting all source files into lib ####################

add_library(${PROJECT_NAME} STATIC
				sources/TelegramBotAPI.cpp
				${${PROJECT_NAME}_RequestManagerSourceFiles}
				${${PROJECT_NAME}_TypesSourceFiles}
		   )


#################### Adding include paths to our headers ####################

target_include_directories(${PROJECT_NAME}
	                        PUBLIC ${PROJECT_SOURCE_DIR}/headers/TelegramBotAPI.h
							PUBLIC ${PROJECT_SOURCE_DIR}/${${PROJECT_NAME}_RequestManagerHeaderFiles}
							PUBLIC ${PROJECT_SOURCE_DIR}/${${PROJECT_NAME}_TypesHeaderFiles}
						  )


#################### Adding definitions to our library ####################

target_compile_definitions(${PROJECT_NAME}
                           PRIVATE TELEGRAMBOTAPI_LIBRARY)