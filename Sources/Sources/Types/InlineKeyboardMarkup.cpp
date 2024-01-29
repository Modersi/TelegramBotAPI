#include "Types/InlineKeyboardMarkup.h"

#include "qjsonarray.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

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
	json_object.contains("inline_keyboard") ? inline_keyboard = Utility::QVectorInserter<QVector<InlineKeyboardButton>>::make(json_object["inline_keyboard"].toArray()) : inline_keyboard = QVector<QVector<InlineKeyboardButton>>();
}

QJsonObject Telegram::InlineKeyboardMarkup::toObject() const {
	if (isEmpty()) return {};

	return { {"inline_keyboard", Utility::QJsonArrayInserter::make(inline_keyboard.begin(), inline_keyboard.end())} };
}

bool Telegram::InlineKeyboardMarkup::isEmpty() const {
	return inline_keyboard.isEmpty();
}
