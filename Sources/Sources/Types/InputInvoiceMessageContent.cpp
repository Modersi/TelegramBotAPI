#include "Types/InputInvoiceMessageContent.h"

#include "Internal/Utility/QJsonArrayInserter.h"

Telegram::InputInvoiceMessageContent::InputInvoiceMessageContent() :
	title(),
	description(),
	payload(),
	provider_token(),
	currency(),
	//prices(),
	max_tip_amount(),
	suggested_tip_amounts(),
	provider_data(),
	photo_url(),
	photo_size(),
	photo_width(),
	photo_height(),
	need_name(),
	need_phone_number(),
	need_email(),
	need_shipping_address(),
	send_phone_number_to_provider(),
	send_email_to_provider(),
	is_flexible()
{}

Telegram::InputInvoiceMessageContent::InputInvoiceMessageContent(const QString& title,
																 const QString& description,
																 const QString& payload,
																 const QString& provider_token,
																 const QString& currency,
																 //const QVector<LabeledPrice>& prices,
																 const std::optional<qint32>& max_tip_amount,
																 const std::optional<QVector<qint32>>& suggested_tip_amounts,
																 const std::optional<QJsonObject>& provider_data,
																 const std::optional<QString>& photo_url,
																 const std::optional<qint32>& photo_size,
																 const std::optional<qint32>& photo_width,
																 const std::optional<qint32>& photo_height,
																 const std::optional<bool>& need_name,
																 const std::optional<bool>& need_phone_number,
																 const std::optional<bool>& need_email,
																 const std::optional<bool>& need_shipping_address,
																 const std::optional<bool>& send_phone_number_to_provider,
																 const std::optional<bool>& send_email_to_provider,
																 const std::optional<bool>& is_flexible) :
	title(title),
	description(description),
	payload(payload),
	provider_token(provider_token),
	currency(currency),
	//prices(prices),
	max_tip_amount(max_tip_amount),
	suggested_tip_amounts(suggested_tip_amounts),
	provider_data(provider_data),
	photo_url(photo_url),
	photo_size(photo_size),
	photo_width(photo_width),
	photo_height(photo_height),
	need_name(need_name),
	need_phone_number(need_phone_number),
	need_email(need_email),
	need_shipping_address(need_shipping_address),
	send_phone_number_to_provider(send_phone_number_to_provider),
	send_email_to_provider(send_email_to_provider),
	is_flexible(is_flexible)
{}

QJsonObject Telegram::InputInvoiceMessageContent::toObject() const {
	if (isEmpty()) return {};

	QJsonObject input_invoice_message_content_json_object{ {"title", title}, {"description", description}, {"payload", payload}, {"provider_token", provider_token}, {"currency", currency}/*, {"prices", Utility::QJsonArrayInserter::make(prices)}*/ };

	if (max_tip_amount.has_value())					input_invoice_message_content_json_object.insert("max_tip_amount", *max_tip_amount);
	if (suggested_tip_amounts.has_value())			input_invoice_message_content_json_object.insert("suggested_tip_amounts", Utility::QJsonArrayInserter::make(*suggested_tip_amounts));
	if (provider_data.has_value())					input_invoice_message_content_json_object.insert("provider_data", *provider_data);
	if (photo_url.has_value())						input_invoice_message_content_json_object.insert("photo_url", *photo_url);
	if (photo_size.has_value())						input_invoice_message_content_json_object.insert("photo_size", *photo_size);
	if (photo_width.has_value())					input_invoice_message_content_json_object.insert("photo_width", *photo_width);
	if (photo_height.has_value())					input_invoice_message_content_json_object.insert("photo_height", *photo_height);
	if (need_name.has_value())						input_invoice_message_content_json_object.insert("need_name", *need_name);
	if (need_phone_number.has_value())				input_invoice_message_content_json_object.insert("need_phone_number", *need_phone_number);
	if (need_email.has_value())						input_invoice_message_content_json_object.insert("need_email", *need_email);
	if (need_shipping_address.has_value())			input_invoice_message_content_json_object.insert("need_shipping_address", *need_shipping_address);
	if (send_phone_number_to_provider.has_value())	input_invoice_message_content_json_object.insert("send_phone_number_to_provider", *send_phone_number_to_provider);
	if (send_email_to_provider.has_value())			input_invoice_message_content_json_object.insert("send_email_to_provider", *send_email_to_provider);
	if (is_flexible.has_value())					input_invoice_message_content_json_object.insert("is_flexible", *is_flexible);

	return input_invoice_message_content_json_object;
}

bool Telegram::InputInvoiceMessageContent::isEmpty() const {
	return title == ""
		   and description == ""
		   and payload == ""
		   and provider_token == ""
		   and currency == ""
		   //and prices.isEmpty()
		   and max_tip_amount == std::nullopt
		   and suggested_tip_amounts == std::nullopt
		   and provider_data == std::nullopt
		   and photo_url == std::nullopt
		   and photo_size == std::nullopt
		   and photo_width == std::nullopt
		   and photo_height == std::nullopt
		   and need_name == std::nullopt
		   and need_phone_number == std::nullopt
		   and need_email == std::nullopt
		   and need_shipping_address == std::nullopt
		   and send_phone_number_to_provider == std::nullopt
		   and send_email_to_provider == std::nullopt
		   and is_flexible == std::nullopt;
}
