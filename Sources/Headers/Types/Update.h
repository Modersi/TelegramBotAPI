#ifndef TELEGRAM_TYPES_UPDATE_H
#define TELEGRAM_TYPES_UPDATE_H

#include <optional>
#include <compare>

#include "qjsonobject.h"

#include "Message.h"
#include "InlineQuery.h"
#include "ChosenInlineResult.h"
#include "CallbackQuery.h"
//#include "ShippingQuery.h"
//#include "PreCheckoutQuery.h"
#include "Poll.h"
#include "PollAnswer.h"
#include "ChatMemberUpdated.h"

namespace Telegram
{
	/**
	 *
	 * @brief This struct represents an incoming update
	 *
	 * At most one of the optional parameters can be present in any given update.
	 *
	 */

	struct Update
	{
		/** @brief Default constructor. Constructs an empty Update object
		 *
		 * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
		Update();
		
		/** @brief Constructs Update object from parameters */
		Update(const qint32& update_id,
			   const std::optional<Message>& message = std::nullopt,
			   const std::optional<Message>& edited_message = std::nullopt,
			   const std::optional<Message>& channel_post = std::nullopt,
			   const std::optional<Message>& edited_channel_post = std::nullopt,
			   const std::optional<InlineQuery>& inline_query = std::nullopt,
			   const std::optional<ChosenInlineResult>& chosen_inline_result = std::nullopt,
			   const std::optional<CallbackQuery>& callback_query = std::nullopt,
			   //const std::optional<ShippingQuery>& shipping_query = std::nullopt,
			   //const std::optional<PreCheckoutQuery>& pre_checkout_query = std::nullopt,
			   const std::optional<Poll>& poll = std::nullopt,
			   const std::optional<PollAnswer>& poll_answer = std::nullopt,
			   const std::optional<ChatMemberUpdated>& my_chat_member = std::nullopt,
			   const std::optional<ChatMemberUpdated>& chat_member = std::nullopt);

		/** @brief JSON constructor. Constructs Update object from QJsonObject
		 *
		 * QJsonObject which is passed to constuctor has to has all key-value pairs related to Update class fields. For example it should contain pairs such as "update_id" = "...",
		 * "message" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
		Update(const QJsonObject& json_object);


		/* @brief Returns Update in form of JSON object. Returns empty QJsonObject if Update is empty */
		QJsonObject toObject() const;

		/* @brief Returns true if Update is empty */
		bool isEmpty() const;


		std::partial_ordering operator <=> (const Update&) const = default;


//** Fields **//

		/** @brief The update's unique identifier
		 * 
		 * Update identifiers start from a certain positive number and increase sequentially. This ID becomes especially handy if you're using Webhooks, since it allows you to ignore repeated
		 * updates or to restore the correct update sequence, should they get out of order. If there are no new updates for at least a week, then identifier of the next update will be chosen randomly instead of sequentially */
		qint32 update_id;
		
		/** @brief Optional. New incoming message of any kind — text, photo, sticker, etc. */
		std::optional<Message> message;
		
		/** @brief Optional. New version of a message that is known to the bot and was edited */
		std::optional<Message> edited_message;
		
		/** @brief Optional. New incoming channel post of any kind — text, photo, sticker, etc. */
		std::optional<Message> channel_post;
		
		/** @brief Optional. New version of a channel post that is known to the bot and was edited */
		std::optional<Message> edited_channel_post;
		
		/** @brief Optional. New incoming inline query */
		std::optional<InlineQuery> inline_query;
		
		/** @brief Optional. The result of an inline query that was chosen by a user and sent to their chat partner. Please see our documentation on the feedback collecting for details on how to enable these updates for your bot */
		std::optional<ChosenInlineResult> chosen_inline_result;
		
		/** @brief Optional. New incoming callback query */
		std::optional<CallbackQuery> callback_query;
		
		/** @brief Optional. New incoming shipping query. Only for invoices with flexible price */
		//std::optional<ShippingQuery> shipping_query;
		
		/** @brief Optional. New incoming pre-checkout query. Contains full information about checkout */
		//std::optional<PreCheckoutQuery> pre_checkout_query;
		
		/** @brief Optional. New poll state. Bots receive only updates about stopped polls and polls, which are sent by the bot */
		std::optional<Poll> poll;
		
		/** @brief Optional. A user changed their answer in a non-anonymous poll. Bots receive new votes only in polls that were sent by the bot itself */
		std::optional<PollAnswer> poll_answer;
		
		/** @brief Optional. The bot's chat member status was updated in a chat. For private chats, this update is received only when the bot is blocked or unblocked by the user */
		std::optional<ChatMemberUpdated> my_chat_member;
		
		/** @brief Optional. A chat member's status was updated in a chat. The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates to receive these updates */
		std::optional<ChatMemberUpdated> chat_member;
	};
}

#endif // TELEGRAM_TYPES_UPDATE_H
