#include "Types/InlineQueryResultCachedAudio.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultCachedAudio::InlineQueryResultCachedAudio() :
	id(),
	audio_file_id(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{
}

Telegram::InlineQueryResultCachedAudio::InlineQueryResultCachedAudio(const QString& id,
																	 const QString& audio_file_id,
																	 const std::optional<QString>& caption,
																	 const std::optional<QString>& parse_mode,
																	 const std::optional<QVector<MessageEntity>>& caption_entities,
																	 const std::optional<InlineKeyboardMarkup>& reply_markup,
																	 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	audio_file_id(audio_file_id),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{
}

QJsonObject Telegram::InlineQueryResultCachedAudio::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultCachedVoiceJsonObject{ {"type", type}, {"id", id}, {"audio_file_id", audio_file_id} };

	if (caption.has_value())				inlineQueryResultCachedVoiceJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultCachedVoiceJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultCachedVoiceJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (reply_markup.has_value())			inlineQueryResultCachedVoiceJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultCachedVoiceJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultCachedVoiceJsonObject;
}

bool Telegram::InlineQueryResultCachedAudio::isEmpty() const
{
	return id == ""
		   and audio_file_id == ""
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
