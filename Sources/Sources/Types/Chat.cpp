#include "Types/Chat.h"
#include "Types/Message.h"

Telegram::Chat::Chat() :
	id(),
	type(),
	title(),
	username(),
	first_name(),
	last_name(),
	photo(),
	bio(),
	description(),
	invite_link(),
	pinned_message(),
	permissions(),
	slow_mode_delay(),
	message_auto_delete_time(),
	sticker_set_name(),
	can_set_sticker_set(),
	linked_chat_id(),
	location()
{}

Telegram::Chat::Chat(const qint64& id,
	                 const Type& type,
	                 const std::optional<QString>& title,
	                 const std::optional<QString>& username,
	                 const std::optional<QString>& first_name,
	                 const std::optional<QString>& last_name,
	                 const std::optional<ChatPhoto>& photo,
	                 const std::optional<QString>& bio,
	                 const std::optional<QString>& description,
	                 const std::optional<QString>& invite_link,
	                 const std::optional<std::shared_ptr<Message>>& pinned_message,
	                 const std::optional<ChatPermissions>& permissions,
	                 const std::optional<qint32>& slow_mode_delay,
	                 const std::optional<qint32>& message_auto_delete_time,
	                 const std::optional<QString>& sticker_set_name,
	                 const std::optional<bool>& can_set_sticker_set,
	                 const std::optional<qint64>& linked_chat_id,
	                 const std::optional<ChatLocation>& location) :
	id(id),
	type(type),
	title(title),
	username(username),
	first_name(first_name),
	last_name(last_name),
	photo(photo),
	bio(bio),
	description(description),
	invite_link(invite_link),
	pinned_message(pinned_message),
	permissions(permissions),
	slow_mode_delay(slow_mode_delay),
	message_auto_delete_time(message_auto_delete_time),
	sticker_set_name(sticker_set_name),
	can_set_sticker_set(can_set_sticker_set),
	linked_chat_id(linked_chat_id),
	location(location)
{}

Telegram::Chat::Chat(const QJsonObject& json_object) {
	json_object.contains("id")						 ? id = json_object["id"].toInteger()													: id = 0;
	json_object.contains("title")					 ? title = json_object["title"].toString()												: title = std::nullopt;
	json_object.contains("username")				 ? username = json_object["username"].toString()										: username = std::nullopt;
	json_object.contains("first_name")				 ? first_name = json_object["first_name"].toString()									: first_name = std::nullopt;
	json_object.contains("last_name")				 ? last_name = json_object["last_name"].toString()										: last_name = std::nullopt;
	json_object.contains("photo")					 ? photo = ChatPhoto(json_object["photo"].toObject())									: photo = std::nullopt;
	json_object.contains("bio")						 ? bio = json_object["bio"].toString()													: bio = std::nullopt;
	json_object.contains("description")				 ? description = json_object["description"].toString()									: description = std::nullopt;
	json_object.contains("invite_link")				 ? invite_link = json_object["invite_link"].toString()									: invite_link = std::nullopt;
	json_object.contains("pinned_message")			 ? pinned_message = std::make_shared<Message>(json_object["pinned_message"].toObject()) : pinned_message = std::nullopt;
	json_object.contains("permissions")				 ? permissions = ChatPermissions(json_object["permissions"].toObject())					: permissions = std::nullopt;
	json_object.contains("slow_mode_delay")			 ? slow_mode_delay = json_object["slow_mode_delay"].toInt()								: slow_mode_delay = std::nullopt;
	json_object.contains("message_auto_delete_time") ? message_auto_delete_time = json_object["message_auto_delete_time"].toInt()			: message_auto_delete_time = std::nullopt;
	json_object.contains("sticker_set_name")		 ? sticker_set_name = json_object["sticker_set_name"].toString()						: sticker_set_name = std::nullopt;
	json_object.contains("can_set_sticker_set")		 ? can_set_sticker_set = json_object["can_set_sticker_set"].toBool()					: can_set_sticker_set = std::nullopt;
	json_object.contains("linked_chat_id")			 ? linked_chat_id = json_object["linked_chat_id"].toInteger()							: linked_chat_id = std::nullopt;
	json_object.contains("location")				 ? location = ChatLocation(json_object["location"].toObject())							: location = std::nullopt;
	json_object.contains("type")					 ? type = static_cast<decltype(type)>(QMetaEnum::fromType<decltype(type)>().keyToValue(json_object["type"].toString().toUpper().toUtf8())) : type = decltype(type)::NULL_ENUMERATOR;
}

QJsonObject Telegram::Chat::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chat_json_object{ {"id", id}, {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()} };

	if (title.has_value())						chat_json_object.insert("title", *title);
	if (username.has_value())					chat_json_object.insert("username", *username);
	if (first_name.has_value())					chat_json_object.insert("first_name", *first_name);
	if (last_name.has_value())					chat_json_object.insert("last_name", *last_name);
	if (photo.has_value())						chat_json_object.insert("photo", photo->toObject());
	if (bio.has_value())						chat_json_object.insert("bio", *bio);
	if (description.has_value())				chat_json_object.insert("description", *description);
	if (invite_link.has_value())				chat_json_object.insert("invite_link", *invite_link);
	if (pinned_message.has_value())				chat_json_object.insert("pinned_message", pinned_message.value()->toObject());
	if (permissions.has_value())				chat_json_object.insert("permissions", permissions->toObject());
	if (slow_mode_delay.has_value())			chat_json_object.insert("slow_mode_delay", *slow_mode_delay);
	if (message_auto_delete_time.has_value())	chat_json_object.insert("message_auto_delete_time", *message_auto_delete_time);
	if (sticker_set_name.has_value())			chat_json_object.insert("sticker_set_name", *sticker_set_name);
	if (can_set_sticker_set.has_value())		chat_json_object.insert("can_set_sticker_set", *can_set_sticker_set);
	if (linked_chat_id.has_value())				chat_json_object.insert("linked_chat_id", *linked_chat_id);
	if (location.has_value())					chat_json_object.insert("location", location->toObject());

	return chat_json_object;
}

bool Telegram::Chat::isEmpty() const
{
	return id == 0
		   and type == decltype(type)::NULL_ENUMERATOR
		   and title == std::nullopt
		   and username == std::nullopt
		   and first_name == std::nullopt
		   and last_name == std::nullopt
		   and photo == std::nullopt
		   and bio == std::nullopt
		   and description == std::nullopt
		   and invite_link == std::nullopt
		   and pinned_message == std::nullopt
		   and permissions == std::nullopt
		   and slow_mode_delay == std::nullopt
		   and message_auto_delete_time == std::nullopt
		   and sticker_set_name == std::nullopt
		   and can_set_sticker_set == std::nullopt
		   and linked_chat_id == std::nullopt
		   and location == std::nullopt;
}
