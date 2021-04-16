#ifndef MESSAGE_H
#define MESSAGE_H

#include "Types/Type.h"
#include "Types/Chat.h"
#include "Types/User.h"

class Message : public Type
{
public:
    Message();

    Message(qint32               messageId,
            qint32               date,
            Chat                 chat,
            User                 from = User(),
            Chat                 forwardFromChat = Chat(),
            User                 forwardFrom = User(),
            qint32               forwardFromMessageId = 0,
            QString              forwardSignature = "",
            QString              forwardSenderName = "",
            qint32               forwardDate = 0,
            Message              replyToMessage = Message(),
            User                 viaBot = User(),
            qint32               editDate = 0,
            QString              mediaGroupId = "",
            QString              authorSignature = "",
            QString              text = "",
            //MessageEntity        entities[] = new MessageEntity(),
            //Animation            animation = Animation(),
            //Audio                audio = Audio(),
            //Document             document = Document(),
            //PhotoSize            photo[] = new PhotoSize(),
            //Sticker              sticker = Sticker(),
            //Video                video = Video(),
            //VideoNote            videoNote = VideoNote(),
            //Voice                voice = Voice(),
            QString              caption = "",
            //MessageEntity        captionEntities[] = new MessageEntity(),
            //Contact              contact = Contact(),
            //Dice                 dice = Dice(),
            //Game                 game = Game(),
            //Poll                 poll = Poll(),
            //Venue                venue = Venue(),
            //Location             location = Location(),
            QVector<User>        newChatMembers = QVector<User>(),
            User                 leftChatMember = User(),
            QString              newChatTitle = "",
            //PhotoSize            newChatPhoto[] = new PhotoSize(),
            bool                 deleteChatPhoto = false,
            bool                 groupChatCreated = false,
            bool                 supergroupChatCreated = false,
            bool                 channelChatCreated = false,
            qint64               migrateToChatId = 0,
            qint64               migrateFromChatId = 0,
            Message              pinnedMessage = Message(),
            //Invoice              invoice = Invoice(),
            //SuccessfulPayment    successfulPayment = SuccessfulPayment(),
            //PassportData         passportData = PassportData(),
            //InlineKeyboardMarkup replyMarkup = InlineKeyboardMarkup(),
            QString              connectedWebsite =  ""
            );

    Message(QJsonObject jsonObject);

    qint32       messageId();
    void         setMessageId(qint32 messageId);

    qint32       date();
    void         setDate(qint32 date);

    Chat         chat();
    void         setChat(Chat chat);

    User         from();
    void         setFrom(User from);
    bool         hasFrom();

    Chat         forwardFromChat();
    void         setForwardFromChat(Chat forwardFromChat);
    bool         hasForwardFromChat();

    User         forwardFrom();
    void         setForwardFrom(User forwardFrom);
    bool         hasForwardFrom();

    qint32       forwardFromMessageId();
    void         setForwardFromMessageId(qint32 forwardFromMessageId);
    bool         hasForwardFromMessageId();

    QString      forwardSignature();
    void         setForwardSignature(QString forwardSignature);
    bool         hasForwardSignature();

    QString      forwardSenderName();
    void         setForwardSenderName(QString forwardSenderName);
    bool         hasForwardSenderName();

    qint32       forwardDate();
    void         setForwardDate(qint32 forwardDate);
    bool         hasForwardDate();

    Message      replyToMessage();
    void         setReplyToMessage(Message replyToMessage);
    bool         hasReplyToMessage();

    User         viaBot();
    void         setViaBot(User viaBot);
    bool         hasViaBot();

    qint32       editDate();
    void         setEditDate(qint32 editDate);
    bool         hasEditDate();

    QString      mediaGroupId();
    void         setMediaGroupId(QString mediaGroupId);
    bool         hasMediaGroupId();

    QString      authorSignature();
    void         setAuthorSignature(QString authorSignature);
    bool         hasAuthorSignature();

    QString      text();
    void         setText(QString text);
    bool         hasText();

    //inline MessageEntity    entities() { return MessageEntity(_jsonObject.value("entities").toObject()); }
    //inline void             setEntities(MessageEntity entities[]) { _jsonObject.value("entities") = QJsonArray(entities); }

    //inline Animation    animation() { return Animation(_jsonObject.value("animation").toObject()); }
    //inline void         setAnimation(Animation animation) { _jsonObject.value("animation") = animation.toObject(); }
    //
    //inline Document     document() { return document(_jsonObject.value("document").toObject()); }
    //inline void         setDocument(Document document) { _jsonObject.value("document") = document.toObject(); }
    //
    //inline Audio        audio() { return Audio(_jsonObject.value("audio").toObject()); }
    //inline void         setAudio(Audio audio) { _jsonObject.value("audio") = audio.toObject(); }
    //
    //inline PhotoSize    photo() { return PhotoSize(_jsonObject.value("photo").toObject()); }
    //inline void         setPhoto(PhotoSize photo) { _jsonObject.value("photo") = photo.toObject(); }
    //
    //inline Sticker      sticker() { return Sticker(_jsonObject.value("sticker").toObject()); }
    //inline void         setSticker(Sticker sticker) { _jsonObject.value("sticker") = sticker.toObject(); }
    //
    //inline Video        video() { return Video(_jsonObject.value("video").toObject()); }
    //inline void         setVideo(Video video) { _jsonObject.value("video") = video.toObject(); }
    //
    //inline VideoNote    videoNote() { return VideoNote(_jsonObject.value("video_note").toObject()); }
    //inline void         setVideoNote(VideoNote videoNote) { _jsonObject.value("video_note") = videoNote.toObject(); }
    //
    //inline Voice        voice() { return Voice(_jsonObject.value("voice").toObject()); }
    //inline void         setVoice(Voice voice) { _jsonObject.value("voice") = voice.toObject(); }

    QString      caption();
    void         setCaption(QString caption);
    bool         hasCaption();

    //inline MessageEntity    captionEntities() { return MessageEntity(_jsonObject.value("caption_entities").toObject()); }
    //inline void             setСaptionEntities(MessageEntity captionEntities) { _jsonObject.value("caption_entities") = captionEntities.toObject(); }
    //
    //inline Contact      contact() { return Contact(_jsonObject.value("contact").toObject()); }
    //inline void         setContact(Contact contact) { _jsonObject.value("contact") = contact.toObject(); }
    //
    //inline Dice         dice() { return Dice(_jsonObject.value("dice").toObject()); }
    //inline void         setDice(Dice dice) { _jsonObject.value("dice") = dice.toObject(); }
    //
    //inline Game         sticker() { return Game(_jsonObject.value("game").toObject()); }
    //inline void         setGame(Game game) { _jsonObject.value("game") = game.toObject(); }
    //
    //inline Poll         poll() { return Poll(_jsonObject.value("poll").toObject()); }
    //inline void         setPoll(Poll poll) { _jsonObject.value("poll") = poll.toObject(); }
    //
    //inline Venue        venue() { return Venue(_jsonObject.value("venue").toObject()); }
    //inline void         setVenue(Venue venue) { _jsonObject.value("venue") = venue.toObject(); }
    //
    //inline Location     location() { return Location(_jsonObject.value("location").toObject()); }
    //inline void         setLocation(Location location) { _jsonObject.value("location") = location.toObject(); }

    QVector<User>   newChatMembers();
    void            setNewChatMembers(QVector<User> newChatMembers);
    bool            hasNewChatMembers();

    User         leftChatMember();
    void         setLeftChatMember(User leftChatMember);
    bool         hasLeftChatMember();

    QString      newChatTitle();
    void         setNewChatTitle(QString newChatTitle);
    bool         hasNewChatTitle();

    //inline QList<PhotoSize>   newChatPhoto() { return Type::toQList(_jsonObject.value("new_chat_photo").toArray(), PhotoShize()); }
    //inline void               setNewChatPhoto(QList<PhotoSize> newChatPhoto) { _jsonObject.value("new_chat_photo") = Type::toArray(newChatPhoto); }

    bool         chatPhotoDeleted();
    void         setChatPhotoDeleted(bool deleteChatPhoto);
    bool         hasChatPhotoDeleted();

    bool         groupChatCreated();
    void         setGroupChatCreated(bool groupChatCreated);
    bool         hasGroupChatCreated();

    bool         supergroupChatCreated();
    void         setSupergroupChatCreated(bool supergroupChatCreated);
    bool         hasSupergroupChatCreated();

    bool         channelChatCreated();
    void         setChannelChatCreated(bool channelChatCreated);
    bool         hasChannelChatCreated();

    qint64       migrateToChatId();
    void         setMigrateToChatId(qint64 migrateToChatId);
    bool         hasMigrateToChatId();

    qint64       migrateFromChatId();
    void         setMigrateFromChatId(qint64 migrateFromChatId);
    bool         hasMigrateFromChatId();

    Message      pinnedMessage();
    void         setPinnedMessage(Message pinnedMessage);
    bool         hasPinnedMessage();

    //inline Invoice      invoice() { return Invoice(_jsonObject.value("invoice").toObject()); }
    //inline void         setInvoice(Invoice invoice) { _jsonObject.value("invoice") = invoice.toObject(); }
    //
    //inline SuccessfulPayment    successfulPayment() { return SuccessfulPayment(_jsonObject.value("successful_payment").toObject()); }
    //inline void                 setSuccessfulPayment(SuccessfulPayment successfulPayment) { _jsonObject.value("successful_payment") = successfulPayment.toObject(); }
    //
    //inline PassportData     passportData() { return PassportData(_jsonObject.value("passport_data").toObject()); }
    //inline void             setPassportData(PassportData passportData) { _jsonObject.value("passport_data") = passportData.toObject(); }
    //
    //inline InlineKeyboardMarkup     replyMarkup() { return InlineKeyboardMarkup(_jsonObject.value("reply_markup").toObject()); }
    //inline void                     setReplyMarkup(InlineKeyboardMarkup replyMarkup) { _jsonObject.value("reply_markup") = replyMarkup.toObject(); }

    QString      connectedWebsite();
    void         setConnectedWebsite(QString connectedWebsite);
    bool         hasConnectedWebsite();
};

#endif // MESSAGE_H
