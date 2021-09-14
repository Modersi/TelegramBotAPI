#include "Types/Update.h"

#include "qjsonobject.h"

Telegram::Update::Update() :
	update_id(0),
	message(std::nullopt),
	edited_message(std::nullopt),
	channel_post(std::nullopt),
	edited_channel_post(std::nullopt),
	//inline_query(std::nullopt),
	//chosen_inline_result(std::nullopt),
	callback_query(std::nullopt),
	//shipping_query(std::nullopt),
	//pre_checkout_query(std::nullopt),
	poll(std::nullopt),
	poll_answer(std::nullopt),
	my_chat_member(std::nullopt),
	chat_member(std::nullopt)
{}

Telegram::Update::Update(const qint32& update_id,
						 const std::optional<Message>& message,
						 const std::optional<Message>& edited_message,
						 const std::optional<Message>& channel_post,
						 const std::optional<Message>& edited_channel_post,
						 //const std::optional<InlineQuery>& inline_query,
						 //const std::optional<ChosenInlineResult>& chosen_inline_result,
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
	//inline_query(inline_query),
	//chosen_inline_result(chosen_inline_result),
	callback_query(callback_query),
	//shipping_query(shipping_query),
	//pre_checkout_query(pre_checkout_query),
	poll(poll),
	poll_answer(poll_answer),
	my_chat_member(my_chat_member),
	chat_member(chat_member)
{}

Telegram::Update::Update(const QJsonObject& jsonObject)
{
	jsonObject.contains("update_id")			? update_id = jsonObject["update_id"].toInt()											   : update_id = 0;
	jsonObject.contains("message")				? message = Message(jsonObject["message"].toObject())									   : message = std::nullopt;
	jsonObject.contains("edited_message")		? edited_message = Message(jsonObject["edited_message"].toObject())						   : edited_message = std::nullopt;
	jsonObject.contains("channel_post")			? channel_post = Message(jsonObject["channel_post"].toObject())							   : channel_post = std::nullopt;
	jsonObject.contains("edited_channel_post")	? edited_channel_post = jsonObject["edited_channel_post"].toObject()					   : edited_channel_post = std::nullopt;
	//jsonObject.contains("inline_query")			? inline_query = InlineQuery(jsonObject["inline_query"].toObject())						   : inline_query = std::nullopt;
	//jsonObject.contains("chosen_inline_result") ? chosen_inline_result = ChosenInlineResult(jsonObject["chosen_inline_result"].toObject()) : chosen_inline_result = std::nullopt;
	jsonObject.contains("callback_query")		? callback_query = CallbackQuery(jsonObject["callback_query"].toObject())				   : callback_query = std::nullopt;
	//jsonObject.contains("shipping_query")		? shipping_query = ShippingQuery(jsonObject["shipping_query"].toObject())				   : shipping_query = std::nullopt;
	//jsonObject.contains("pre_checkout_query")	? pre_checkout_query = PreCheckoutQuery(jsonObject["pre_checkout_query"].toObject())	   : pre_checkout_query = std::nullopt;
	jsonObject.contains("poll")					? poll = Poll(jsonObject["poll"].toObject())											   : poll = std::nullopt;
	jsonObject.contains("poll_answer")			? poll_answer = PollAnswer(jsonObject["poll_answer"].toObject())						   : poll_answer = std::nullopt;
	jsonObject.contains("my_chat_member")		? my_chat_member = ChatMemberUpdated(jsonObject["my_chat_member"].toObject())			   : my_chat_member = std::nullopt;
	jsonObject.contains("chat_member")			? chat_member = ChatMemberUpdated(jsonObject["chat_member"].toObject())					   : chat_member = std::nullopt;
}

QJsonObject Telegram::Update::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject updateJsonObject{ {"update_id", update_id} };

	if (message.has_value())				updateJsonObject.insert("message", message->toObject());
	if (edited_message.has_value())			updateJsonObject.insert("edited_message", edited_message->toObject());
	if (channel_post.has_value())			updateJsonObject.insert("channel_post", channel_post->toObject());
	if (edited_channel_post.has_value())	updateJsonObject.insert("edited_channel_post", edited_channel_post->toObject());
	//if (inline_query.has_value())			updateJsonObject.insert("inline_query", inline_query->toObject());
	//if (chosen_inline_result.has_value())	updateJsonObject.insert("chosen_inline_result", chosen_inline_result->toObject());
	if (callback_query.has_value())			updateJsonObject.insert("callback_query", callback_query->toObject());
	//if (shipping_query.has_value())			updateJsonObject.insert("shipping_query", shipping_query->toObject());
	//if (pre_checkout_query.has_value())		updateJsonObject.insert("pre_checkout_query", pre_checkout_query->toObject());
	if (poll.has_value())					updateJsonObject.insert("poll", poll->toObject());
	if (poll_answer.has_value())			updateJsonObject.insert("poll_answer", poll_answer->toObject());
	if (my_chat_member.has_value())			updateJsonObject.insert("my_chat_member", my_chat_member->toObject());
	if (chat_member.has_value())			updateJsonObject.insert("chat_member", chat_member->toObject());

	return updateJsonObject;
}

bool Telegram::Update::isEmpty() const
{
	return update_id == 0
		   and message == std::nullopt
		   and edited_message == std::nullopt
		   and channel_post == std::nullopt
		   and edited_channel_post == std::nullopt
		   //and inline_query == std::nullopt
		   //and chosen_inline_result == std::nullopt
		   and callback_query == std::nullopt
		   //and shipping_query == std::nullopt
		   //and pre_checkout_query == std::nullopt
		   and poll == std::nullopt
		   and poll_answer == std::nullopt
		   and my_chat_member == std::nullopt
		   and chat_member == std::nullopt;
}
