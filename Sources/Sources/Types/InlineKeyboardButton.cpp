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

Telegram::InlineKeyboardButton::InlineKeyboardButton(const QJsonObject& json_object)
{
	json_object.contains("text")							? text = json_object["text"].toString()														   : text = "";
	json_object.contains("url")								? url = json_object["url"].toString()														   : url = std::nullopt;
	json_object.contains("login_url")						? login_url = LoginURL(json_object["login_url"].toObject())									   : login_url = std::nullopt;
	json_object.contains("callback_data")					? callback_data = json_object["callback_data"].toString()									   : callback_data = std::nullopt;
	json_object.contains("switch_inline_query")				? switch_inline_query = json_object["switch_inline_query"].toString()						   : switch_inline_query = std::nullopt;
	json_object.contains("switch_inline_query_current_chat") ? switch_inline_query_current_chat = json_object["switch_inline_query_current_chat"].toString() : switch_inline_query_current_chat = std::nullopt;
	//json_object.contains("callback_game")					? callback_game = CallbackGame(json_object["callback_game"].toObject())						   : callback_game = std::nullopt;
	json_object.contains("pay")								? pay = json_object["pay"].toBool()															   : pay = std::nullopt;
}

QJsonObject Telegram::InlineKeyboardButton::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_keyboard_button_json_object{ {"text", text} };

	if (url.has_value())								inline_keyboard_button_json_object.insert("url", *url);
	if (login_url.has_value())							inline_keyboard_button_json_object.insert("login_url", login_url->toObject());
	if (callback_data.has_value())						inline_keyboard_button_json_object.insert("callback_data", *callback_data);
	if (switch_inline_query.has_value())				inline_keyboard_button_json_object.insert("switch_inline_query", *switch_inline_query);
	if (switch_inline_query_current_chat.has_value())	inline_keyboard_button_json_object.insert("switch_inline_query_current_chat", *switch_inline_query_current_chat);
	//if (callback_game.has_value())						inline_keyboard_button_json_object.insert("callback_game", *callback_game);
	if (pay.has_value())								inline_keyboard_button_json_object.insert("pay", *pay);

	return inline_keyboard_button_json_object;
}

bool Telegram::InlineKeyboardButton::isEmpty() const {
	return text == ""
		   and url == std::nullopt
		   and login_url == std::nullopt
		   and callback_data == std::nullopt
		   and switch_inline_query == std::nullopt
		   and switch_inline_query_current_chat == std::nullopt
		   //and callback_game == std::nullopt
		   and pay == std::nullopt;
}
