#include "Types/InlineKeyboardMarkup.h"

#include "qjsonarray.h"

#include "Internal/ConversionFunctions.h"

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup() :
	inline_keyboard()
{}

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup(std::initializer_list<std::initializer_list<InlineKeyboardButton>> inline_keyboard) :
	inline_keyboard(inline_keyboard.size())
{
	std::ranges::move(std::move(inline_keyboard), this->inline_keyboard.begin());
}

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup(const QVector<QVector<InlineKeyboardButton>>& inline_keyboard) :
	inline_keyboard(inline_keyboard)
{}

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup(const QJsonObject& json_object)
{
	json_object.contains("inline_keyboard") ? inline_keyboard = DoubleQJsonArrayToDoubleQVector<InlineKeyboardButton>(json_object["inline_keyboard"].toArray()) : inline_keyboard = QVector<QVector<InlineKeyboardButton>>();
}

QJsonObject Telegram::InlineKeyboardMarkup::toObject() const {
	if (isEmpty()) return {};

	return { {"inline_keyboard", DoubleQVectorToDoubleQJsonArray(inline_keyboard)} };
}

bool Telegram::InlineKeyboardMarkup::isEmpty() const {
	return inline_keyboard.isEmpty();
}
