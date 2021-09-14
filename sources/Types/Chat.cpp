#include "Types/Chat.h"
#include "Types/Message.h"

#include "qjsonobject.h"

Telegram::Chat::Chat() :
	id(0),
	type(Type::UNINITIALIZED_VALUE),
	title(std::nullopt),
	username(std::nullopt),
	first_name(std::nullopt),
	last_name(std::nullopt),
	photo(std::nullopt),
	bio(std::nullopt),
	description(std::nullopt),
	invite_link(std::nullopt),
	pinned_message(std::nullopt),
	permissions(std::nullopt),
	slow_mode_delay(std::nullopt),
	message_auto_delete_time(std::nullopt),
	sticker_set_name(std::nullopt),
	can_set_sticker_set(std::nullopt),
	linked_chat_id(std::nullopt),
	location(std::nullopt)
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

Telegram::Chat::Chat(const QJsonObject& jsonObject)
{
	auto getChatType = [](const QJsonValue& chatType) -> Chat::Type
						{
							if (chatType == "private") return Type::PRIVATE;
							if (chatType == "group") return Type::GROUP;
							if (chatType == "supergroup") return Type::SUPERGROUP;
							if (chatType == "channel") return Type::CHANNEL;
							else return Type::UNINITIALIZED_VALUE;
						};

	jsonObject.contains("id")						? id = jsonObject["id"].toInt()														  : id = 0;
	jsonObject.contains("type")						? type = getChatType(jsonObject["type"])											  : type = Type::UNINITIALIZED_VALUE;
	jsonObject.contains("title")					? title = jsonObject["title"].toString()											  : title = std::nullopt;
	jsonObject.contains("username")					? username = jsonObject["username"].toString()										  : username = std::nullopt;
	jsonObject.contains("first_name")				? first_name = jsonObject["first_name"].toString()									  : first_name = std::nullopt;
	jsonObject.contains("last_name")				? last_name = jsonObject["last_name"].toString()									  : last_name = std::nullopt;
	jsonObject.contains("photo")					? photo = ChatPhoto(jsonObject["photo"].toObject())									  : photo = std::nullopt;
	jsonObject.contains("bio")						? bio = jsonObject["bio"].toString()												  : bio = std::nullopt;
	jsonObject.contains("description")				? description = jsonObject["description"].toString()								  : description = std::nullopt;
	jsonObject.contains("invite_link")				? invite_link = jsonObject["invite_link"].toString()								  : invite_link = std::nullopt;
	jsonObject.contains("pinned_message")			? pinned_message = std::make_shared<Message>(jsonObject["pinned_message"].toObject()) : pinned_message = std::nullopt;
	jsonObject.contains("permissions")				? permissions = ChatPermissions(jsonObject["permissions"].toObject())				  : permissions = std::nullopt;
	jsonObject.contains("slow_mode_delay")			? slow_mode_delay = jsonObject["slow_mode_delay"].toInt()							  : slow_mode_delay = std::nullopt;
	jsonObject.contains("message_auto_delete_time") ? message_auto_delete_time = jsonObject["message_auto_delete_time"].toInt()			  : message_auto_delete_time = std::nullopt;
	jsonObject.contains("sticker_set_name")			? sticker_set_name = jsonObject["sticker_set_name"].toString()						  : sticker_set_name = std::nullopt;
	jsonObject.contains("can_set_sticker_set")		? can_set_sticker_set = jsonObject["can_set_sticker_set"].toBool()					  : can_set_sticker_set = std::nullopt;
	jsonObject.contains("linked_chat_id")			? linked_chat_id = jsonObject["linked_chat_id"].toInt()								  : linked_chat_id = std::nullopt;
	jsonObject.contains("location")					? location = ChatLocation(jsonObject["location"].toObject())						  : location = std::nullopt;
}

QJsonObject Telegram::Chat::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	auto getChatType = [](const Chat::Type& chatType) -> QString
						{
							if (chatType == Type::PRIVATE) return "private";
							if (chatType == Type::GROUP) return "group";
							if (chatType == Type::SUPERGROUP) return "supergroup";
							if (chatType == Type::CHANNEL) return "channel";
							else return "";
						};

	QJsonObject chatJsonObject{ {"id", id}, {"type", getChatType(type)} };

	if (title.has_value())						chatJsonObject.insert("title", *title);
	if (username.has_value())					chatJsonObject.insert("username", *username);
	if (first_name.has_value())					chatJsonObject.insert("first_name", *first_name);
	if (last_name.has_value())					chatJsonObject.insert("last_name", *last_name);
	if (photo.has_value())						chatJsonObject.insert("photo", photo->toObject());
	if (bio.has_value())						chatJsonObject.insert("bio", *bio);
	if (description.has_value())				chatJsonObject.insert("description", *description);
	if (invite_link.has_value())				chatJsonObject.insert("invite_link", *invite_link);
	if (pinned_message.has_value())				chatJsonObject.insert("pinned_message", pinned_message.value()->toObject());
	if (permissions.has_value())				chatJsonObject.insert("permissions", permissions->toObject());
	if (slow_mode_delay.has_value())			chatJsonObject.insert("slow_mode_delay", *slow_mode_delay);
	if (message_auto_delete_time.has_value())	chatJsonObject.insert("message_auto_delete_time", *message_auto_delete_time);
	if (sticker_set_name.has_value())			chatJsonObject.insert("sticker_set_name", *sticker_set_name);
	if (can_set_sticker_set.has_value())		chatJsonObject.insert("can_set_sticker_set", *can_set_sticker_set);
	if (linked_chat_id.has_value())				chatJsonObject.insert("linked_chat_id", *linked_chat_id);
	if (location.has_value())					chatJsonObject.insert("location", location->toObject());

	return chatJsonObject;
}

bool Telegram::Chat::isEmpty() const
{
	return id == 0
		   and type == Type::UNINITIALIZED_VALUE
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
