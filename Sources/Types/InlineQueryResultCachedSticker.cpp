#include "Types/InlineQueryResultCachedSticker.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultCachedSticker::InlineQueryResultCachedSticker() :
	id(),
	sticker_file_id(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultCachedSticker::InlineQueryResultCachedSticker(const QString& id,
																		 const QString& sticker_file_id,
																		 const std::optional<InlineKeyboardMarkup>& reply_markup,
																		 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	sticker_file_id(sticker_file_id),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultCachedSticker::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultCachedStickerJsonObject{ {"type", type}, {"id", id}, {"sticker_file_id", sticker_file_id} };

	if (reply_markup.has_value())			inlineQueryResultCachedStickerJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultCachedStickerJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultCachedStickerJsonObject;
}

bool Telegram::InlineQueryResultCachedSticker::isEmpty() const
{
	return id == ""
		   and sticker_file_id == ""
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
