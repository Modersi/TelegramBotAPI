#include "Types/InlineQueryResultVoice.h"

#include "Internal/Utility/QJsonArrayInserter.h"

Telegram::InlineQueryResultVoice::InlineQueryResultVoice() : 
	id(),
	voice_url(),
	title(),
	caption(),
	parse_mode(),
	caption_entities(),
	voice_duration(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultVoice::InlineQueryResultVoice(const QString& id,
														 const QString& voice_url,
														 const QString& title,
														 const std::optional<QString>& caption,
														 const std::optional<QString>& parse_mode,
														 const std::optional<QVector<MessageEntity>>& caption_entities,
														 const std::optional<qint32>& voice_duration,
														 const std::optional<InlineKeyboardMarkup>& reply_markup, 
														 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) : 
	id(id),
	voice_url(voice_url),
	title(title),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	voice_duration(voice_duration),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultVoice::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_voice_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"voice_url", voice_url}, {"title", title} };

	if (caption.has_value())				inline_query_result_voice_json_object.insert("caption", *caption);
	if (parse_mode.has_value())				inline_query_result_voice_json_object.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inline_query_result_voice_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));
	if (voice_duration.has_value())			inline_query_result_voice_json_object.insert("voice_duration", *voice_duration);
	if (reply_markup.has_value())			inline_query_result_voice_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_voice_json_object.insert("input_message_content", (**input_message_content).toObject());

	return inline_query_result_voice_json_object;
}

bool Telegram::InlineQueryResultVoice::isEmpty() const {
	return id == ""
		   and voice_url == ""
		   and title == ""
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and voice_duration == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultVoice::getType() const {
	return type;
}
