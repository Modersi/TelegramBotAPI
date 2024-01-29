#include "Types/InputTextMessageContent.h"

#include "Internal/Utility/QJsonArrayInserter.h"

Telegram::InputTextMessageContent::InputTextMessageContent() :
	message_text(),
	parse_mode(),
	entities(),
	disable_web_page_preview()
	
{}

Telegram::InputTextMessageContent::InputTextMessageContent(const QString& message_text,
														   const std::optional<QString>& parse_mode,
														   const std::optional<QVector<MessageEntity>>& entities,
														   const std::optional<bool>& disable_web_page_preview) :
	message_text(message_text),
	parse_mode(parse_mode),
	entities(entities),
	disable_web_page_preview(disable_web_page_preview)
{}

QJsonObject Telegram::InputTextMessageContent::toObject() const {
	if (isEmpty()) return {};

	QJsonObject input_text_message_content_json_object{ {"message_text", message_text} };

	if (parse_mode.has_value())					input_text_message_content_json_object.insert("parse_mode", *parse_mode);
	if (entities.has_value())					input_text_message_content_json_object.insert("entities", Utility::QJsonArrayInserter::make(*entities));
	if (disable_web_page_preview.has_value())	input_text_message_content_json_object.insert("disable_web_page_preview", *disable_web_page_preview);

	return input_text_message_content_json_object;
}

bool Telegram::InputTextMessageContent::isEmpty() const {
	return message_text == ""
		   and parse_mode == std::nullopt
		   and entities == std::nullopt
		   and disable_web_page_preview == std::nullopt;
}
