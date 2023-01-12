#include "Types/CallbackQuery.h"

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

Telegram::CallbackQuery::CallbackQuery(const QJsonObject& json_object) {
    json_object.contains("id")                ? id = json_object["id"].toString()                               : id = "";
    json_object.contains("from")              ? from = User(json_object["from"].toObject())                     : from = User();
    json_object.contains("chat_instance")     ? chat_instance = json_object["chat_instance"].toString()         : chat_instance = "";
    json_object.contains("message")           ? message = Message(json_object["message"].toObject())            : message = std::nullopt;
    json_object.contains("inline_message_id") ? inline_message_id = json_object["inline_message_id"].toString() : inline_message_id = std::nullopt;
    json_object.contains("data")              ? data = json_object["data"].toString()                           : data = std::nullopt;
    json_object.contains("game_short_name")   ? game_short_name = json_object["game_short_name"].toString()     : game_short_name = std::nullopt;
}

QJsonObject Telegram::CallbackQuery::toObject() const {
    if (isEmpty()) return {};

    QJsonObject callback_query_json_object{ {"id", id}, {"from", from.toObject()}, {"chat_instance", chat_instance} };

    if (message.has_value())			callback_query_json_object.insert("message", message->toObject());
    if (inline_message_id.has_value())	callback_query_json_object.insert("inline_message_id", *inline_message_id);
    if (data.has_value())				callback_query_json_object.insert("data", *data);
    if (game_short_name.has_value())	callback_query_json_object.insert("game_short_name", *game_short_name);

    return callback_query_json_object;
}

bool Telegram::CallbackQuery::isEmpty() const {
    return id == ""
           and from.isEmpty()
           and chat_instance == ""
           and message == std::nullopt
           and inline_message_id == std::nullopt
           and data == std::nullopt
           and game_short_name == std::nullopt;
}
