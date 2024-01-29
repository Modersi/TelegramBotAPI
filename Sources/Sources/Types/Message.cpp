#include "Types/Message.h"

#include "Types/Chat.h"
#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::Message::Message() :
	message_id(),
	date(),
	chat(),
	from(),
	sender_chat(),
	forward_from(),
	forward_from_chat(),
	forward_from_message_id(),
	forward_signature(),
	forward_sender_name(),
	forward_date(),
	reply_to_message(),
	via_bot(),
	edit_date(),
	media_group_id(),
	author_signature(),
	text(),
	entities(),
	animation(),
	audio(),
	document(),
	photo(),
	sticker(),
	video(),
	video_note(),
	voice(),
	caption(),
	caption_entities(),
	contact(),
	dice(),
	//game(),
	poll(),
	venue(),
	location(),
	new_chat_members(),
	left_chat_member(),
	new_chat_title(),
	new_chat_photo(),
	delete_chat_photo(),
	group_chat_created(),
	supergroup_chat_created(),
	channel_chat_created(),
	message_auto_delete_timer_changed(),
	migrate_to_chat_id(),
	migrate_from_chat_id(),
	pinned_message(),
	//invoice(),
	//successful_payment(),
	connected_website(),
	//passport_data(),
	proximity_alert_triggered(),
	voice_chat_scheduled(),
	voice_chat_started(),
	voice_chat_ended(),
	voice_chat_participants_invited(),
	reply_markup()
{}

Telegram::Message::Message(const qint32& message_id,
						   const qint32& date,
						   const std::shared_ptr<Chat>& chat,
						   const std::optional<User>& from,
						   const std::optional<std::shared_ptr<Chat>>& sender_chat,
						   const std::optional<User>& forward_from,
						   const std::optional<std::shared_ptr<Chat>>& forward_from_chat,
						   const std::optional<qint32>& forward_from_message_id,
						   const std::optional<QString>& forward_signature,
						   const std::optional<QString>& forward_sender_name,
						   const std::optional<qint32>& forward_date,
						   const std::optional<std::shared_ptr<Message>>& reply_to_message,
						   const std::optional<User>& via_bot,
						   const std::optional<qint32>& edit_date,
						   const std::optional<QString>& media_group_id,
						   const std::optional<QString>& author_signature,
						   const std::optional<QString>& text,
						   const std::optional<QVector<MessageEntity>>& entities,
						   const std::optional<Animation>& animation,
						   const std::optional<Audio>& audio,
						   const std::optional<Document>& document,
						   const std::optional<QVector<PhotoSize>>& photo,
						   const std::optional<Sticker>& sticker,
						   const std::optional<Video>& video,
						   const std::optional<VideoNote>& video_note,
						   const std::optional<Voice>& voice,
						   const std::optional<QString>& caption,
						   const std::optional<QVector<MessageEntity>>& caption_entities,
						   const std::optional<Contact>& contact,
						   const std::optional<Dice>& dice,
						   //const std::optional<Game>& game,
						   const std::optional<Poll>& poll,
						   const std::optional<Venue>& venue,
						   const std::optional<Location>& location,
						   const std::optional<QVector<User>>& new_chat_members,
						   const std::optional<User>& left_chat_member,
						   const std::optional<QString>& new_chat_title,
						   const std::optional<QVector<PhotoSize>>& new_chat_photo,
						   const std::optional<bool>& delete_chat_photo,
						   const std::optional<bool>& group_chat_created,
						   const std::optional<bool>& supergroup_chat_created,
						   const std::optional<bool>& channel_chat_created,
						   const std::optional<MessageAutoDeleteTimerChanged>& message_auto_delete_timer_changed,
						   const std::optional<qint32>& migrate_to_chat_id,
						   const std::optional<qint32>& migrate_from_chat_id,
						   const std::optional<std::shared_ptr<Message>>& pinned_message,
						   //const std::optional<Invoice>& invoice,
						   //const std::optional<SuccessfulPayment>& successful_payment,
						   const std::optional<QString>& connected_website,
						   //const std::optional<PassportData>& passport_data,
						   const std::optional<ProximityAlertTriggered>& proximity_alert_triggered,
						   const std::optional<VoiceChatScheduled>& voice_chat_scheduled,
						   const std::optional<VoiceChatStarted>& voice_chat_started,
						   const std::optional<VoiceChatEnded>& voice_chat_ended,
						   const std::optional<VoiceChatParticipantsInvited>& voice_chat_participants_invited,
						   const std::optional<InlineKeyboardMarkup>& reply_markup) :
	message_id(message_id),
	date(date),
	chat(chat),
	from(from),
	sender_chat(sender_chat),
	forward_from(forward_from),
	forward_from_chat(forward_from_chat),
	forward_from_message_id(forward_from_message_id),
	forward_signature(forward_signature),
	forward_sender_name(forward_sender_name),
	forward_date(forward_date),
	reply_to_message(reply_to_message),
	via_bot(via_bot),
	edit_date(edit_date),
	media_group_id(media_group_id),
	author_signature(author_signature),
	text(text),
	entities(entities),
	animation(animation),
	audio(audio),
	document(document),
	photo(photo),
	sticker(sticker),
	video(video),
	video_note(video_note),
	voice(voice),
	caption(caption),
	caption_entities(caption_entities),
	contact(contact),
	dice(dice),
	//game(game),
	poll(poll),
	venue(venue),
	location(location),
	new_chat_members(new_chat_members),
	left_chat_member(left_chat_member),
	new_chat_title(new_chat_title),
	new_chat_photo(new_chat_photo),
	delete_chat_photo(delete_chat_photo),
	group_chat_created(group_chat_created),
	supergroup_chat_created(supergroup_chat_created),
	channel_chat_created(channel_chat_created),
	message_auto_delete_timer_changed(message_auto_delete_timer_changed),
	migrate_to_chat_id(migrate_to_chat_id),
	migrate_from_chat_id(migrate_from_chat_id),
	pinned_message(pinned_message),
	//invoice(invoice),
	//successful_payment(successful_payment),
	connected_website(connected_website),
	//passport_data(passport_data),
	proximity_alert_triggered(proximity_alert_triggered),
	voice_chat_scheduled(voice_chat_scheduled),
	voice_chat_started(voice_chat_started),
	voice_chat_ended(voice_chat_ended),
	voice_chat_participants_invited(voice_chat_participants_invited),
	reply_markup(reply_markup)
{}

Telegram::Message::Message(const QJsonObject& json_object) {
	json_object.contains("message_id")						  ? message_id = json_object["message_id"].toInt()																					: message_id = 0;
	json_object.contains("date")							  ? date = json_object["date"].toInt()																								: date = 0;
	json_object.contains("chat")							  ? chat = std::make_shared<Chat>(json_object["chat"].toObject())																	: chat = std::make_shared<Chat>();
	json_object.contains("from")							  ? from = User(json_object["from"].toObject())																						: from = std::nullopt;
	json_object.contains("sender_chat")						  ? sender_chat = std::make_shared<Chat>(json_object["sender_chat"].toObject())														: sender_chat = std::nullopt;
	json_object.contains("forward_from")					  ? forward_from = User(json_object["forward_from"].toObject())																		: forward_from = std::nullopt;
	json_object.contains("forward_from_chat")				  ? forward_from_chat = std::make_shared<Chat>(json_object["forward_from_chat"].toObject())											: forward_from_chat = std::nullopt;
	json_object.contains("forward_from_message_id")			  ? forward_from_message_id = json_object["forward_from_message_id"].toInt()														: forward_from_message_id = std::nullopt;
	json_object.contains("forward_signature")				  ? forward_signature = json_object["forward_signature"].toString()																	: forward_signature = std::nullopt;
	json_object.contains("forward_sender_name")				  ? forward_sender_name = json_object["forward_sender_name"].toString()																: forward_sender_name = std::nullopt;
	json_object.contains("forward_date")					  ? forward_date = json_object["forward_date"].toInt()																				: forward_date = std::nullopt;
	json_object.contains("reply_to_message")				  ? reply_to_message = std::make_shared<Message>(json_object["reply_to_message"].toObject())										: reply_to_message = std::nullopt;
	json_object.contains("via_bot")							  ? via_bot = User(json_object["via_bot"].toObject())																				: via_bot = std::nullopt;
	json_object.contains("edit_date")						  ? edit_date = json_object["edit_date"].toInt()																					: edit_date = std::nullopt;
	json_object.contains("media_group_id")					  ? media_group_id = json_object["media_group_id"].toString()																		: media_group_id = std::nullopt;
	json_object.contains("author_signature")				  ? author_signature = json_object["author_signature"].toString()																	: author_signature = std::nullopt;
	json_object.contains("text")							  ? text = json_object["text"].toString()																							: text = std::nullopt;										 
	json_object.contains("entities")						  ? entities = Utility::QVectorInserter<MessageEntity>::make(json_object["entities"].toArray())												: entities = std::nullopt;
	json_object.contains("animation")						  ? animation = Animation(json_object["animation"].toObject())																		: animation = std::nullopt;
	json_object.contains("audio")							  ? audio = Audio(json_object["audio"].toObject())																					: audio = std::nullopt;
	json_object.contains("document")						  ? document = Document(json_object["document"].toObject())																			: document = std::nullopt;												 
	json_object.contains("photo")							  ? photo = Utility::QVectorInserter<PhotoSize>::make(json_object["photo"].toArray())															: photo = std::nullopt;
	json_object.contains("sticker")							  ? sticker = Sticker(json_object["sticker"].toObject())																			: sticker = std::nullopt;
	json_object.contains("video")							  ? video = Video(json_object["video"].toObject())																					: video = std::nullopt;
	json_object.contains("video_note")						  ? video_note = VideoNote(json_object["video_note"].toObject())																	: video_note = std::nullopt;
	json_object.contains("voice")							  ? voice = Voice(json_object["voice"].toObject())																					: voice = std::nullopt;
	json_object.contains("caption")							  ? caption = json_object["caption"].toString()																						: caption = std::nullopt;											 
	json_object.contains("caption_entities")				  ? caption_entities = Utility::QVectorInserter<MessageEntity>::make(json_object["caption_entities"].toArray())								: caption_entities = std::nullopt;
	json_object.contains("contact")							  ? contact = Contact(json_object["contact"].toObject())																			: contact = std::nullopt;
	json_object.contains("dice")							  ? dice = Dice(json_object["dice"].toObject())																						: dice = std::nullopt;
	//json_object.contains("game")							  ? game = Game(json_object["game"].toObject())																						: game = std::nullopt;
	json_object.contains("poll")							  ? poll = Poll(json_object["poll"].toObject())																						: poll = std::nullopt;
	json_object.contains("venue")							  ? venue = Venue(json_object["venue"].toObject())																					: venue = std::nullopt;
	json_object.contains("location")						  ? location = Location(json_object["location"].toObject())																			: location = std::nullopt;
	json_object.contains("new_chat_members")				  ? new_chat_members = Utility::QVectorInserter<User>::make(json_object["new_chat_members"].toArray())											: new_chat_members = std::nullopt;
	json_object.contains("left_chat_member")				  ? left_chat_member = User(json_object["left_chat_member"].toObject())																: left_chat_member = std::nullopt;
	json_object.contains("new_chat_title")					  ? new_chat_title = json_object["new_chat_title"].toString()																		: new_chat_title = std::nullopt;												 
	json_object.contains("new_chat_photo")					  ? new_chat_photo = Utility::QVectorInserter<PhotoSize>::make(json_object["new_chat_photo"].toArray())										: new_chat_photo = std::nullopt;
	json_object.contains("delete_chat_photo")				  ? delete_chat_photo = json_object["delete_chat_photo"].toBool()																	: delete_chat_photo = std::nullopt;
	json_object.contains("group_chat_created")				  ? group_chat_created = json_object["group_chat_created"].toBool()																	: group_chat_created = std::nullopt;
	json_object.contains("supergroup_chat_created")			  ? supergroup_chat_created = json_object["supergroup_chat_created"].toBool()														: supergroup_chat_created = std::nullopt;
	json_object.contains("channel_chat_created")			  ? channel_chat_created = json_object["channel_chat_created"].toBool()																: channel_chat_created = std::nullopt;
	json_object.contains("message_auto_delete_timer_changed") ? message_auto_delete_timer_changed = MessageAutoDeleteTimerChanged(json_object["message_auto_delete_timer_changed"].toObject())	: message_auto_delete_timer_changed = std::nullopt;
	json_object.contains("migrate_to_chat_id")				  ? migrate_to_chat_id = json_object["migrate_to_chat_id"].toInteger()																: migrate_to_chat_id = std::nullopt;
	json_object.contains("migrate_from_chat_id")			  ? migrate_from_chat_id = json_object["migrate_from_chat_id"].toInteger()															: migrate_from_chat_id = std::nullopt;
	json_object.contains("pinned_message")					  ? pinned_message = std::make_shared<Message>(json_object["pinned_message"].toObject())											: pinned_message = std::nullopt;
	//json_object.contains("invoice")						  ? invoice = Invoice(json_object["invoice"].toObject())																			: invoice = std::nullopt;
	//json_object.contains("successful_payment")			  ? successful_payment = SuccessfulPayment(json_object["successful_payment"].toObject())											: successful_payment = std::nullopt;
	json_object.contains("connected_website")				  ? connected_website = json_object["connected_website"].toString()																	: connected_website = std::nullopt;
	//json_object.contains("passport_data")					  ? passport_data = PassportData(json_object["passport_data"].toObject())															: passport_data = std::nullopt;
	json_object.contains("proximity_alert_triggered")		  ? proximity_alert_triggered = ProximityAlertTriggered(json_object["proximity_alert_triggered"].toObject())						: proximity_alert_triggered = std::nullopt;
	json_object.contains("voice_chat_scheduled")			  ? voice_chat_scheduled = VoiceChatScheduled(json_object["voice_chat_scheduled"].toObject())										: voice_chat_scheduled = std::nullopt;
	json_object.contains("voice_chat_started")				  ? voice_chat_started = VoiceChatStarted(/*json_object["voice_chat_started"].toObject()*/)											: voice_chat_started = std::nullopt;
	json_object.contains("voice_chat_ended")				  ? voice_chat_ended = VoiceChatEnded(json_object["voice_chat_ended"].toObject())													: voice_chat_ended = std::nullopt;
	json_object.contains("voice_chat_participants_invited")	  ? voice_chat_participants_invited = VoiceChatParticipantsInvited(json_object["voice_chat_participants_invited"].toObject())		: voice_chat_participants_invited = std::nullopt;
	json_object.contains("reply_markup")					  ? reply_markup = InlineKeyboardMarkup(json_object["reply_markup"].toObject())														: reply_markup = std::nullopt;
}

QJsonObject Telegram::Message::toObject() const {
	if (isEmpty()) return {};

	QJsonObject message_json_object{ {"message_id", message_id}, {"date", date}, {"chat", chat->toObject()} };

	if (from.has_value())								message_json_object.insert("from", from->toObject());
	if (sender_chat.has_value())						message_json_object.insert("sender_chat", sender_chat.value()->toObject());
	if (forward_from.has_value())						message_json_object.insert("forward_from", forward_from->toObject());
	if (forward_from_chat.has_value())					message_json_object.insert("forward_from_chat", forward_from_chat.value()->toObject());
	if (forward_from_message_id.has_value())			message_json_object.insert("forward_from_message_id", *forward_from_message_id);
	if (forward_signature.has_value())					message_json_object.insert("forward_signature", *forward_signature);
	if (forward_sender_name.has_value())				message_json_object.insert("forward_sender_name", *forward_sender_name);
	if (forward_date.has_value())						message_json_object.insert("forward_date", *forward_date);
	if (reply_to_message.has_value())					message_json_object.insert("reply_to_message", reply_to_message.value()->toObject());
	if (via_bot.has_value())							message_json_object.insert("via_bot", via_bot->toObject());
	if (edit_date.has_value())							message_json_object.insert("edit_date", *edit_date);
	if (media_group_id.has_value())						message_json_object.insert("media_group_id", *media_group_id);
	if (author_signature.has_value())					message_json_object.insert("author_signature", *author_signature);
	if (text.has_value())								message_json_object.insert("text", *text);
	if (entities.has_value())							message_json_object.insert("entities", Utility::QJsonArrayInserter::make(*entities));
	if (animation.has_value())							message_json_object.insert("animation", animation->toObject());
	if (audio.has_value())								message_json_object.insert("audio", audio->toObject());
	if (document.has_value())							message_json_object.insert("document", document->toObject());
	if (photo.has_value())								message_json_object.insert("photo", Utility::QJsonArrayInserter::make(*photo));
	if (sticker.has_value())							message_json_object.insert("sticker", sticker->toObject());
	if (video.has_value())								message_json_object.insert("video", video->toObject());
	if (video_note.has_value())							message_json_object.insert("video_note", video_note->toObject());
	if (voice.has_value())								message_json_object.insert("voice", voice->toObject());
	if (caption.has_value())							message_json_object.insert("caption", *caption);
	if (caption_entities.has_value())					message_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));
	if (contact.has_value())							message_json_object.insert("contact", contact->toObject());
	if (dice.has_value())								message_json_object.insert("dice", dice->toObject());
	//if (game.has_value())								message_json_object.insert("game", *game);
	if (poll.has_value())								message_json_object.insert("poll", poll->toObject());
	if (venue.has_value())								message_json_object.insert("venue", venue->toObject());
	if (location.has_value())							message_json_object.insert("location", location->toObject());
	if (new_chat_members.has_value())					message_json_object.insert("new_chat_members", Utility::QJsonArrayInserter::make(*new_chat_members));
	if (left_chat_member.has_value())					message_json_object.insert("left_chat_member", left_chat_member->toObject());
	if (new_chat_title.has_value())						message_json_object.insert("new_chat_title", *new_chat_title);
	if (new_chat_photo.has_value())						message_json_object.insert("new_chat_photo", Utility::QJsonArrayInserter::make(*new_chat_photo));
	if (delete_chat_photo.has_value())					message_json_object.insert("delete_chat_photo", *delete_chat_photo);
	if (group_chat_created.has_value())					message_json_object.insert("group_chat_created", *group_chat_created);
	if (supergroup_chat_created.has_value())			message_json_object.insert("supergroup_chat_created", *supergroup_chat_created);
	if (channel_chat_created.has_value())				message_json_object.insert("channel_chat_created", *channel_chat_created);
	if (message_auto_delete_timer_changed.has_value())	message_json_object.insert("message_auto_delete_timer_changed", message_auto_delete_timer_changed->toObject());
	if (migrate_to_chat_id.has_value())					message_json_object.insert("migrate_to_chat_id", *migrate_to_chat_id);
	if (migrate_from_chat_id.has_value())				message_json_object.insert("migrate_from_chat_id", *migrate_from_chat_id);
	if (pinned_message.has_value())						message_json_object.insert("pinned_message", pinned_message.value()->toObject());
	//if (invoice.has_value())							message_json_object.insert("invoice", *invoice);
	//if (successful_payment.has_value())					message_json_object.insert("successful_payment", *successful_payment);
	if (connected_website.has_value())					message_json_object.insert("connected_website", *connected_website);
	//if (passport_data.has_value())						message_json_object.insert("passport_data", *passport_data);
	if (proximity_alert_triggered.has_value())			message_json_object.insert("proximity_alert_triggered", proximity_alert_triggered->toObject());
	if (voice_chat_scheduled.has_value())				message_json_object.insert("voice_chat_scheduled", voice_chat_scheduled->toObject());
	if (voice_chat_started.has_value())					message_json_object.insert("voice_chat_started", voice_chat_started->toObject());
	if (voice_chat_ended.has_value())					message_json_object.insert("voice_chat_ended", voice_chat_ended->toObject());
	if (voice_chat_participants_invited.has_value())	message_json_object.insert("voice_chat_participants_invited", voice_chat_participants_invited->toObject());
	if (reply_markup.has_value())						message_json_object.insert("reply_markup", reply_markup->toObject());

	return message_json_object;
}

bool Telegram::Message::isEmpty() const
{
	return message_id == 0
		   and date == 0
		   and chat == nullptr
		   and from == std::nullopt
		   and sender_chat == std::nullopt
		   and forward_from == std::nullopt
		   and forward_from_chat == std::nullopt
		   and forward_from_message_id == std::nullopt
		   and forward_signature == std::nullopt
		   and forward_sender_name == std::nullopt
		   and forward_date == std::nullopt
		   and reply_to_message == std::nullopt
		   and via_bot == std::nullopt
		   and edit_date == std::nullopt
		   and media_group_id == std::nullopt
		   and author_signature == std::nullopt
		   and text == std::nullopt
		   and entities == std::nullopt
		   and animation == std::nullopt
		   and audio == std::nullopt
		   and document == std::nullopt
		   and photo == std::nullopt
		   and sticker == std::nullopt
		   and video == std::nullopt
		   and video_note == std::nullopt
		   and voice == std::nullopt
		   and caption == std::nullopt
		   and contact == std::nullopt
		   and dice == std::nullopt
		   //and game == std::nullopt
		   and poll == std::nullopt
		   and venue == std::nullopt
		   and location == std::nullopt
		   and left_chat_member == std::nullopt
		   and new_chat_title == std::nullopt
		   and delete_chat_photo == std::nullopt
		   and group_chat_created == std::nullopt
		   and supergroup_chat_created == std::nullopt
		   and channel_chat_created == std::nullopt
		   and migrate_to_chat_id == std::nullopt
		   and migrate_from_chat_id == std::nullopt
		   and pinned_message == std::nullopt
		   //and invoice == std::nullopt
		   //and successful_payment == std::nullopt
		   and connected_website == std::nullopt
		   //and passport_data == std::nullopt
		   and voice_chat_started == std::nullopt
		   and voice_chat_ended == std::nullopt
		   and reply_markup == std::nullopt
		   and new_chat_photo == std::nullopt
		   and new_chat_members == std::nullopt
		   and caption_entities == std::nullopt
		   and message_auto_delete_timer_changed == std::nullopt
		   and voice_chat_scheduled == std::nullopt
		   and proximity_alert_triggered == std::nullopt
		   and voice_chat_participants_invited == std::nullopt;
}

QPair<QString, QVector<Telegram::MessageEntity>> applyFormattingOnString(QString string_to_apply_formatting, QVector<Telegram::MessageEntity> formatting_entities, const Telegram::Message::FormattingType& formatting_type) {
	if (string_to_apply_formatting.isEmpty() == true or formatting_type == Telegram::Message::FormattingType::NULL_ENUMERATOR)
		return {};

	using MessageEntities = QVector<Telegram::MessageEntity>;
	using EntityType = Telegram::MessageEntity::Type;
	using FormattingType = Telegram::Message::FormattingType;

	/* Function that apply formatting rules on string_to_apply_formatting:
	*
	* HTML:
	*	All <, > and & symbols that are not a part of a tag or an HTML entity must be replaced with the corresponding HTML entities (< with &lt;, > with &gt; and & with &amp;)
	*
	* Markdown:
	*	• To escape characters '_', '*', '`', '[' outside of an entity, prepend the characters '\' before them.
	*	• Escaping inside entities is not allowed, so entity must be closed first and reopened again: use _snake_\__case_ for italic snake_case and *2*\**2=4* for bold 2*2=4.
	*
	* MarkdownV2:
	*	• Any character with code between 1 and 126 inclusively can be escaped anywhere with a preceding '\' character, in which case it is treated as an ordinary character and not a part of the markup. This implies that '\' character usually must be escaped with a preceding '\' character.
	*	• Inside pre and code entities, all '`' and '\' characters must be escaped with a preceding '\' character.
	*	• Inside (...) part of inline link definition, all ')' and '\' must be escaped with a preceding '\' character.
	*	• In all other places characters '_', '*', '[', ']', '(', ')', '~', '`', '>', '#', '+', '-', '=', '|', '{', '}', '.', '!' must be escaped with the preceding character '\'.
	*/
	auto applyFormattingRules = [](auto& string_to_apply_formatting, auto& formatting_entities, auto& formatting_type) {
		auto isInsideOfAnyEntity = [](const auto& character_index, MessageEntities& formatting_entities) {
			for (auto&& formatting_entity_iterator = formatting_entities.begin(); formatting_entity_iterator != formatting_entities.end(); formatting_entity_iterator++) {
				if (character_index >= formatting_entity_iterator->offset and character_index < formatting_entity_iterator->offset + formatting_entity_iterator->length)
					return formatting_entity_iterator;
			}
			return formatting_entities.end();
		};

		if (formatting_type == FormattingType::HTML) {

			for (auto&& character_to_escape : { std::make_pair<QString, QString>("<", "&lt"), std::make_pair<QString, QString>(">", "&gt"), std::make_pair<QString, QString>("&", "&amp") }) {
				for (auto&& character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape.first); character_to_escape_index != -1; character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape.first, character_to_escape.second.size() - 1)) {

					string_to_apply_formatting = string_to_apply_formatting.replace(character_to_escape_index, 1, character_to_escape.second);
					std::ranges::for_each(formatting_entities, [&](auto& formatting_entity) {
						if (formatting_entity.offset > character_to_escape_index)
							formatting_entity.offset += character_to_escape.second.size() - character_to_escape.first.size();
						});
				}
			}

		}
		else if (formatting_type == FormattingType::Markdown) {

			for (auto&& character_to_escape : { '_', '*', '`', '[' }) {
				for (auto&& character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape); character_to_escape_index != -1;) {

					if (auto entity_iterator = isInsideOfAnyEntity(character_to_escape_index, formatting_entities); entity_iterator != formatting_entities.end()
						and ((character_to_escape == '_' and entity_iterator->type == EntityType::ITALIC) or (character_to_escape == '*' and entity_iterator->type == EntityType::BOLD) or (character_to_escape == '`' and entity_iterator->type == EntityType::CODE)))
					{
						string_to_apply_formatting = string_to_apply_formatting.replace(character_to_escape_index, 1, QStringLiteral("%1\\%2%3").arg(character_to_escape).arg(character_to_escape).arg(character_to_escape));
						entity_iterator->length += 3;
						std::for_each(++entity_iterator, formatting_entities.end(), [](auto& formatting_entity) { formatting_entity.offset += 3; });
						character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape, character_to_escape_index + 4);
					}
					else {
						string_to_apply_formatting = string_to_apply_formatting.replace(character_to_escape_index, 1, QStringLiteral("\\%1").arg(character_to_escape));
						std::ranges::for_each(formatting_entities, [&](auto& formatting_entity) { if (formatting_entity.offset > character_to_escape_index) formatting_entity.offset += 1; });
						character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape, character_to_escape_index + 2);
					}
				}
			}
		}
		else if (formatting_type == FormattingType::MarkdownV2) {

			for (auto&& character_to_escape_index = string_to_apply_formatting.indexOf('\\'); character_to_escape_index != -1; character_to_escape_index = string_to_apply_formatting.indexOf('\\', character_to_escape_index + 2)) {

				if (auto entity_iterator = isInsideOfAnyEntity(character_to_escape_index, formatting_entities); entity_iterator != formatting_entities.end()
					and (entity_iterator->type == EntityType::PRE or entity_iterator->type == EntityType::CODE or (entity_iterator->type == EntityType::TEXT_LINK and entity_iterator->url->contains('\\'))))
				{
					string_to_apply_formatting = string_to_apply_formatting.insert(character_to_escape_index, "\\");
					entity_iterator->length += 1;
					std::for_each(++entity_iterator, formatting_entities.end(), [](auto& formatting_entity) { formatting_entity.offset += 1; });
				}
			}

			for (auto&& character_to_escape : { '_', '*', '[', ']', '(', ')', '~', '`', '>', '#', '+', '-', '=', '|', '{', '}', '.', '!' }) {
				for (auto&& character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape); character_to_escape_index != -1; character_to_escape_index = string_to_apply_formatting.indexOf(character_to_escape, character_to_escape_index + 2)) {

					string_to_apply_formatting = string_to_apply_formatting.insert(character_to_escape_index, '\\');
					if (auto entity_iterator = isInsideOfAnyEntity(character_to_escape_index, formatting_entities); entity_iterator != formatting_entities.end()) { entity_iterator->length += 1; }
					std::ranges::for_each(formatting_entities, [&](auto& formatting_entity) { if (formatting_entity.offset > character_to_escape_index) formatting_entity.offset += 1; });
				}
			}
		}
	};

	/* Function that insert fromatting_entities in string_to_apply_formatting. e.g. { {EntityType::BOLD, 0, 12} } -> "<b>example_text</b>" */
	auto insertFormattingEntities = [](auto& string_to_apply_formatting, auto& formatting_entities, auto& formatting_type) {
		for (auto formatting_entity_iterator = formatting_entities.begin(); formatting_entity_iterator != formatting_entities.end(); formatting_entity_iterator++) {

			auto insertFormattingEntity = [&string_to_apply_formatting, &formatting_entities](auto formatting_entity_iterator, const QString& entity_begin_string, const QString& entity_end_string) {
				string_to_apply_formatting = string_to_apply_formatting.insert(formatting_entity_iterator->offset + formatting_entity_iterator->length, entity_end_string)
																	   .insert(formatting_entity_iterator->offset, entity_begin_string);
				std::ranges::for_each(formatting_entity_iterator + 1, formatting_entities.end(), [&](auto& formatting_entity) {
					if (formatting_entity.offset >= formatting_entity_iterator->offset + formatting_entity_iterator->length)
						formatting_entity.offset += entity_begin_string.count() + entity_end_string.count();
					else if (formatting_entity.offset >= formatting_entity_iterator->offset)
						formatting_entity.offset += entity_begin_string.count();
					});
				formatting_entity_iterator->length += entity_begin_string.count() + entity_end_string.count();

			};

			if (formatting_entity_iterator->type == EntityType::BOLD) {
				if		(formatting_type == FormattingType::HTML)														insertFormattingEntity(formatting_entity_iterator, "<b>", "</b>");
				else if (formatting_type == FormattingType::Markdown or formatting_type == FormattingType::MarkdownV2)	insertFormattingEntity(formatting_entity_iterator, "*", "*");
			}
			else if (formatting_entity_iterator->type == EntityType::ITALIC) {
				if		(formatting_type == FormattingType::HTML)														insertFormattingEntity(formatting_entity_iterator, "<i>", "</i>");
				else if (formatting_type == FormattingType::Markdown or formatting_type == FormattingType::MarkdownV2)	insertFormattingEntity(formatting_entity_iterator, "_", "_\r");
			}
			else if (formatting_entity_iterator->type == EntityType::UNDERLINE) {
				if		(formatting_type == FormattingType::HTML)		insertFormattingEntity(formatting_entity_iterator, "<u>", "</u>");
				else if (formatting_type == FormattingType::MarkdownV2) insertFormattingEntity(formatting_entity_iterator, "__", "__");
			}
			else if (formatting_entity_iterator->type == EntityType::STRIKETHROUGH) {
				if		(formatting_type == FormattingType::HTML)		insertFormattingEntity(formatting_entity_iterator, "<s>", "</s>");
				else if (formatting_type == FormattingType::MarkdownV2) insertFormattingEntity(formatting_entity_iterator, "~", "~");
			}
			else if (formatting_entity_iterator->type == EntityType::SPOILER) {
				if		(formatting_type == FormattingType::HTML)		insertFormattingEntity(formatting_entity_iterator, "<tg-spoiler>", "</tg-spoiler>");
				else if (formatting_type == FormattingType::MarkdownV2) insertFormattingEntity(formatting_entity_iterator, "||", "||");
			}
			else if (formatting_entity_iterator->type == EntityType::CODE) {
				if		(formatting_type == FormattingType::HTML)														insertFormattingEntity(formatting_entity_iterator, "<code>", "</code>");
				else if (formatting_type == FormattingType::Markdown or formatting_type == FormattingType::MarkdownV2)	insertFormattingEntity(formatting_entity_iterator, "`", "`");
			}
			else if (formatting_entity_iterator->type == EntityType::PRE) {
				if		(formatting_type == FormattingType::HTML)														insertFormattingEntity(formatting_entity_iterator, "<pre>", "</pre>");
				else if (formatting_type == FormattingType::Markdown or formatting_type == FormattingType::MarkdownV2)  insertFormattingEntity(formatting_entity_iterator, "```", "```");
			}
			else if (formatting_entity_iterator->type == EntityType::TEXT_LINK) {
				if		(formatting_type == FormattingType::HTML)														insertFormattingEntity(formatting_entity_iterator, QStringLiteral("<a href=\"%1\">").arg(*formatting_entity_iterator->url), "</a>");
				else if (formatting_type == FormattingType::Markdown or formatting_type == FormattingType::MarkdownV2)	insertFormattingEntity(formatting_entity_iterator, "[", QStringLiteral("](%1)").arg(*formatting_entity_iterator->url));
			}
			else if (formatting_entity_iterator->type == EntityType::TEXT_MENTION) {
				if		(formatting_type == FormattingType::HTML)														insertFormattingEntity(formatting_entity_iterator, QStringLiteral("<a href=\"tg://user?id=%1\">").arg(formatting_entity_iterator->user->id), "</a>");
				else if (formatting_type == FormattingType::Markdown or formatting_type == FormattingType::MarkdownV2)	insertFormattingEntity(formatting_entity_iterator, "[", QStringLiteral("](%1)").arg(formatting_entity_iterator->user->id));
			}
		}
	};

	applyFormattingRules(string_to_apply_formatting, formatting_entities, formatting_type);
	if(formatting_entities.isEmpty() == false) insertFormattingEntities(string_to_apply_formatting, formatting_entities, formatting_type);

	return std::make_pair( std::move(string_to_apply_formatting), std::move(formatting_entities) );
}

QPair<QString, QVector<Telegram::MessageEntity>> Telegram::Message::getTextWithFormatting(const FormattingType& formatting_type) const {
	if (text.has_value() == false) return {};

	return applyFormattingOnString(*text, entities.value_or(QVector<Telegram::MessageEntity>()), formatting_type);
}

QPair<QString, QVector<Telegram::MessageEntity>> Telegram::Message::getCaptionWithFormatting(const FormattingType& formatting_type) const {
	if (caption.has_value() == false) return {};

	return applyFormattingOnString(*caption, caption_entities.value_or(QVector<Telegram::MessageEntity>()), formatting_type);
}
