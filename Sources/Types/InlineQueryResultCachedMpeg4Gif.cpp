#include "Types/InlineQueryResultCachedMpeg4Gif.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultCachedMpeg4Gif::InlineQueryResultCachedMpeg4Gif() :
	id(),
	mpeg4_file_id(),
	title(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultCachedMpeg4Gif::InlineQueryResultCachedMpeg4Gif(const QString& id,
																		   const QString& mpeg4_file_id,
																		   const std::optional<QString>& title,
																		   const std::optional<QString>& caption,
																		   const std::optional<QString>& parse_mode,
																		   const std::optional<QVector<MessageEntity>>& caption_entities,
																		   const std::optional<InlineKeyboardMarkup>& reply_markup,
																		   const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	mpeg4_file_id(mpeg4_file_id),
	title(title),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultCachedMpeg4Gif::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultCachedMpeg4GifJsonObject{ {"type", type}, {"id", id}, {"mpeg4_file_id", mpeg4_file_id} };

	if (title.has_value())					inlineQueryResultCachedMpeg4GifJsonObject.insert("title", *title);
	if (caption.has_value())				inlineQueryResultCachedMpeg4GifJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultCachedMpeg4GifJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultCachedMpeg4GifJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (reply_markup.has_value())			inlineQueryResultCachedMpeg4GifJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultCachedMpeg4GifJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultCachedMpeg4GifJsonObject;
}

bool Telegram::InlineQueryResultCachedMpeg4Gif::isEmpty() const
{
	return id == ""
		   and mpeg4_file_id == ""
		   and title == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
