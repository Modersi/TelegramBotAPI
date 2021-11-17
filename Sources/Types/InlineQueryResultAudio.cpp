#include "Types/InlineQueryResultAudio.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultAudio::InlineQueryResultAudio() :
	id(),
	audio_url(),
	title(),
	caption(),
	parse_mode(),
	caption_entities(),
	performer(),
	audio_duration(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultAudio::InlineQueryResultAudio(const QString& id,
														 const QString& audio_url,
														 const QString& title,
														 const std::optional<QString>& caption,
														 const std::optional<QString>& parse_mode,
														 const std::optional<QVector<MessageEntity>>& caption_entities,
														 const std::optional<QString>& performer,
														 const std::optional<qint32>& audio_duration,
														 const std::optional<InlineKeyboardMarkup>& reply_markup,
														 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	audio_url(audio_url),
	title(title),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	performer(performer),
	audio_duration(audio_duration),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultAudio::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultAudioJsonObject{ {"type", type}, {"id", id}, {"audio_url", audio_url}, {"title", title} };

	if (caption.has_value())				inlineQueryResultAudioJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultAudioJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultAudioJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (performer.has_value())				inlineQueryResultAudioJsonObject.insert("performer", *performer);
	if (audio_duration.has_value())			inlineQueryResultAudioJsonObject.insert("audio_duration", *audio_duration);
	if (reply_markup.has_value())			inlineQueryResultAudioJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultAudioJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultAudioJsonObject;
}

bool Telegram::InlineQueryResultAudio::isEmpty() const
{
	return id == ""
		   and audio_url == ""
		   and title == ""
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and performer == std::nullopt
		   and audio_duration == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
