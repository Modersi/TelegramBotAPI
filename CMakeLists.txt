cmake_minimum_required(VERSION 3.20.0)

project(TelegramBotAPI
        VERSION 0.0.1
        LANGUAGES CXX
        DESCRIPTION "Telegram Bot API on C++ and QT")

# Setting all paths for dependencies of a project, such as Qt5_DIR or OPENSSL_ROOT_DIR #
include(${PROJECT_SOURCE_DIR}/CMake/DependeciesPaths)

set(CMAKE_AUTOMOC ON)

##### TelegramBotAPI
add_library(${PROJECT_NAME} STATIC)

target_precompile_headers(${PROJECT_NAME} PRIVATE PrecompiledHeaders)

set_target_properties(${PROJECT_NAME} 
						PROPERTIES 
							CXX_STANDARD 20
							CXX_STANDARD_REQUIRED ON
							VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Headers)
target_sources(${PROJECT_NAME}
					PUBLIC
						##### Main header
							Headers/TelegramBotAPI.h

						##### Networking
							Sources/WebhookManager.cpp
							Headers/WebhookManager.h
							Sources/RequestManager.cpp
							Headers/RequestManager.h

						##### Bot
							Sources/Bot.cpp 
							Headers/Bot.h 
							Sources/BotSettings.cpp
							Headers/BotSettings.h

						##### Types
							Sources/Types/Animation.cpp
							Headers/Types/Animation.h
							Sources/Types/Audio.cpp
							Headers/Types/Audio.h
							Sources/Types/BotCommand.cpp
							Headers/Types/BotCommand.h
							Headers/Types/BotCommandScope.h
							Headers/Types/BotCommandScopeAllChatAdministrators.h
							Headers/Types/BotCommandScopeAllGroupChats.h
							Headers/Types/BotCommandScopeAllPrivateChats.h
							Sources/Types/BotCommandScopeChat.cpp
							Headers/Types/BotCommandScopeChat.h
							Sources/Types/BotCommandScopeChatAdministrators.cpp
							Headers/Types/BotCommandScopeChatAdministrators.h
							Sources/Types/BotCommandScopeChatMember.cpp
							Headers/Types/BotCommandScopeChatMember.h
							Headers/Types/BotCommandScopeDefault.h
							Sources/Types/CallbackQuery.cpp
							Headers/Types/CallbackQuery.h
							Sources/Types/Chat.cpp
							Headers/Types/Chat.h
							Sources/Types/ChatInviteLink.cpp
							Headers/Types/ChatInviteLink.h
							Sources/Types/ChatLocation.cpp
							Headers/Types/ChatLocation.h
							Headers/Types/ChatMember.h
							Sources/Types/ChatMemberAdministrator.cpp 
							Headers/Types/ChatMemberAdministrator.h
							Sources/Types/ChatMemberBanned.cpp        
							Headers/Types/ChatMemberBanned.h       
							Sources/Types/ChatMemberLeft.cpp          
							Headers/Types/ChatMemberLeft.h         
							Sources/Types/ChatMemberMember.cpp        
							Headers/Types/ChatMemberMember.h       
							Sources/Types/ChatMemberOwner.cpp         
							Headers/Types/ChatMemberOwner.h        
							Sources/Types/ChatMemberRestricted.cpp 	  
							Headers/Types/ChatMemberRestricted.h 
							Sources/Types/ChatMemberUpdated.cpp
							Headers/Types/ChatMemberUpdated.h
							Sources/Types/ChatPermissions.cpp
							Headers/Types/ChatPermissions.h
							Sources/Types/ChatPhoto.cpp
							Headers/Types/ChatPhoto.h
							Sources/Types/ChosenInlineResult.cpp
							Headers/Types/ChosenInlineResult.h
							Sources/Types/Contact.cpp
							Headers/Types/Contact.h
							Sources/Types/Dice.cpp
							Headers/Types/Dice.h
							Sources/Types/Document.cpp
							Headers/Types/Document.h
							Sources/Types/Error.cpp
							Headers/Types/Error.h
							Sources/Types/File.cpp
							Headers/Types/File.h
							Sources/Types/ForceReply.cpp
							Headers/Types/ForceReply.h
							Sources/Types/InlineKeyboardButton.cpp
							Headers/Types/InlineKeyboardButton.h
							Sources/Types/InlineKeyboardMarkup.cpp
							Headers/Types/InlineKeyboardMarkup.h
							Sources/Types/InlineQuery.cpp
							Headers/Types/InlineQuery.h
							Headers/Types/InlineQueryResult.h
							Sources/Types/InlineQueryResultArticle.cpp
							Headers/Types/InlineQueryResultArticle.h
							Sources/Types/InlineQueryResultAudio.cpp
							Headers/Types/InlineQueryResultAudio.h
							Sources/Types/InlineQueryResultCachedAudio.cpp
							Headers/Types/InlineQueryResultCachedAudio.h
							Sources/Types/InlineQueryResultCachedDocument.cpp
							Headers/Types/InlineQueryResultCachedDocument.h
							Sources/Types/InlineQueryResultCachedGif.cpp
							Headers/Types/InlineQueryResultCachedGif.h
							Sources/Types/InlineQueryResultCachedMpeg4Gif.cpp
							Headers/Types/InlineQueryResultCachedMpeg4Gif.h
							Sources/Types/InlineQueryResultCachedPhoto.cpp
							Headers/Types/InlineQueryResultCachedPhoto.h
							Sources/Types/InlineQueryResultCachedSticker.cpp
							Headers/Types/InlineQueryResultCachedSticker.h
							Sources/Types/InlineQueryResultCachedVideo.cpp
							Headers/Types/InlineQueryResultCachedVideo.h
							Sources/Types/InlineQueryResultCachedVoice.cpp
							Headers/Types/InlineQueryResultCachedVoice.h
							Sources/Types/InlineQueryResultContact.cpp
							Headers/Types/InlineQueryResultContact.h
							Sources/Types/InlineQueryResultDocument.cpp
							Headers/Types/InlineQueryResultDocument.h
							Sources/Types/InlineQueryResultGame.cpp
							Headers/Types/InlineQueryResultGame.h
							Sources/Types/InlineQueryResultGif.cpp
							Headers/Types/InlineQueryResultGif.h
							Sources/Types/InlineQueryResultLocation.cpp
							Headers/Types/InlineQueryResultLocation.h
							Sources/Types/InlineQueryResultMpeg4Gif.cpp
							Headers/Types/InlineQueryResultMpeg4Gif.h
							Sources/Types/InlineQueryResultPhoto.cpp
							Headers/Types/InlineQueryResultPhoto.h
							Sources/Types/InlineQueryResultVenue.cpp
							Headers/Types/InlineQueryResultVenue.h
							Sources/Types/InlineQueryResultVideo.cpp
							Headers/Types/InlineQueryResultVideo.h
							Sources/Types/InlineQueryResultVoice.cpp
							Headers/Types/InlineQueryResultVoice.h
							Sources/Types/InputContactMessageContent.cpp
							Headers/Types/InputContactMessageContent.h
							Sources/Types/InputInvoiceMessageContent.cpp
							Headers/Types/InputInvoiceMessageContent.h
							Sources/Types/InputLocationMessageContent.cpp
							Headers/Types/InputLocationMessageContent.h
							Headers/Types/InputMedia.h
							Sources/Types/InputMediaAnimation.cpp
							Headers/Types/InputMediaAnimation.h
							Sources/Types/InputMediaAudio.cpp
							Headers/Types/InputMediaAudio.h
							Sources/Types/InputMediaDocument.cpp
							Headers/Types/InputMediaDocument.h
							Sources/Types/InputMediaPhoto.cpp
							Headers/Types/InputMediaPhoto.h
							Sources/Types/InputMediaVideo.cpp
							Headers/Types/InputMediaVideo.h    
							Headers/Types/InputMessageContent.h
							Sources/Types/InputTextMessageContent.cpp  
							Headers/Types/InputTextMessageContent.h
							Sources/Types/InputVenueMessageContent.cpp 
							Headers/Types/InputVenueMessageContent.h
							Sources/Types/KeyboardButton.cpp
							Headers/Types/KeyboardButton.h
							Sources/Types/KeyboardButtonPollType.cpp
							Headers/Types/KeyboardButtonPollType.h
							Sources/Types/Location.cpp
							Headers/Types/Location.h
							Sources/Types/LoginURL.cpp
							Headers/Types/LoginURL.h
							Sources/Types/MaskPosition.cpp
							Headers/Types/MaskPosition.h
							Sources/Types/Message.cpp
							Headers/Types/Message.h
							Sources/Types/MessageAutoDeleteTimerChanged.cpp
							Headers/Types/MessageAutoDeleteTimerChanged.h
							Sources/Types/MessageEntity.cpp
							Headers/Types/MessageEntity.h
							Sources/Types/MessageId.cpp
							Headers/Types/MessageId.h
							Sources/Types/PhotoSize.cpp
							Headers/Types/PhotoSize.h
							Sources/Types/Poll.cpp
							Headers/Types/Poll.h
							Sources/Types/PollAnswer.cpp
							Headers/Types/PollAnswer.h
							Sources/Types/PollOption.cpp
							Headers/Types/PollOption.h
							Sources/Types/ProximityAlertTriggered.cpp
							Headers/Types/ProximityAlertTriggered.h
							Sources/Types/ReplyKeyboardMarkup.cpp
							Headers/Types/ReplyKeyboardMarkup.h
							Sources/Types/ReplyKeyboardRemove.cpp
							Headers/Types/ReplyKeyboardRemove.h
							Sources/Types/ResponseParameters.cpp
							Headers/Types/ResponseParameters.h
							Sources/Types/Sticker.cpp
							Headers/Types/Sticker.h
							Sources/Types/StickerSet.cpp
							Headers/Types/StickerSet.h
							Sources/Types/Update.cpp
							Headers/Types/Update.h
							Sources/Types/User.cpp
							Headers/Types/User.h
							Sources/Types/UserProfilePhotos.cpp
							Headers/Types/UserProfilePhotos.h
							Sources/Types/Venue.cpp
							Headers/Types/Venue.h
							Sources/Types/Video.cpp
							Headers/Types/Video.h
							Sources/Types/VideoNote.cpp
							Headers/Types/VideoNote.h
							Sources/Types/Voice.cpp
							Headers/Types/Voice.h
							Sources/Types/VoiceChatEnded.cpp
							Headers/Types/VoiceChatEnded.h
							Sources/Types/VoiceChatParticipantsInvited.cpp
							Headers/Types/VoiceChatParticipantsInvited.h
							Sources/Types/VoiceChatScheduled.cpp
							Headers/Types/VoiceChatScheduled.h
							Sources/Types/VoiceChatStarted.cpp
							Headers/Types/VoiceChatStarted.h
							Sources/Types/WebhookInfo.cpp
							Headers/Types/WebhookInfo.h

						##### Internal
							Headers/Internal/ConversionFunctions.h)


if(TURN_ON_DEBUG_MODE)
	target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE)
endif(TURN_ON_DEBUG_MODE)

# Library (.lib, .so) destination folder #
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/Libraries/TelegramBotAPI)
# Headers (.h) destination folder #
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Headers/ DESTINATION ${CMAKE_INSTALL_PREFIX}/Headers/TelegramBotAPI)

# Linking with Qt5 #
find_package(Qt5 REQUIRED Core Network)				
target_link_libraries(${PROJECT_NAME} 
						PUBLIC Qt5::Core
						PUBLIC Qt5::Network)

# Linking with OpenSSL #
find_package(OpenSSL REQUIRED)				
target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::SSL)



