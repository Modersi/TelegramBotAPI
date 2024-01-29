#include "Types/ReplyKeyboardMarkup.h"

#include "qjsonarray.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup() :
	keyboard(),
	resize_keyboard(),
	one_time_keyboard(),
	selective()
{}

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup(std::initializer_list<std::initializer_list<KeyboardButton>> keyboard,
												   const std::optional<bool>&resize_keyboard,
												   const std::optional<bool>&one_time_keyboard,
												   const std::optional<bool>&selective) :
	keyboard(keyboard.size()),
	resize_keyboard(resize_keyboard),
	one_time_keyboard(one_time_keyboard),
	selective(selective)
{
	std::ranges::move(std::move(keyboard), this->keyboard.begin());
}

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup(const QVector<QVector<KeyboardButton>>& keyboard,
												   const std::optional<bool>& resize_keyboard,
												   const std::optional<bool>& one_time_keyboard,
												   const std::optional<bool>& selective) :
	keyboard(keyboard),
	resize_keyboard(resize_keyboard),
	one_time_keyboard(one_time_keyboard),
	selective(selective)
{}

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup(const QJsonObject& json_object) {
	json_object.contains("keyboard")			? keyboard = Utility::QVectorInserter<QVector<KeyboardButton>>::make(json_object["keyboard"].toArray()) : keyboard = QVector<QVector<KeyboardButton>>();
	json_object.contains("resize_keyboard")		? resize_keyboard = json_object["resize_keyboard"].toBool()										: resize_keyboard = std::nullopt;
	json_object.contains("one_time_keyboard")	? one_time_keyboard = json_object["one_time_keyboard"].toBool()									: one_time_keyboard = std::nullopt;
	json_object.contains("selective")			? selective = json_object["selective"].toBool()													: selective = std::nullopt;
}

QJsonObject Telegram::ReplyKeyboardMarkup::toObject() const {
	if (isEmpty()) return {};

	QJsonObject reply_keyboard_markup_json_object{ {"keyboard",  Utility::QJsonArrayInserter::make(keyboard.begin(), keyboard.end())} };

	if (resize_keyboard.has_value())	reply_keyboard_markup_json_object.insert("resize_keyboard", *resize_keyboard);
	if (one_time_keyboard.has_value())	reply_keyboard_markup_json_object.insert("one_time_keyboard", *one_time_keyboard);
	if (selective.has_value())			reply_keyboard_markup_json_object.insert("selective", *selective);

	return reply_keyboard_markup_json_object;
}

bool Telegram::ReplyKeyboardMarkup::isEmpty() const {
	return keyboard.isEmpty()
		   and resize_keyboard == std::nullopt
		   and one_time_keyboard == std::nullopt
		   and selective == std::nullopt;
}
