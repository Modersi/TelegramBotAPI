#include "Types/InlineQueryResultGif.h"

#include "Internal/Utility/QJsonArrayInserter.h"

Telegram::InlineQueryResultGif::InlineQueryResultGif() :
	id(),
	gif_url(),
	thumb_url(),
	gif_width(),
	gif_height(),
	gif_duration(),
	thumb_mime_type(),
	title(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultGif::InlineQueryResultGif(const QString& id,
													 const QString& gif_url,
													 const QString& thumb_url,
													 const std::optional<qint32>& gif_width,
													 const std::optional<qint32>& gif_height,
													 const std::optional<qint32>& gif_duration,
													 const std::optional<QString>& thumb_mime_type,
													 const std::optional<QString>& title,
													 const std::optional<QString>& caption,
													 const std::optional<QString>& parse_mode,
													 const std::optional<QVector<MessageEntity>>& caption_entities,
													 const std::optional<InlineKeyboardMarkup>& reply_markup,
													 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	gif_url(gif_url),
	thumb_url(thumb_url),
	gif_width(gif_width),
	gif_height(gif_height),
	gif_duration(gif_duration),
	thumb_mime_type(thumb_mime_type),
	title(title),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultGif::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_gif_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"gif_url", gif_url}, {"thumb_url", thumb_url} };

	if (gif_width.has_value())				inline_query_result_gif_json_object.insert("gif_width", *gif_width);
	if (gif_height.has_value())				inline_query_result_gif_json_object.insert("gif_height", *gif_height);
	if (gif_duration.has_value())			inline_query_result_gif_json_object.insert("gif_duration", *gif_duration);
	if (thumb_mime_type.has_value())		inline_query_result_gif_json_object.insert("thumb_mime_type", *thumb_mime_type);
	if (title.has_value())					inline_query_result_gif_json_object.insert("title", *title);
	if (caption.has_value())				inline_query_result_gif_json_object.insert("caption", *caption);
	if (parse_mode.has_value())				inline_query_result_gif_json_object.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inline_query_result_gif_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));
	if (reply_markup.has_value())			inline_query_result_gif_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_gif_json_object.insert("input_message_content", (**input_message_content).toObject());

	return inline_query_result_gif_json_object;
}

bool Telegram::InlineQueryResultGif::isEmpty() const {
	return id == ""
		   and gif_url == ""
		   and thumb_url == ""
		   and gif_width == std::nullopt
		   and gif_height == std::nullopt
		   and gif_duration == std::nullopt
		   and thumb_mime_type == std::nullopt
		   and title == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultGif::getType() const {
	return type;
}
