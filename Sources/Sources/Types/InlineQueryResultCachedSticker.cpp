#include "Types/InlineQueryResultCachedSticker.h"

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

QJsonObject Telegram::InlineQueryResultCachedSticker::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_cached_sticker_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"sticker_file_id", sticker_file_id} };

	if (reply_markup.has_value())			inline_query_result_cached_sticker_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_cached_sticker_json_object.insert("input_message_content", (**input_message_content).toObject());

	return inline_query_result_cached_sticker_json_object;
}

bool Telegram::InlineQueryResultCachedSticker::isEmpty() const {
	return id == ""
		   and sticker_file_id == ""
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultCachedSticker::getType() const {
	return type;
}
