#include "Types/InlineQueryResultVideo.h"

#include "Internal/Utility/QJsonArrayInserter.h"

Telegram::InlineQueryResultVideo::InlineQueryResultVideo() :
	id(),
	video_url(),
	mime_type(),
	thumb_url(),
	title(),
	caption(),
	parse_mode(),
	caption_entities(),
	video_width(),
	video_height(),
	video_duration(),
	description(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultVideo::InlineQueryResultVideo(const QString& id,
														 const QString& video_url,
														 const QString& mime_type,
														 const QString& thumb_url,
														 const QString& title,
														 const std::optional<QString>& caption,
														 const std::optional<QString>& parse_mode,
														 const std::optional<QVector<MessageEntity>>& caption_entities,
														 const std::optional<qint32>& video_width,
														 const std::optional<qint32>& video_height,
														 const std::optional<qint32>& video_duration,
														 const std::optional<QString>& description,
														 const std::optional<InlineKeyboardMarkup>& reply_markup,
														 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	video_url(video_url),
	mime_type(mime_type),
	thumb_url(thumb_url),
	title(title),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	video_width(video_width),
	video_height(video_height),
	video_duration(video_duration),
	description(description),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultVideo::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_video_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"video_url", video_url}, {"mime_type", mime_type}, {"thumb_url", thumb_url}, {"title", title} };

	if (caption.has_value())				inline_query_result_video_json_object.insert("caption", *caption);
	if (parse_mode.has_value())				inline_query_result_video_json_object.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inline_query_result_video_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));
	if (video_width.has_value())			inline_query_result_video_json_object.insert("video_width", *video_width);
	if (video_height.has_value())			inline_query_result_video_json_object.insert("video_height", *video_height);
	if (video_duration.has_value())			inline_query_result_video_json_object.insert("video_duration", *video_duration);
	if (description.has_value())			inline_query_result_video_json_object.insert("description", *description);
	if (reply_markup.has_value())			inline_query_result_video_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_video_json_object.insert("input_message_content", (**input_message_content).toObject());

	return inline_query_result_video_json_object;
}

bool Telegram::InlineQueryResultVideo::isEmpty() const {
	return id == ""
		   and video_url == ""
		   and mime_type == ""
		   and thumb_url == ""
		   and title == ""
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and video_width == std::nullopt
		   and video_height == std::nullopt
		   and video_duration == std::nullopt
		   and description == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultVideo::getType() const {
	return type;
}
