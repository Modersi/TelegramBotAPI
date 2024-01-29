#include "Types/InlineQueryResultCachedDocument.h"

#include "Internal/Utility/QJsonArrayInserter.h"

Telegram::InlineQueryResultCachedDocument::InlineQueryResultCachedDocument() :
	id(),
	title(),
	document_file_id(),
	description(),
	caption(),
	parse_mode(),
	caption_entities(),
	reply_markup(),
	input_message_content()
{}

Telegram::InlineQueryResultCachedDocument::InlineQueryResultCachedDocument(const QString& id, 
																		   const QString& title,
																		   const QString& document_file_id,
																		   const std::optional<QString>& description,
																		   const std::optional<QString>& caption,
																		   const std::optional<QString>& parse_mode,
																		   const std::optional<QVector<MessageEntity>>& caption_entities,
																		   const std::optional<InlineKeyboardMarkup>& reply_markup,
																		   const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content) :
	id(id),
	title(title),
	document_file_id(document_file_id),
	description(description),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	reply_markup(reply_markup),
	input_message_content(input_message_content)
{}

QJsonObject Telegram::InlineQueryResultCachedDocument::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_cached_document_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"title", title}, {"document_file_id", document_file_id} };

	if (description.has_value())			inline_query_result_cached_document_json_object.insert("description", *description);
	if (caption.has_value())				inline_query_result_cached_document_json_object.insert("caption", *caption);
	if (parse_mode.has_value())				inline_query_result_cached_document_json_object.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())		inline_query_result_cached_document_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));
	if (reply_markup.has_value())			inline_query_result_cached_document_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_cached_document_json_object.insert("input_message_content", (**input_message_content).toObject());

	return inline_query_result_cached_document_json_object;
}

bool Telegram::InlineQueryResultCachedDocument::isEmpty() const {
	return id == ""
		   and title == ""
		   and document_file_id == ""
		   and description == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultCachedDocument::getType() const {
	return type;
}
