#include "Types/ReplyKeyboardMarkup.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

#include "Internal/ConversionFunctions.h"

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup() :
	keyboard(),
	resize_keyboard(),
	one_time_keyboard(),
	selective()
{}

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup(const QVector<QVector<KeyboardButton>>& keyboard,
												   const std::optional<bool>& resize_keyboard,
												   const std::optional<bool>& one_time_keyboard,
												   const std::optional<bool>& selective) :
	keyboard(keyboard),
	resize_keyboard(resize_keyboard),
	one_time_keyboard(one_time_keyboard),
	selective(selective)
{}

Telegram::ReplyKeyboardMarkup::ReplyKeyboardMarkup(const QJsonObject& jsonObject)
{
	jsonObject.contains("keyboard")			 ? keyboard = DoubleQJsonArrayToDoubleQVector<KeyboardButton>(jsonObject["keyboard"].toArray()) : keyboard = QVector<QVector<KeyboardButton>>();
	jsonObject.contains("resize_keyboard")	 ? resize_keyboard = jsonObject["resize_keyboard"].toBool()										: resize_keyboard = std::nullopt;
	jsonObject.contains("one_time_keyboard") ? one_time_keyboard = jsonObject["one_time_keyboard"].toBool()									: one_time_keyboard = std::nullopt;
	jsonObject.contains("selective")		 ? selective = jsonObject["selective"].toBool()													: selective = std::nullopt;
}

QJsonObject Telegram::ReplyKeyboardMarkup::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject replyKeyboardMarkupJsonObject{ {"keyboard", DoubleQVectorToDoubleQJsonArray(keyboard)} };

	if (resize_keyboard.has_value())	replyKeyboardMarkupJsonObject.insert("resize_keyboard", *resize_keyboard);
	if (one_time_keyboard.has_value())	replyKeyboardMarkupJsonObject.insert("one_time_keyboard", *one_time_keyboard);
	if (selective.has_value())			replyKeyboardMarkupJsonObject.insert("selective", *selective);

	return replyKeyboardMarkupJsonObject;
}

bool Telegram::ReplyKeyboardMarkup::isEmpty() const
{
	return keyboard.isEmpty()
		   and resize_keyboard == std::nullopt
		   and one_time_keyboard == std::nullopt
		   and selective == std::nullopt;
}
