#include "Types/InlineQueryResultCachedVoice.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultCachedVoice::InlineQueryResultCachedVoice() :
	id(),
	voice_file_id(),
	title(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{
}

Telegram::InlineQueryResultCachedVoice::InlineQueryResultCachedVoice(const QString& id,
																	 const QString& voice_file_id,
																	 const QString& title,
																	 const std::optional<QString>& caption,
																	 const std::optional<QString>& parse_mode,
																	 const std::optional<QVector<MessageEntity>>& caption_entities,
																	 const std::optional<InlineKeyboardMarkup>& reply_markup,
																	 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	voice_file_id(voice_file_id),
	title(title),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{
}

QJsonObject Telegram::InlineQueryResultCachedVoice::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultCachedVoiceJsonObject{ {"type", type}, {"id", id}, {"voice_file_id", voice_file_id}, {"title", title} };

	if (caption.has_value())				inlineQueryResultCachedVoiceJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultCachedVoiceJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultCachedVoiceJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (reply_markup.has_value())			inlineQueryResultCachedVoiceJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultCachedVoiceJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultCachedVoiceJsonObject;
}

bool Telegram::InlineQueryResultCachedVoice::isEmpty() const
{
	return id == ""
		   and voice_file_id == ""
		   and title == ""
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
