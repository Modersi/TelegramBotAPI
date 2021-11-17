#include "Types/CallbackQuery.h"

#include "qjsonobject.h"

Telegram::CallbackQuery::CallbackQuery() : 
    id(),
    from(),
    chat_instance(),
    message(),
    inline_message_id(),
    data(),
    game_short_name()
{}

Telegram::CallbackQuery::CallbackQuery(const QString& id,
                                       const User& from,
                                       const QString& chat_instance,
                                       const std::optional<Message>& message,
                                       const std::optional<QString>& inline_message_id,
                                       const std::optional<QString>& data,
                                       const std::optional<QString>& game_short_name) :
    id(id),
    from(from),
    chat_instance(chat_instance),
    message(message),
    inline_message_id(inline_message_id),
    data(data),
    game_short_name(game_short_name)
{}

Telegram::CallbackQuery::CallbackQuery(const QJsonObject& jsonObject)
{
    jsonObject.contains("id")                ? id = jsonObject["id"].toString()                               : id = "";
    jsonObject.contains("from")              ? from = User(jsonObject["from"].toObject())                     : from = User();
    jsonObject.contains("chat_instance")     ? chat_instance = jsonObject["chat_instance"].toString()         : chat_instance = "";
    jsonObject.contains("message")           ? message = Message(jsonObject["message"].toObject())            : message = std::nullopt;
    jsonObject.contains("inline_message_id") ? inline_message_id = jsonObject["inline_message_id"].toString() : inline_message_id = std::nullopt;
    jsonObject.contains("data")              ? data = jsonObject["data"].toString()                           : data = std::nullopt;
    jsonObject.contains("game_short_name")   ? game_short_name = jsonObject["game_short_name"].toString()     : game_short_name = std::nullopt;
}

QJsonObject Telegram::CallbackQuery::toObject() const
{
    if (isEmpty())
        return QJsonObject();

    QJsonObject callBackQueryJsonObject{ {"id", id}, {"from", from.toObject()}, {"chat_instance", chat_instance} };

    if (message.has_value())			callBackQueryJsonObject.insert("message", message->toObject());
    if (inline_message_id.has_value())	callBackQueryJsonObject.insert("inline_message_id", *inline_message_id);
    if (data.has_value())				callBackQueryJsonObject.insert("data", *data);
    if (game_short_name.has_value())	callBackQueryJsonObject.insert("game_short_name", *game_short_name);

    return callBackQueryJsonObject;
}

bool Telegram::CallbackQuery::isEmpty() const
{
    return id == ""
           and from.isEmpty()
           and chat_instance == ""
           and message == std::nullopt
           and inline_message_id == std::nullopt
           and data == std::nullopt
           and game_short_name == std::nullopt;
}
