#include "Types/InlineKeyboardButton.h"

#include "qjsonobject.h"

Telegram::InlineKeyboardButton::InlineKeyboardButton() :
	text(),
	url(),
	login_url(),
	callback_data(),
	switch_inline_query(),
	switch_inline_query_current_chat(),
	//callback_game(),
	pay()
{}

Telegram::InlineKeyboardButton::InlineKeyboardButton(const QString& text,
													 const std::optional<QString>& url,
													 const std::optional<LoginURL>& login_url,
													 const std::optional<QString>& callback_data,
													 const std::optional<QString>& switch_inline_query,
													 const std::optional<QString>& switch_inline_query_current_chat,
													 //const std::optional<CallbackGame>& callback_game,
													 const std::optional<bool>& pay) :
	text(text),
	url(url),
	login_url(login_url),
	callback_data(callback_data),
	switch_inline_query(switch_inline_query),
	switch_inline_query_current_chat(switch_inline_query_current_chat),
	//callback_game(callback_game),
	pay(pay)
{}

Telegram::InlineKeyboardButton::InlineKeyboardButton(const QJsonObject& jsonObject)
{
	jsonObject.contains("text")								? text = jsonObject["text"].toString()														   : text = "";
	jsonObject.contains("url")								? url = jsonObject["url"].toString()														   : url = std::nullopt;
	jsonObject.contains("login_url")						? login_url = LoginURL(jsonObject["login_url"].toObject())									   : login_url = std::nullopt;
	jsonObject.contains("callback_data")					? callback_data = jsonObject["callback_data"].toString()									   : callback_data = std::nullopt;
	jsonObject.contains("switch_inline_query")				? switch_inline_query = jsonObject["switch_inline_query"].toString()						   : switch_inline_query = std::nullopt;
	jsonObject.contains("switch_inline_query_current_chat") ? switch_inline_query_current_chat = jsonObject["switch_inline_query_current_chat"].toString() : switch_inline_query_current_chat = std::nullopt;
	//jsonObject.contains("callback_game")					? callback_game = CallbackGame(jsonObject["callback_game"].toObject())						   : callback_game = std::nullopt;
	jsonObject.contains("pay")								? pay = jsonObject["pay"].toBool()															   : pay = std::nullopt;
}

QJsonObject Telegram::InlineKeyboardButton::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineKeyboardButtonJsonObject{ {"text", text} };

	if (url.has_value())								inlineKeyboardButtonJsonObject.insert("url", *url);
	if (login_url.has_value())							inlineKeyboardButtonJsonObject.insert("login_url", login_url->toObject());
	if (callback_data.has_value())						inlineKeyboardButtonJsonObject.insert("callback_data", *callback_data);
	if (switch_inline_query.has_value())				inlineKeyboardButtonJsonObject.insert("switch_inline_query", *switch_inline_query);
	if (switch_inline_query_current_chat.has_value())	inlineKeyboardButtonJsonObject.insert("switch_inline_query_current_chat", *switch_inline_query_current_chat);
	//if (callback_game.has_value())						inlineKeyboardButtonJsonObject.insert("callback_game", *callback_game);
	if (pay.has_value())								inlineKeyboardButtonJsonObject.insert("pay", *pay);

	return inlineKeyboardButtonJsonObject;
}

bool Telegram::InlineKeyboardButton::isEmpty() const
{
	return text == ""
		   and url == std::nullopt
		   and login_url == std::nullopt
		   and callback_data == std::nullopt
		   and switch_inline_query == std::nullopt
		   and switch_inline_query_current_chat == std::nullopt
		   //and callback_game == std::nullopt
		   and pay == std::nullopt;
}
