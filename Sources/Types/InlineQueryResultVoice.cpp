#include "Types/InlineQueryResultVoice.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

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

QJsonObject Telegram::InlineQueryResultVoice::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultVoiceJsonObject{ {"type", type}, {"id", id}, {"voice_url", voice_url}, {"title", title} };

	if (caption.has_value())				inlineQueryResultVoiceJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultVoiceJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultVoiceJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (voice_duration.has_value())			inlineQueryResultVoiceJsonObject.insert("voice_duration", *voice_duration);
	if (reply_markup.has_value())			inlineQueryResultVoiceJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultVoiceJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultVoiceJsonObject;
}

bool Telegram::InlineQueryResultVoice::isEmpty() const
{
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
