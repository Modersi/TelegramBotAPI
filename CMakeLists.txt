cmake_minimum_required( VERSION 3.20.0 )
##### Declaring a project

# Project data #
project( TelegramBotAPI
         VERSION 0.0.1
         LANGUAGES CXX
         DESCRIPTION "Telegram Bot REST API realization on C++ and QT" )

#? Maybe make module system ?#
# Adding Telegram Bot API library #
add_library( ${PROJECT_NAME} STATIC)

# Может удалить? #
# Adding library definition #
target_compile_definitions( ${PROJECT_NAME} PRIVATE TELEGRAMBOTAPI_LIBRARY )

# Setting library destination folder #
install( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/Libraries )

# Setting project C++ requirements #
set_target_properties( ${PROJECT_NAME} 
						PROPERTIES
							CMAKE_CXX_STANDARD 20
							CMAKE_CXX_STANDARD_REQUIRED ON )


##### Library files

# Including all header files #
target_include_directories( ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Headers )

#? Set privtae and public headers ?# 
# Putting all headers in build destination folder #
install( DIRECTORY ${PROJECT_SOURCE_DIR}/Headers/ DESTINATION ${CMAKE_INSTALL_PREFIX}/Headers )

# Variable which contain all game source files directories #
set( ${PROJECT_NAME}_SourceFiles

		# Telegram Bot API main header #
		Sources/TelegramBotAPI.cpp

		# Request Manager #
		Sources/RequestManager/RequestManager.cpp

		# Types #
		Sources/Types/Animation.cpp
		Sources/Types/Audio.cpp
		Sources/Types/BotCommand.cpp
		Sources/Types/CallbackQuery.cpp
		Sources/Types/Chat.cpp
		Sources/Types/ChatMember.cpp
		Sources/Types/ChatPermissions.cpp
		Sources/Types/ChatPhoto.cpp
		Sources/Types/Contact.cpp
		Sources/Types/Dice.cpp
		Sources/Types/Document.cpp
		Sources/Types/File.cpp
		Sources/Types/ForceReply.cpp
		Sources/Types/InlineKeyboardButton.cpp
		Sources/Types/InlineKeyboardMarkup.cpp
		Sources/Types/InputFile.cpp
		Sources/Types/InputMedia.cpp
		Sources/Types/InputMediaAnimation.cpp
		Sources/Types/InputMediaAudio.cpp
		Sources/Types/InputMediaDocument.cpp
		Sources/Types/InputMediaPhoto.cpp
		Sources/Types/InputMediaVideo.cpp
		Sources/Types/KeyboardButton.cpp
		Sources/Types/KeyboardButtonPollType.cpp
		Sources/Types/Location.cpp
		Sources/Types/LoginUrl.cpp
		Sources/Types/Message.cpp
		Sources/Types/MessageEntity.cpp
		Sources/Types/PhotoSize.cpp
		Sources/Types/Poll.cpp
		Sources/Types/PollAnswer.cpp
		Sources/Types/PollOption.cpp
		Sources/Types/ReplyKeyboardMarkup.cpp
		Sources/Types/ReplyKeyboardRemove.cpp
		Sources/Types/ResponseParameters.cpp
		Sources/Types/Type.cpp
		Sources/Types/User.cpp
		Sources/Types/UserProfilePhotos.cpp
		Sources/Types/Venue.cpp
		Sources/Types/Video.cpp
		Sources/Types/VideoNote.cpp
		Sources/Types/Voice.cpp )

# Setting source files for our library #
target_sources( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SourceFiles} )

##### QT

# Searching for QT5 package files (in directory of Qt5_DIR variable) #
find_package( Qt5 
				COMPONENTS 
					Core REQUIRED #? Раздупрлить этот ебанный REQUIRED ?#
					Network REQUIRED )

#find_package(Qt5 COMPONENTS Core Network REQUIRED)

# Link our library with QT #					
target_link_libraries( ${PROJECT_NAME} 
						PRIVATE Qt5::Core
						PRIVATE Qt5::Network )


##### OpenSSL

# Searching for OpenSSL package files (in directory of OPENSSL_ROOT_DIR variable) #
find_package(OpenSSL REQUIRED )

# Link our library with OpenSSL #					
target_link_libraries( ${PROJECT_NAME} 
						PRIVATE 
							OpenSSL::SSL )

