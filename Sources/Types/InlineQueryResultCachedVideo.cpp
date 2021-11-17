#include "Types/InlineQueryResultCachedVideo.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultCachedVideo::InlineQueryResultCachedVideo() :
	id(),
	video_file_id(),
	title(),
	description(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{
}

Telegram::InlineQueryResultCachedVideo::InlineQueryResultCachedVideo(const QString& id, 
																		   const QString& video_file_id,
																		   const QString& title,
																		   const std::optional<QString>& description,
																		   const std::optional<QString>& caption,
																		   const std::optional<QString>& parse_mode,
																		   const std::optional<QVector<MessageEntity>>& caption_entities,
																		   const std::optional<InlineKeyboardMarkup>& reply_markup,
																		   const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	video_file_id(video_file_id),
	title(title),
	description(description),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{
}

QJsonObject Telegram::InlineQueryResultCachedVideo::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultCachedVideoJsonObject{ {"type", type}, {"id", id}, {"title", title}, {"video_file_id", video_file_id} };

	if (description.has_value())			inlineQueryResultCachedVideoJsonObject.insert("description", *description);
	if (caption.has_value())				inlineQueryResultCachedVideoJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultCachedVideoJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultCachedVideoJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (reply_markup.has_value())			inlineQueryResultCachedVideoJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultCachedVideoJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultCachedVideoJsonObject;
}

bool Telegram::InlineQueryResultCachedVideo::isEmpty() const
{
	return id == ""
		   and title == ""
		   and video_file_id == ""
		   and description == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
