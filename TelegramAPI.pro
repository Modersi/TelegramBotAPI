QT -= gui
QT += network

TEMPLATE = lib
DEFINES += TELEGRAMAPI_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RequestManager.cpp \
    TelegramAPI.cpp \
    Types/Animation.cpp \
    Types/Audio.cpp \
    Types/BotCommand.cpp \
    Types/CallbackQuery.cpp \
    Types/Chat.cpp \
    Types/ChatMember.cpp \
    Types/ChatPermissions.cpp \
    Types/ChatPhoto.cpp \
    Types/Contact.cpp \
    Types/Dice.cpp \
    Types/Document.cpp \
    Types/File.cpp \
    Types/ForceReply.cpp \
    Types/InlineKeyboardButton.cpp \
    Types/InlineKeyboardMarkup.cpp \
    Types/InputFile.cpp \
    Types/InputMedia.cpp \
    Types/InputMediaAnimation.cpp \
    Types/InputMediaAudio.cpp \
    Types/InputMediaDocument.cpp \
    Types/InputMediaPhoto.cpp \
    Types/InputMediaVideo.cpp \
    Types/KeyboardButton.cpp \
    Types/KeyboardButtonPollType.cpp \
    Types/Location.cpp \
    Types/LoginUrl.cpp \
    Types/Message.cpp \
    Types/MessageEntity.cpp \
    Types/PhotoSize.cpp \
    Types/Poll.cpp \
    Types/PollAnswer.cpp \
    Types/PollOption.cpp \
    Types/ReplyKeyboardMarkup.cpp \
    Types/ReplyKeyboardRemove.cpp \
    Types/ResponseParameters.cpp \
    Types/Type.cpp \
    Types/User.cpp \
    Types/UserProfilePhotos.cpp \
    Types/Venue.cpp \
    Types/Video.cpp \
    Types/VideoNote.cpp \
    Types/Voice.cpp

HEADERS += \
    RequestManager.h \
    TelegramAPI_global.h \
    TelegramAPI.h \
    Types/Animation.h \
    Types/Audio.h \
    Types/BotCommand.h \
    Types/CallbackQuery.h \
    Types/Chat.h \
    Types/ChatMember.h \
    Types/ChatPermissions.h \
    Types/ChatPhoto.h \
    Types/Contact.h \
    Types/Dice.h \
    Types/Document.h \
    Types/File.h \
    Types/ForceReply.h \
    Types/InlineKeyboardButton.h \
    Types/InlineKeyboardMarkup.h \
    Types/InputFile.h \
    Types/InputMedia.h \
    Types/InputMediaAnimation.h \
    Types/InputMediaAudio.h \
    Types/InputMediaDocument.h \
    Types/InputMediaPhoto.h \
    Types/InputMediaVideo.h \
    Types/KeyboardButton.h \
    Types/KeyboardButtonPollType.h \
    Types/Location.h \
    Types/LoginUrl.h \
    Types/Message.h \
    Types/MessageEntity.h \
    Types/PhotoSize.h \
    Types/Poll.h \
    Types/PollAnswer.h \
    Types/PollOption.h \
    Types/ReplyKeyboardMarkup.h \
    Types/ReplyKeyboardRemove.h \
    Types/ResponseParameters.h \
    Types/Type.h \
    Types/User.h \
    Types/UserProfilePhotos.h \
    Types/Venue.h \
    Types/Video.h \
    Types/VideoNote.h \
    Types/Voice.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
