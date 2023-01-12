#include "Types/Update.h"

Telegram::Update::Update() :
	update_id(),
	message(),
	edited_message(),
	channel_post(),
	edited_channel_post(),
	inline_query(),
	chosen_inline_result(),
	callback_query(),
	//shipping_query(),
	//pre_checkout_query(),
	poll(),
	poll_answer(),
	my_chat_member(),
	chat_member()
{}

Telegram::Update::Update(const qint32& update_id,
						 const std::optional<Message>& message,
						 const std::optional<Message>& edited_message,
						 const std::optional<Message>& channel_post,
						 const std::optional<Message>& edited_channel_post,
						 const std::optional<InlineQuery>& inline_query,
						 const std::optional<ChosenInlineResult>& chosen_inline_result,
						 const std::optional<CallbackQuery>& callback_query,
						 //const std::optional<ShippingQuery>& shipping_query,
						 //const std::optional<PreCheckoutQuery>& pre_checkout_query,
						 const std::optional<Poll>& poll,
						 const std::optional<PollAnswer>& poll_answer,
						 const std::optional<ChatMemberUpdated>& my_chat_member,
						 const std::optional<ChatMemberUpdated>& chat_member) :
	update_id(update_id),
	message(message),
	edited_message(edited_message),
	channel_post(channel_post),
	edited_channel_post(edited_channel_post),
	inline_query(inline_query),
	chosen_inline_result(chosen_inline_result),
	callback_query(callback_query),
	//shipping_query(shipping_query),
	//pre_checkout_query(pre_checkout_query),
	poll(poll),
	poll_answer(poll_answer),
	my_chat_member(my_chat_member),
	chat_member(chat_member)
{}

Telegram::Update::Update(const QJsonObject& json_object) {
	json_object.contains("update_id")				? update_id = json_object["update_id"].toInt()											    : update_id = 0;
	json_object.contains("message")					? message = Message(json_object["message"].toObject())									    : message = std::nullopt;
	json_object.contains("edited_message")			? edited_message = Message(json_object["edited_message"].toObject())						: edited_message = std::nullopt;
	json_object.contains("channel_post")			? channel_post = Message(json_object["channel_post"].toObject())							: channel_post = std::nullopt;
	json_object.contains("edited_channel_post")		? edited_channel_post = json_object["edited_channel_post"].toObject()					    : edited_channel_post = std::nullopt;
	json_object.contains("inline_query")			? inline_query = InlineQuery(json_object["inline_query"].toObject())						: inline_query = std::nullopt;
	json_object.contains("chosen_inline_result")	? chosen_inline_result = ChosenInlineResult(json_object["chosen_inline_result"].toObject()) : chosen_inline_result = std::nullopt;
	json_object.contains("callback_query")			? callback_query = CallbackQuery(json_object["callback_query"].toObject())					: callback_query = std::nullopt;
	//json_object.contains("shipping_query")		? shipping_query = ShippingQuery(json_object["shipping_query"].toObject())					: shipping_query = std::nullopt;
	//json_object.contains("pre_checkout_query")	? pre_checkout_query = PreCheckoutQuery(json_object["pre_checkout_query"].toObject())		: pre_checkout_query = std::nullopt;
	json_object.contains("poll")					? poll = Poll(json_object["poll"].toObject())												: poll = std::nullopt;
	json_object.contains("poll_answer")				? poll_answer = PollAnswer(json_object["poll_answer"].toObject())							: poll_answer = std::nullopt;
	json_object.contains("my_chat_member")			? my_chat_member = ChatMemberUpdated(json_object["my_chat_member"].toObject())				: my_chat_member = std::nullopt;
	json_object.contains("chat_member")				? chat_member = ChatMemberUpdated(json_object["chat_member"].toObject())					: chat_member = std::nullopt;
}

QJsonObject Telegram::Update::toObject() const {
	if (isEmpty()) return {};

	QJsonObject update_json_object{ {"update_id", update_id} };

	if (message.has_value())				update_json_object.insert("message", message->toObject());
	if (edited_message.has_value())			update_json_object.insert("edited_message", edited_message->toObject());
	if (channel_post.has_value())			update_json_object.insert("channel_post", channel_post->toObject());
	if (edited_channel_post.has_value())	update_json_object.insert("edited_channel_post", edited_channel_post->toObject());
	if (inline_query.has_value())			update_json_object.insert("inline_query", inline_query->toObject());
	if (chosen_inline_result.has_value())	update_json_object.insert("chosen_inline_result", chosen_inline_result->toObject());
	if (callback_query.has_value())			update_json_object.insert("callback_query", callback_query->toObject());
	//if (shipping_query.has_value())			update_json_object.insert("shipping_query", shipping_query->toObject());
	//if (pre_checkout_query.has_value())		update_json_object.insert("pre_checkout_query", pre_checkout_query->toObject());
	if (poll.has_value())					update_json_object.insert("poll", poll->toObject());
	if (poll_answer.has_value())			update_json_object.insert("poll_answer", poll_answer->toObject());
	if (my_chat_member.has_value())			update_json_object.insert("my_chat_member", my_chat_member->toObject());
	if (chat_member.has_value())			update_json_object.insert("chat_member", chat_member->toObject());

	return update_json_object;
}

bool Telegram::Update::isEmpty() const {
	return update_id == 0
		   and message == std::nullopt
		   and edited_message == std::nullopt
		   and channel_post == std::nullopt
		   and edited_channel_post == std::nullopt
		   and inline_query == std::nullopt
		   and chosen_inline_result == std::nullopt
		   and callback_query == std::nullopt
		   //and shipping_query == std::nullopt
		   //and pre_checkout_query == std::nullopt
		   and poll == std::nullopt
		   and poll_answer == std::nullopt
		   and my_chat_member == std::nullopt
		   and chat_member == std::nullopt;
}
