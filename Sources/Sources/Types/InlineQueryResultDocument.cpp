#include "Types/InlineQueryResultDocument.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultDocument::InlineQueryResultDocument() :
	id(),
	title(),
	document_url(),
	mime_type(),
	caption(),
	parse_mode(),
	caption_entities(),
	description(),
	reply_markup(),
	input_message_content(),
	thumb_url(),
	thumb_width(),
	thumb_height()
{}

Telegram::InlineQueryResultDocument::InlineQueryResultDocument(const QString& id,
															   const QString& title,
															   const QString& document_url,
															   const QString& mime_type,
															   const std::optional<QString>& caption,
															   const std::optional<QString>& parse_mode,
															   const std::optional<QVector<MessageEntity>>& caption_entities,
															   const std::optional<QString>& description,
															   const std::optional<InlineKeyboardMarkup>& reply_markup,
															   const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content,
															   const std::optional<QString>& thumb_url,
															   const std::optional<qint32>& thumb_width,
															   const std::optional<qint32>& thumb_height) :
	id(id),
	title(title),
	document_url(document_url),
	mime_type(mime_type),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	description(description),
	reply_markup(reply_markup),
	input_message_content(input_message_content),
	thumb_url(thumb_url),
	thumb_width(thumb_width),
	thumb_height(thumb_height)
{}

QJsonObject Telegram::InlineQueryResultDocument::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultDocumentJsonObject{ {"type", type}, {"id", id}, {"title", title}, {"document_url", document_url}, {"mime_type", mime_type} };

	if (caption.has_value())				inlineQueryResultDocumentJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultDocumentJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultDocumentJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (description.has_value())			inlineQueryResultDocumentJsonObject.insert("description", *description);
	if (reply_markup.has_value())			inlineQueryResultDocumentJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultDocumentJsonObject.insert("input_message_content", (**input_message_content).toObject());
	if (thumb_url.has_value())				inlineQueryResultDocumentJsonObject.insert("thumb_url", *thumb_url);
	if (thumb_width.has_value())			inlineQueryResultDocumentJsonObject.insert("thumb_width", *thumb_width);
	if (thumb_height.has_value())			inlineQueryResultDocumentJsonObject.insert("thumb_height", *thumb_height);

	return inlineQueryResultDocumentJsonObject;
}

bool Telegram::InlineQueryResultDocument::isEmpty() const
{
	return id == ""
		   and title == ""
		   and document_url == ""
		   and mime_type == ""
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and description == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt
		   and thumb_url == std::nullopt
		   and thumb_width == std::nullopt
		   and thumb_height == std::nullopt;
}
