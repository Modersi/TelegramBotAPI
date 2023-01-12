#ifndef TELEGRAM_TYPES_INLINEKEYBOARDBUTTON_H
#define TELEGRAM_TYPES_INLINEKEYBOARDBUTTON_H

#include <compare>
#include <optional>

#include "qjsonobject.h"
#include "qstring.h"

#include "LoginURL.h"
//#include "CallbackGame.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents one button of an inline keyboard
     *
     * > You **must** use exactly one of the optional fields
     * 
     */

    struct InlineKeyboardButton
    {
        /** @brief Default constructor. Constructs an empty InlineKeyboardButton object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineKeyboardButton();

        /** @brief Constructs InlineKeyboardButton object from parameters */
        InlineKeyboardButton(const QString& text,
                             const std::optional<QString>& url = std::nullopt,
                             const std::optional<LoginURL>& login_url = std::nullopt,
                             const std::optional<QString>& callback_data = std::nullopt,
                             const std::optional<QString>& switch_inline_query = std::nullopt,
                             const std::optional<QString>& switch_inline_query_current_chat = std::nullopt,
                             //const std::optional<CallbackGame>& callback_game = std::nullopt,
                             const std::optional<bool>& pay = std::nullopt);

        /** @brief JSON constructor. Constructs InlineKeyboardButton object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InlineKeyboardButton class fields. For example it should contain pairs such as "text" = "...",
         * "url" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InlineKeyboardButton(const QJsonObject& json_object);

        /* @brief Returns InlineKeyboardButton in form of JSON object. Returns empty QJsonObject if InlineKeyboardButton is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if InlineKeyboardButton is empty */
        bool isEmpty() const;

        std::partial_ordering operator <=> (const InlineKeyboardButton&) const = default;

//** Fields **//

        /** @brief Label text on the button */
        QString text;
        
        /** @brief Optional. HTTP or tg:// url to be opened when button is pressed */
        std::optional<QString> url;
        
        /** @brief Optional. An HTTP URL used to automatically authorize the user 
         * 
         * Can be used as a replacement for the Telegram Login Widget */
        std::optional<LoginURL> login_url;
        
        /** @brief Optional. Data to be sent in a callback query to the bot when button is pressed, 1 - 64 bytes */
        std::optional<QString> callback_data;
        
        /** @brief Optional. If set, pressing the button will prompt the user to select one of their chats, open that chat and insert the bot's username and the specified inline query in the input field. Can be empty, in which case just the bot's username will be inserted
         *
         * Note: This offers an easy way for users to start using your bot in inline mode when they are currently in a private chat with it. Especially useful when combined with switch_pm… actions – in this case the user will be automatically returned to the chat they switched from, skipping the chat selection screen */
        std::optional<QString> switch_inline_query;
        
        /** @brief Optional. If set, pressing the button will insert the bot's username and the specified inline query in the current chat's input field. Can be empty, in which case only the bot's username will be inserted
         *
         *  This offers a quick way for the user to open your bot in inline mode in the same chat – good for selecting something from multiple options */
         std::optional<QString> switch_inline_query_current_chat;
        
        /** @brief Optional. Description of the game that will be launched when the user presses the button
         *
         * NOTE: This type of button must always be the first button in the first row */
        //std::optional<CallbackGame> callback_game;
        
        /** @brief Optional. Specify True, to send a Pay button
         *
         * NOTE: This type of button must always be the first button in the first row */
        std::optional<bool> pay;
    };
}

#endif // TELEGRAM_TYPES_INLINEKEYBOARDBUTTON_H
