#ifndef TELEGRAM_TYPES_MESSAGE_H
#define TELEGRAM_TYPES_MESSAGE_H

#include <compare>
#include <memory>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"

namespace Telegram { class Chat; }
#include "User.h"
#include "MessageEntity.h"
#include "Animation.h"
#include "Audio.h"
#include "Document.h"
#include "PhotoSize.h"
#include "Sticker.h"
#include "Video.h"
#include "VideoNote.h"
#include "Voice.h"
#include "Contact.h"
#include "Dice.h"
//#include "Game.h"
#include "Poll.h"
#include "Venue.h"
#include "Location.h"
#include "MessageAutoDeleteTimerChanged.h"
//#include "Invoice.h"
//#include "SuccessfulPayment.h"
//#include "PassportData.h"
#include "ProximityAlertTriggered.h"
#include "VoiceChatScheduled.h"
#include "VoiceChatStarted.h"
#include "VoiceChatEnded.h"
#include "VoiceChatParticipantsInvited.h"
#include "InlineKeyboardMarkup.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a message
     *
     */

    class Message
    {
        Q_GADGET
    
    public:

        /** @brief Default constructor. Constructs an empty Message object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Message();

        /** @brief Constructs Message object from parameters */
        Message(const qint32& message_id,
                const qint32& date,
                const std::shared_ptr<Chat>& chat,
                const std::optional<User>& from = std::nullopt,
                const std::optional<std::shared_ptr<Chat>>& sender_chat = std::nullopt,
                const std::optional<User>& forward_from = std::nullopt,
                const std::optional<std::shared_ptr<Chat>>& forward_from_chat = std::nullopt,
                const std::optional<qint32>& forward_from_message_id = std::nullopt,
                const std::optional<QString>& forward_signature = std::nullopt,
                const std::optional<QString>& forward_sender_name = std::nullopt,
                const std::optional<qint32>& forward_date = std::nullopt,
                const std::optional<std::shared_ptr<Message>>& reply_to_message = std::nullopt,
                const std::optional<User>& via_bot = std::nullopt,
                const std::optional<qint32>& edit_date = std::nullopt,
                const std::optional<QString>& media_group_id = std::nullopt,
                const std::optional<QString>& author_signature = std::nullopt,
                const std::optional<QString>& text = std::nullopt,
                const std::optional<QVector<MessageEntity>>& entities = std::nullopt,
                const std::optional<Animation>& animation = std::nullopt,
                const std::optional<Audio>& audio = std::nullopt,
                const std::optional<Document>& document = std::nullopt,
                const std::optional<QVector<PhotoSize>>& photo = std::nullopt,
                const std::optional<Sticker>& sticker = std::nullopt,
                const std::optional<Video>& video = std::nullopt,
                const std::optional<VideoNote>& video_note = std::nullopt,
                const std::optional<Voice>& voice = std::nullopt,
                const std::optional<QString>& caption = std::nullopt,
                const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                const std::optional<Contact>& contact = std::nullopt,
                const std::optional<Dice>& dice = std::nullopt,
                //const std::optional<Game>& game = std::nullopt,
                const std::optional<Poll>& poll = std::nullopt,
                const std::optional<Venue>& venue = std::nullopt,
                const std::optional<Location>& location = std::nullopt,
                const std::optional<QVector<User>>& new_chat_members = std::nullopt,
                const std::optional<User>& left_chat_member = std::nullopt,
                const std::optional<QString>& new_chat_title = std::nullopt,
                const std::optional<QVector<PhotoSize>>& new_chat_photo = std::nullopt,
                const std::optional<bool>& delete_chat_photo = std::nullopt,
                const std::optional<bool>& group_chat_created = std::nullopt,
                const std::optional<bool>& supergroup_chat_created = std::nullopt,
                const std::optional<bool>& channel_chat_created = std::nullopt,
                const std::optional<MessageAutoDeleteTimerChanged>& message_auto_delete_timer_changed = std::nullopt,
                const std::optional<qint32>& migrate_to_chat_id = std::nullopt,
                const std::optional<qint32>& migrate_from_chat_id = std::nullopt,
                const std::optional<std::shared_ptr<Message>>& pinned_message = std::nullopt,
                //const std::optional<Invoice>& invoice = std::nullopt,
                //const std::optional<SuccessfulPayment>& successful_payment = std::nullopt,
                const std::optional<QString>& connected_website = std::nullopt,
                //const std::optional<PassportData>& passport_data = std::nullopt,
                const std::optional<ProximityAlertTriggered>& proximity_alert_triggered = std::nullopt,
                const std::optional<VoiceChatScheduled>& voice_chat_scheduled = std::nullopt,
                const std::optional<VoiceChatStarted>& voice_chat_started = std::nullopt,
                const std::optional<VoiceChatEnded>& voice_chat_ended = std::nullopt,
                const std::optional<VoiceChatParticipantsInvited>& voice_chat_participants_invited = std::nullopt,
                const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);

        /** @brief JSON constructor. Constructs Message object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Message class fields. For example it should contain pairs such as "message_id" = "...",
         * "date" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Message(const QJsonObject& json_object);


        /* @brief Returns Message in form of JSON object. Returns empty QJsonObject if Message is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Message is empty */
        bool isEmpty() const;


        /** @brief Enum that represents all available types of available formatting for message */
        enum class FormattingType {
            Markdown,
            MarkdownV2,
            HTML,
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(FormattingType)

        /* @brief With this function you can get text which is prepared to sending with some formatting(ex.HTML or Markdown). Applies formatting rules on the text, and inserts message entities in the text */
        QPair<QString, QVector<Telegram::MessageEntity>> getTextWithFormatting(const FormattingType& formatting_type) const;

        /* @brief With this function you can get caption which is prepared to sending with some formatting(ex.HTML or Markdown). Applies formatting rules on the caption, and inserts caption entities in the text */
        QPair<QString, QVector<Telegram::MessageEntity>> getCaptionWithFormatting(const FormattingType& formatting_type) const;


        std::partial_ordering operator <=> (const Message& message) const = default;


//** Fields **//

        /** @brief Unique message identifier inside this chat */
        qint32 message_id;
        
        /** @brief Date the message was sent in Unix time */
        qint32 date;
        
        /** @brief Conversation the message belongs to */
        std::shared_ptr<Chat> chat;
        
        /** @brief Optional. Sender, empty for messages sent to channels */
        std::optional<User> from;
        
        /** @brief Optional. Sender of the message, sent on behalf of a chat
         *
         * The channel itself for channel messages. The supergroup itself for messages from anonymous group administrators. The linked channel for messages automatically forwarded to the discussion group */
        std::optional<std::shared_ptr<Chat>> sender_chat;
        
        /** @brief Optional. For forwarded messages, sender of the original message */
        std::optional<User> forward_from;
        
        /** @brief Optional. For messages forwarded from channels or from anonymous administrators, information about the original sender chat */
        std::optional<std::shared_ptr<Chat>> forward_from_chat;
        
        /** @brief Optional. For messages forwarded from channels, identifier of the original message in the channel */
        std::optional<qint32> forward_from_message_id;
        
        /** @brief Optional. For messages forwarded from channels, signature of the post author if present */
        std::optional<QString> forward_signature;
        
        /** @brief Optional. Sender's name for messages forwarded from users who disallow adding a link to their account in forwarded messages */
        std::optional<QString> forward_sender_name;
        
        /** @brief Optional. For forwarded messages, date the original message was sent in Unix time */
        std::optional<qint32> forward_date;
        
        /** @brief Optional. For replies, the original message
         *
         * > Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply */
        std::optional<std::shared_ptr<Message>> reply_to_message;
        
        /** @brief Optional. Bot through which the message was sent */
        std::optional<User> via_bot;
        
        /** @brief Optional. Date the message was last edited in Unix time */
        std::optional<qint32> edit_date;
        
        /** @brief Optional. The unique identifier of a media message group this message belongs to */
        std::optional<QString> media_group_id;
        
        /** @brief Optional. Signature of the post author for messages in channels, or the custom title of an anonymous group administrator */
        std::optional<QString> author_signature;
        
        /** @brief Optional. For text messages, the actual UTF-8 text of the message, 0-4096 characters */
        std::optional<QString> text;
        
        /** @brief Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text */
        std::optional<QVector<MessageEntity>> entities;
        
        /** @brief Optional. Message is an animation, information about the animation. For backward compatibility, when this field is set, the document field will also be set */
        std::optional<Animation> animation;
        
        /** @brief Optional. Message is an audio file, information about the file */
        std::optional<Audio> audio;
        
        /** @brief Optional. Message is a general file, information about the file */
        std::optional<Document> document;
        
        /** @brief 	Optional. Message is a photo, available sizes of the photo */
        std::optional<QVector<PhotoSize>> photo;
        
        /** @brief Optional. Message is a sticker, information about the sticker */
        std::optional<Sticker> sticker;
        
        /** @brief Optional. Message is a video, information about the video */
        std::optional<Video> video;
        
        /** @brief Optional. Message is a video note, information about the video message */
        std::optional<VideoNote> video_note;
        
        /** @brief Optional. Message is a voice message, information about the file */
        std::optional<Voice> voice;
        
        /** @brief Optional. Caption for the animation, audio, document, photo, video or voice, 0-1024 characters */
        std::optional<QString> caption;
        
        /** @brief Optional. For messages with a caption, special entities like usernames, URLs, bot commands, etc. that appear in the caption */
        std::optional<QVector<MessageEntity>> caption_entities;
        
        /** @brief Optional. Message is a shared contact, information about the contact */
        std::optional<Contact> contact;
        
        /** @brief Optional. Message is a dice with random value */
        std::optional<Dice> dice;
        
        /** @brief Optional. Message is a game, information about the game. [More about games](https://core.telegram.org/bots/api#games) */
        //std::optional<Game> game;
        
        /** @brief Optional. Message is a native poll, information about the poll */
        std::optional<Poll> poll;
        
        /** @brief Optional. Message is a venue, information about the venue
         *
         * For backward compatibility, when this field is set, the location field will also be set */
        std::optional<Venue> venue;
        
        /** @brief Optional. Message is a shared location, information about the location */
        std::optional<Location> location;
        
        /** @brief Optional. New members that were added to the group or supergroup and information about them (the bot itself may be one of these members) */
        std::optional<QVector<User>> new_chat_members;
        
        /** @brief Optional. A member was removed from the group, information about them (this member may be the bot itself) */
        std::optional<User> left_chat_member;
        
        /** @brief Optional. A chat title was changed to this value */
        std::optional<QString> new_chat_title;
        
        /** @brief Optional. A chat photo was change to this value */
        std::optional<QVector<PhotoSize>> new_chat_photo;

        /** @brief Optional. Service message: the chat photo was deleted */
        std::optional<bool> delete_chat_photo;
        
        /** @brief Optional. Service message: the group has been created */
        std::optional<bool> group_chat_created;
        
        /** @brief Optional. Service message: the supergroup has been created
         *
         * This field can't be received in a message coming through updates, because bot can't be a member of a supergroup when it is created. It can only be found in reply_to_message if someone replies to a very first message in a directly created supergroup */
        std::optional<bool> supergroup_chat_created;
        
        /** @brief Optional. Service message: the channel has been created
         *
         * This field can't be received in a message coming through updates, because bot can't be a member of a channel when it is created. It can only be found in reply_to_message if someone replies to a very first message in a channel */
        std::optional<bool> channel_chat_created;

        /** @brief Optional. Service message: auto-delete timer settings changed in the chat */
        std::optional<MessageAutoDeleteTimerChanged> message_auto_delete_timer_changed;
        
        /** @brief Optional. The group has been migrated to a supergroup with the specified identifier */
        std::optional<qint64> migrate_to_chat_id;
        
        /** @brief Optional. The supergroup has been migrated from a group with the specified identifier */
        std::optional<qint64> migrate_from_chat_id;
        
        /** @brief Optional. Specified message was pinned
         *
         * > Note that the Message object in this field will not contain further reply_to_message fields even if it is itself a reply */
        std::optional<std::shared_ptr<Message>> pinned_message;
        
        /** @brief Optional. Message is an invoice for a payment, information about the invoice. [More about payments](https://core.telegram.org/bots/api#payments) */
        //std::optional<Invoice> invoice;
        
        /** @brief Optional. Message is a service message about a successful payment, information about the payment. [More about payments](https://core.telegram.org/bots/api#payments) */
        //std::optional<SuccessfulPayment> successful_payment;
        
        /** @brief Optional. The domain name of the website on which the user has logged in. [More about Telegram Login](https://core.telegram.org/widgets/login) */
        std::optional<QString> connected_website;
        
        /** @brief Optional. Telegram Passport data */
        //std::optional<PassportData> passport_data;
        
        /** @brief Optional. Service message. A user in the chat triggered another user's proximity alert while sharing Live Location */
        std::optional<ProximityAlertTriggered> proximity_alert_triggered;
        
        /** @brief Optional. Service message: voice chat scheduled */
        std::optional<VoiceChatScheduled> voice_chat_scheduled;
        
        /** @brief Optional. Service message: voice chat started */
        std::optional<VoiceChatStarted> voice_chat_started;
        
        /** @brief Optional. Service message: voice chat ended */
        std::optional<VoiceChatEnded> voice_chat_ended;
        
        /** @brief Optional. Service message: new participants invited to a voice chat */
        std::optional<VoiceChatParticipantsInvited> voice_chat_participants_invited;
        
        /** @brief Optional. Inline keyboard attached to the message. *login_url* buttons are represented as ordinary *url* buttons. */
        std::optional<InlineKeyboardMarkup> reply_markup;
    };
}

#endif // TELEGRAM_TYPES_MESSAGE_H
