#include "Types/InlineQueryResultPhoto.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultPhoto::InlineQueryResultPhoto() :
	id(),
	photo_url(),
	thumb_url(),
	photo_width(),
	photo_height(),
	title(),
	description(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultPhoto::InlineQueryResultPhoto(const QString& id,
														 const QString& photo_url,
														 const QString& thumb_url,
														 const std::optional<qint32>& photo_width,
														 const std::optional<qint32>& photo_height,
														 const std::optional<QString>& title,
														 const std::optional<QString>& description,
														 const std::optional<QString>& caption,
														 const std::optional<QString>& parse_mode,
														 const std::optional<QVector<MessageEntity>>& caption_entities,
														 const std::optional<InlineKeyboardMarkup>& reply_markup,
														 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	photo_url(photo_url),
	thumb_url(thumb_url),
	photo_width(photo_width),
	photo_height(photo_height),
	title(title),
	description(description),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultPhoto::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultPhotoJsonObject{ {"type", type}, {"id", id}, {"photo_url", photo_url}, {"thumb_url", thumb_url} };

	if (photo_width.has_value())			inlineQueryResultPhotoJsonObject.insert("photo_width", *photo_width);
	if (photo_height.has_value())			inlineQueryResultPhotoJsonObject.insert("photo_height", *photo_height);
	if (title.has_value())					inlineQueryResultPhotoJsonObject.insert("title", *title);
	if (description.has_value())			inlineQueryResultPhotoJsonObject.insert("description", *description);
	if (caption.has_value())				inlineQueryResultPhotoJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())				inlineQueryResultPhotoJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inlineQueryResultPhotoJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (reply_markup.has_value())			inlineQueryResultPhotoJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultPhotoJsonObject.insert("input_message_content", (**input_message_content).toObject());

	return inlineQueryResultPhotoJsonObject;
}

bool Telegram::InlineQueryResultPhoto::isEmpty() const
{
	return id == ""
		   and photo_url == ""
		   and thumb_url == ""
		   and photo_width == std::nullopt
		   and photo_height == std::nullopt
		   and title == std::nullopt
		   and description == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}
