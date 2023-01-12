#include "Types/InlineQueryResultArticle.h"

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

QJsonObject Telegram::InlineQueryResultArticle::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_article_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"title", title}, {"input_message_content", input_message_content->toObject()} };

	if (reply_markup.has_value())	inline_query_result_article_json_object.insert("reply_markup", reply_markup->toObject());
	if (url.has_value())			inline_query_result_article_json_object.insert("url", *url);
	if (hide_url.has_value())		inline_query_result_article_json_object.insert("hide_url", *hide_url);
	if (description.has_value())	inline_query_result_article_json_object.insert("description", *description);
	if (thumb_url.has_value())		inline_query_result_article_json_object.insert("thumb_url", *thumb_url);
	if (thumb_width.has_value())	inline_query_result_article_json_object.insert("thumb_width", *thumb_width);
	if (thumb_height.has_value())	inline_query_result_article_json_object.insert("thumb_height", *thumb_height);

	return inline_query_result_article_json_object;
}

bool Telegram::InlineQueryResultArticle::isEmpty() const {
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

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultArticle::getType() const {
	return type;
}
