#include "Types/MessageEntity.h"

#include "qjsonobject.h"

Telegram::MessageEntity::MessageEntity() :
	type(Type::UNINITIALIZED_VALUE),
	offset(0),
	length(0),
	url(std::nullopt),
	user(std::nullopt),
	language(std::nullopt)
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

Telegram::MessageEntity::MessageEntity(const QJsonObject& jsonObject)
{
	auto GetMessageEntityType = [](const QJsonValue& messageEntityType) -> MessageEntity::Type
								{
									if (messageEntityType == "mention") return Type::MENTION;
									if (messageEntityType == "hashtag") return Type::HASHTAG;
									if (messageEntityType == "cashtag") return Type::CASHTAG;
									if (messageEntityType == "bot_command") return Type::BOT_COMMAND;
									if (messageEntityType == "url") return Type::URL;
									if (messageEntityType == "phone_number") return Type::PHONE_NUMBER;
									if (messageEntityType == "bold") return Type::BOLD;
									if (messageEntityType == "italic") return Type::ITALIC;
									if (messageEntityType == "underline") return Type::UNDERLINE;
									if (messageEntityType == "strikethrough") return Type::STRIKETHROUGH;
									if (messageEntityType == "code") return Type::CODE;
									if (messageEntityType == "pre") return Type::PRE;
									if (messageEntityType == "text_link") return Type::TEXT_LINK;
									if (messageEntityType == "text_mention") return Type::TEXT_MENTION;
									else return Type::UNINITIALIZED_VALUE;
								};

	jsonObject.contains("type")		? type = GetMessageEntityType(jsonObject["type"]) : type = Type::UNINITIALIZED_VALUE;
	jsonObject.contains("offset")	? offset = jsonObject["offset"].toInt()			  : offset = 0;
	jsonObject.contains("length")	? length = jsonObject["length"].toInt()			  : length = 0;
	jsonObject.contains("url")		? url = jsonObject["url"].toString()			  : url = std::nullopt;
	jsonObject.contains("user")		? user = User(jsonObject["user"].toObject())	  : user = std::nullopt;
	jsonObject.contains("language") ? language = jsonObject["language"].toString()	  : language = std::nullopt;
}

QJsonObject Telegram::MessageEntity::toObject() const
{
	if(isEmpty())
		return QJsonObject();

	auto GetMessageEntityTypeInString = [](const MessageEntity::Type& messageEntityType) -> QString
								{
									if (messageEntityType == Type::MENTION) return "mention";
									if (messageEntityType == Type::HASHTAG) return "hashtag";
									if (messageEntityType == Type::CASHTAG) return "cashtag";
									if (messageEntityType == Type::BOT_COMMAND) return "bot_command";
									if (messageEntityType == Type::URL) return "url";
									if (messageEntityType == Type::PHONE_NUMBER) return "phone_number";
									if (messageEntityType == Type::BOLD) return "bold";
									if (messageEntityType == Type::ITALIC) return "italic";
									if (messageEntityType == Type::UNDERLINE) return "underline";
									if (messageEntityType == Type::STRIKETHROUGH) return "strikethrough";
									if (messageEntityType == Type::CODE) return "code";
									if (messageEntityType == Type::PRE) return "pre";
									if (messageEntityType == Type::TEXT_LINK) return "text_link";
									if (messageEntityType == Type::TEXT_MENTION) return "text_mention";
								};

	QJsonObject messageEntityJsonObject{ {"type", GetMessageEntityTypeInString(type)}, {"offset", offset}, {"length", length} };

	if (url.has_value())					messageEntityJsonObject.insert("url", *url);
	if (user.has_value())					messageEntityJsonObject.insert("user", user->toObject());
	if (language.has_value())				messageEntityJsonObject.insert("language", *language);

	return messageEntityJsonObject;
}

bool Telegram::MessageEntity::isEmpty() const
{
	return type == Type::UNINITIALIZED_VALUE 
		   and offset == 0 
		   and length == 0 
		   and url == std::nullopt
		   and user == std::nullopt 
		   and language == std::nullopt;
}
