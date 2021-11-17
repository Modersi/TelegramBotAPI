#include "Types/InlineQueryResultArticle.h"

#include "qjsonobject.h"

#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultArticle::InlineQueryResultArticle() :
	id(),
	title(),
	input_message_content(),
	reply_markup(),
	url(),
	hide_url(),
	description(),
	thumb_url(),
	thumb_width(),
	thumb_height()
{}

Telegram::InlineQueryResultArticle::InlineQueryResultArticle(const QString& id,
															 const QString& title,
															 const std::shared_ptr<InputMessageContent>& input_message_content,
															 const std::optional<InlineKeyboardMarkup>& reply_markup,
															 const std::optional<QString>& url,
															 const std::optional<bool>& hide_url,
															 const std::optional<QString>& description,
															 const std::optional<QString>& thumb_url,
															 const std::optional<qint32>& thumb_width, 
															 const std::optional<qint32>& thumb_height) :
	id(id),
	title(title),
	input_message_content(input_message_content),
	reply_markup(reply_markup),
	url(url),
	hide_url(hide_url),
	description(description),
	thumb_url(thumb_url),
	thumb_width(thumb_width),
	thumb_height(thumb_height)
{}

QJsonObject Telegram::InlineQueryResultArticle::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultArticleJsonObject{ {"type", type}, {"id", id}, {"title", title}, {"input_message_content", input_message_content->toObject()} };

	if (reply_markup.has_value())	inlineQueryResultArticleJsonObject.insert("reply_markup", reply_markup->toObject());
	if (url.has_value())			inlineQueryResultArticleJsonObject.insert("url", *url);
	if (hide_url.has_value())		inlineQueryResultArticleJsonObject.insert("hide_url", *hide_url);
	if (description.has_value())	inlineQueryResultArticleJsonObject.insert("description", *description);
	if (thumb_url.has_value())		inlineQueryResultArticleJsonObject.insert("thumb_url", *thumb_url);
	if (thumb_width.has_value())	inlineQueryResultArticleJsonObject.insert("thumb_width", *thumb_width);
	if (thumb_height.has_value())	inlineQueryResultArticleJsonObject.insert("thumb_height", *thumb_height);

	return inlineQueryResultArticleJsonObject;
}

bool Telegram::InlineQueryResultArticle::isEmpty() const
{
	return id == ""
	       and title == ""
	       and input_message_content == nullptr
	       and reply_markup == std::nullopt
	       and url == std::nullopt
	       and hide_url == std::nullopt
	       and description == std::nullopt
	       and thumb_url == std::nullopt
	       and thumb_width == std::nullopt
	       and thumb_height == std::nullopt;
}
