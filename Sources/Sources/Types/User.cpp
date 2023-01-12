 #include "Types/User.h"

Telegram::User::User() :
	id(),
	is_bot(),
	first_name(),
	last_name(),
	username(),
	language_code(),
	can_join_groups(),
	can_read_all_group_messages(),
	supports_inline_queries()
{}

Telegram::User::User(const qint64& id,
					 const bool& is_bot,
					 const QString& first_name,
					 const std::optional<QString>& last_name,
					 const std::optional<QString>& username,
					 const std::optional<QString>& language_code,
					 const std::optional<bool>& can_join_groups,
					 const std::optional<bool>& can_read_all_group_messages,
					 const std::optional<bool>& supports_inline_queries) :
	id(id),
	is_bot(is_bot),
	first_name(first_name),
	last_name(last_name),
	username(username),
	language_code(language_code),
	can_join_groups(can_join_groups),
	can_read_all_group_messages(can_read_all_group_messages),
	supports_inline_queries(supports_inline_queries)
{
}

Telegram::User::User(const QJsonObject& jsonObject)
{
	jsonObject.contains("id")							? id = jsonObject["id"].toInteger()												   : id = 0;
	jsonObject.contains("is_bot")						? is_bot = jsonObject["is_bot"].toBool()										   : is_bot = false;
	jsonObject.contains("first_name")					? first_name = jsonObject["first_name"].toString()								   : first_name = "";
	jsonObject.contains("last_name")					? last_name = jsonObject["last_name"].toString()								   : last_name = std::nullopt;
	jsonObject.contains("username")						? username = jsonObject["username"].toString()									   : username = std::nullopt;
	jsonObject.contains("language_code")				? language_code = jsonObject["language_code"].toString()						   : language_code = std::nullopt;
	jsonObject.contains("can_join_groups")				? can_join_groups = jsonObject["can_join_groups"].toBool()						   : can_join_groups = std::nullopt;
	jsonObject.contains("can_read_all_group_messages")  ? can_read_all_group_messages = jsonObject["can_read_all_group_messages"].toBool() : can_read_all_group_messages = std::nullopt;
	jsonObject.contains("supports_inline_queries")		? supports_inline_queries = jsonObject["supports_inline_queries"].toBool()		   : supports_inline_queries = std::nullopt;
}

QJsonObject Telegram::User::toObject() const {
	if (isEmpty()) return {};

	QJsonObject userJsonObject{ {"id", id}, {"is_bot", is_bot}, {"first_name", first_name} };

	if (last_name.has_value())						userJsonObject.insert("last_name", *last_name);
	if (username.has_value())						userJsonObject.insert("username", *username);
	if (language_code.has_value())					userJsonObject.insert("language_code", *language_code);
	if (can_join_groups.has_value())				userJsonObject.insert("can_join_groups", *can_join_groups);
	if (can_read_all_group_messages.has_value())	userJsonObject.insert("can_read_all_group_messages", *can_read_all_group_messages);
	if (supports_inline_queries.has_value())		userJsonObject.insert("supports_inline_queries", *supports_inline_queries);

	return userJsonObject;
}

bool Telegram::User::isEmpty() const {
	return id == 0 
		   and is_bot == false 
		   and first_name == "" 
		   and last_name == std::nullopt 
		   and username == std::nullopt 
		   and language_code == std::nullopt 
		   and can_join_groups == std::nullopt 
		   and can_read_all_group_messages == std::nullopt 
		   and supports_inline_queries == std::nullopt;
}
