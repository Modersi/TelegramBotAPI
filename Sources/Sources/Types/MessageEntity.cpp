#include "Types/MessageEntity.h"

Telegram::MessageEntity::MessageEntity() :
	type(),
	offset(),
	length(),
	url(),
	user(),
	language()
{
}

Telegram::MessageEntity::MessageEntity(const Type& type,
									   const qint32& offset,
									   const qint32& length,
									   const std::optional<QString>& url,
									   const std::optional<User>& user,
									   const std::optional<QString>& language) :
	type(type),
	offset(offset),
	length(length),
	url(url),
	user(user),
	language(language)
{
}

Telegram::MessageEntity::MessageEntity(const QJsonObject& json_object) {
	json_object.contains("type")	 ? type = static_cast<decltype(type)>(QMetaEnum::fromType<decltype(type)>().keyToValue(json_object["type"].toString().toUpper().toUtf8())) : type = decltype(type)::NULL_ENUMERATOR;
	json_object.contains("offset")	 ? offset = json_object["offset"].toInt()																								   : offset = 0;
	json_object.contains("length")	 ? length = json_object["length"].toInt()																								   : length = 0;
	json_object.contains("url")		 ? url = json_object["url"].toString()																									   : url = std::nullopt;
	json_object.contains("user")	 ? user = User(json_object["user"].toObject())																							   : user = std::nullopt;
	json_object.contains("language") ? language = json_object["language"].toString()																						   : language = std::nullopt;
}

QJsonObject Telegram::MessageEntity::toObject() const {
	if(isEmpty()) return {};

	QJsonObject message_entity_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"offset", offset}, {"length", length}};

	if (url.has_value())		message_entity_json_object.insert("url", *url);
	if (user.has_value())		message_entity_json_object.insert("user", user->toObject());
	if (language.has_value())	message_entity_json_object.insert("language", *language);

	return message_entity_json_object;
}

bool Telegram::MessageEntity::isEmpty() const {
	return type == decltype(type)::NULL_ENUMERATOR
		   and offset == 0 
		   and length == 0 
		   and url == std::nullopt
		   and user == std::nullopt 
		   and language == std::nullopt;
}
