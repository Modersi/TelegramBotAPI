#include "Types/InlineKeyboardMarkup.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

#include "Internal/ConversionFunctions.h"

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup() :
	inline_keyboard()
{}

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup(const QVector<QVector<InlineKeyboardButton>>& inline_keyboard) :
	inline_keyboard(inline_keyboard)
{}

Telegram::InlineKeyboardMarkup::InlineKeyboardMarkup(const QJsonObject& jsonObject)
{
	jsonObject.contains("inline_keyboard") ? inline_keyboard = DoubleQJsonArrayToDoubleQVector<InlineKeyboardButton>(jsonObject["inline_keyboard"].toArray()) : inline_keyboard = QVector<QVector<InlineKeyboardButton>>();
}

QJsonObject Telegram::InlineKeyboardMarkup::toObject() const
{
	if(isEmpty())
		return QJsonObject();

	return QJsonObject{ {"inline_keyboard", DoubleQVectorToDoubleQJsonArray(inline_keyboard)} };
}

bool Telegram::InlineKeyboardMarkup::isEmpty() const
{
	return inline_keyboard.isEmpty();
}
