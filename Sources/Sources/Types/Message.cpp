#include "Types/Chat.h"
#include "Types/Message.h"
#include "Internal/ConversionFunctions.h"

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

Telegram::Message::Message(const QJsonObject& jsonObject)
{
	jsonObject.contains("message_id")						 ? message_id = jsonObject["message_id"].toInt()										: message_id = 0;
	jsonObject.contains("date")								 ? date = jsonObject["date"].toInt()													: date = 0;
	jsonObject.contains("chat")								 ? chat = std::make_shared<Chat>(jsonObject["chat"].toObject())							: chat = std::make_shared<Chat>();
	jsonObject.contains("from")								 ? from = User(jsonObject["from"].toObject())											: from = std::nullopt;
	jsonObject.contains("sender_chat")						 ? sender_chat = std::make_shared<Chat>(jsonObject["sender_chat"].toObject())			: sender_chat = std::nullopt;
	jsonObject.contains("forward_from")						 ? forward_from = User(jsonObject["forward_from"].toObject())							: forward_from = std::nullopt;
	jsonObject.contains("forward_from_chat")				 ? forward_from_chat = std::make_shared<Chat>(jsonObject["forward_from_chat"].toObject()) : forward_from_chat = std::nullopt;
	jsonObject.contains("forward_from_message_id")			 ? forward_from_message_id = jsonObject["forward_from_message_id"].toInt()				: forward_from_message_id = std::nullopt;
	jsonObject.contains("forward_signature")				 ? forward_signature = jsonObject["forward_signature"].toString()						: forward_signature = std::nullopt;
	jsonObject.contains("forward_sender_name")				 ? forward_sender_name = jsonObject["forward_sender_name"].toString()					: forward_sender_name = std::nullopt;
	jsonObject.contains("forward_date")						 ? forward_date = jsonObject["forward_date"].toInt()									: forward_date = std::nullopt;
	jsonObject.contains("reply_to_message")					 ? reply_to_message = std::make_shared<Message>(jsonObject["reply_to_message"].toObject()) : reply_to_message = std::nullopt;
	jsonObject.contains("via_bot")							 ? via_bot = User(jsonObject["via_bot"].toObject())										: via_bot = std::nullopt;
	jsonObject.contains("edit_date")						 ? edit_date = jsonObject["edit_date"].toInt()											: edit_date = std::nullopt;
	jsonObject.contains("media_group_id")					 ? media_group_id = jsonObject["media_group_id"].toString()								: media_group_id = std::nullopt;
	jsonObject.contains("author_signature")					 ? author_signature = jsonObject["author_signature"].toString()							: author_signature = std::nullopt;
	jsonObject.contains("text")								 ? text = jsonObject["text"].toString()													: text = std::nullopt;										 
	jsonObject.contains("entities")							 ? entities = QJsonArrayToQVector<MessageEntity>(jsonObject["entities"].toArray())		: entities = std::nullopt;
	jsonObject.contains("animation")						 ? animation = Animation(jsonObject["animation"].toObject())							: animation = std::nullopt;
	jsonObject.contains("audio")							 ? audio = Audio(jsonObject["audio"].toObject())										: audio = std::nullopt;
	jsonObject.contains("document")							 ? document = Document(jsonObject["document"].toObject())								: document = std::nullopt;												 
	jsonObject.contains("photo")							 ? photo = QJsonArrayToQVector<PhotoSize>(jsonObject["photo"].toArray())				: photo = std::nullopt;
	jsonObject.contains("sticker")							 ? sticker = Sticker(jsonObject["sticker"].toObject())									: sticker = std::nullopt;
	jsonObject.contains("video")							 ? video = Video(jsonObject["video"].toObject())										: video = std::nullopt;
	jsonObject.contains("video_note")						 ? video_note = VideoNote(jsonObject["video_note"].toObject())							: video_note = std::nullopt;
	jsonObject.contains("voice")							 ? voice = Voice(jsonObject["voice"].toObject())										: voice = std::nullopt;
	jsonObject.contains("caption")							 ? caption = jsonObject["caption"].toString()											: caption = std::nullopt;											 
	jsonObject.contains("contact")							 ? contact = Contact(jsonObject["contact"].toObject())									: contact = std::nullopt;
	jsonObject.contains("dice")								 ? dice = Dice(jsonObject["dice"].toObject())											: dice = std::nullopt;
	//jsonObject.contains("game")								 ? game = Game(jsonObject["game"].toObject())											: game = std::nullopt;
	jsonObject.contains("poll")								 ? poll = Poll(jsonObject["poll"].toObject())											: poll = std::nullopt;
	jsonObject.contains("venue")							 ? venue = Venue(jsonObject["venue"].toObject())										: venue = std::nullopt;
	jsonObject.contains("location")							 ? location = Location(jsonObject["location"].toObject())								: location = std::nullopt;
	jsonObject.contains("left_chat_member")					 ? left_chat_member = User(jsonObject["left_chat_member"].toObject())					: left_chat_member = std::nullopt;
	jsonObject.contains("new_chat_title")					 ? new_chat_title = jsonObject["new_chat_title"].toString()								: new_chat_title = std::nullopt;												 
	jsonObject.contains("delete_chat_photo")				 ? delete_chat_photo = jsonObject["delete_chat_photo"].toBool()							: delete_chat_photo = std::nullopt;
	jsonObject.contains("group_chat_created")				 ? group_chat_created = jsonObject["group_chat_created"].toBool()						: group_chat_created = std::nullopt;
	jsonObject.contains("supergroup_chat_created")			 ? supergroup_chat_created = jsonObject["supergroup_chat_created"].toBool()				: supergroup_chat_created = std::nullopt;
	jsonObject.contains("channel_chat_created")				 ? channel_chat_created = jsonObject["channel_chat_created"].toBool()					: channel_chat_created = std::nullopt;
	jsonObject.contains("migrate_to_chat_id")				 ? migrate_to_chat_id = jsonObject["migrate_to_chat_id"].toInt()						: migrate_to_chat_id = std::nullopt;
	jsonObject.contains("migrate_from_chat_id")				 ? migrate_from_chat_id = jsonObject["migrate_from_chat_id"].toInt()					: migrate_from_chat_id = std::nullopt;
	jsonObject.contains("pinned_message")					 ? pinned_message = std::make_shared<Message>(jsonObject["pinned_message"].toObject())  : pinned_message = std::nullopt;
	//jsonObject.contains("invoice")							 ? invoice = Invoice(jsonObject["invoice"].toObject())									: invoice = std::nullopt;
	//jsonObject.contains("successful_payment")				 ? successful_payment = SuccessfulPayment(jsonObject["successful_payment"].toObject())  : successful_payment = std::nullopt;
	jsonObject.contains("connected_website")				 ? connected_website = jsonObject["connected_website"].toString()						: connected_website = std::nullopt;
	//jsonObject.contains("passport_data")					 ? passport_data = PassportData(jsonObject["passport_data"].toObject())					: passport_data = std::nullopt;
	jsonObject.contains("voice_chat_started")				 ? voice_chat_started = VoiceChatStarted(/*jsonObject["voice_chat_started"].toObject()*/)   : voice_chat_started = std::nullopt;
	jsonObject.contains("voice_chat_ended")					 ? voice_chat_ended = VoiceChatEnded(jsonObject["voice_chat_ended"].toObject())		    : voice_chat_ended = std::nullopt;
	jsonObject.contains("reply_markup")						 ? reply_markup = InlineKeyboardMarkup(jsonObject["reply_markup"].toObject())			: reply_markup = std::nullopt;
	jsonObject.contains("new_chat_photo")					 ? new_chat_photo = QJsonArrayToQVector<PhotoSize>(jsonObject["new_chat_photo"].toArray())										 : new_chat_photo = std::nullopt;
	jsonObject.contains("new_chat_members")					 ? new_chat_members = QJsonArrayToQVector<User>(jsonObject["new_chat_members"].toArray())										 : new_chat_members = std::nullopt;
	jsonObject.contains("caption_entities")					 ? caption_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["caption_entities"].toArray())								 : caption_entities = std::nullopt;
	jsonObject.contains("message_auto_delete_timer_changed") ? message_auto_delete_timer_changed = MessageAutoDeleteTimerChanged(jsonObject["message_auto_delete_timer_changed"].toObject()) : message_auto_delete_timer_changed = std::nullopt;
	jsonObject.contains("voice_chat_scheduled")				 ? voice_chat_scheduled = VoiceChatScheduled(jsonObject["voice_chat_scheduled"].toObject())										 : voice_chat_scheduled = std::nullopt;
	jsonObject.contains("proximity_alert_triggered")		 ? proximity_alert_triggered = ProximityAlertTriggered(jsonObject["proximity_alert_triggered"].toObject())						 : proximity_alert_triggered = std::nullopt;
	jsonObject.contains("voice_chat_participants_invited")	 ? voice_chat_participants_invited = VoiceChatParticipantsInvited(jsonObject["voice_chat_participants_invited"].toObject())		 : voice_chat_participants_invited = std::nullopt;
}

QJsonObject Telegram::Message::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject messageJsonObject{ {"message_id", message_id}, {"date", date}, {"chat", chat->toObject()} };

	if (from.has_value())								messageJsonObject.insert("from", from->toObject());
	if (sender_chat.has_value())						messageJsonObject.insert("sender_chat", sender_chat.value()->toObject());
	if (forward_from.has_value())						messageJsonObject.insert("forward_from", forward_from->toObject());
	if (forward_from_chat.has_value())					messageJsonObject.insert("forward_from_chat", forward_from_chat.value()->toObject());
	if (forward_from_message_id.has_value())			messageJsonObject.insert("forward_from_message_id", *forward_from_message_id);
	if (forward_signature.has_value())					messageJsonObject.insert("forward_signature", *forward_signature);
	if (forward_sender_name.has_value())				messageJsonObject.insert("forward_sender_name", *forward_sender_name);
	if (forward_date.has_value())						messageJsonObject.insert("forward_date", *forward_date);
	if (reply_to_message.has_value())					messageJsonObject.insert("reply_to_message", reply_to_message.value()->toObject());
	if (via_bot.has_value())							messageJsonObject.insert("via_bot", via_bot->toObject());
	if (edit_date.has_value())							messageJsonObject.insert("edit_date", *edit_date);
	if (media_group_id.has_value())						messageJsonObject.insert("media_group_id", *media_group_id);
	if (author_signature.has_value())					messageJsonObject.insert("author_signature", *author_signature);
	if (text.has_value())								messageJsonObject.insert("text", *text);
	if (entities.has_value())							messageJsonObject.insert("entities", QVectorToQJsonArray(*entities));
	if (animation.has_value())							messageJsonObject.insert("animation", animation->toObject());
	if (audio.has_value())								messageJsonObject.insert("audio", audio->toObject());
	if (document.has_value())							messageJsonObject.insert("document", document->toObject());
	if (photo.has_value())								messageJsonObject.insert("photo", QVectorToQJsonArray(*photo));
	if (sticker.has_value())							messageJsonObject.insert("sticker", sticker->toObject());
	if (video.has_value())								messageJsonObject.insert("video", video->toObject());
	if (video_note.has_value())							messageJsonObject.insert("video_note", video_note->toObject());
	if (voice.has_value())								messageJsonObject.insert("voice", voice->toObject());
	if (caption.has_value())							messageJsonObject.insert("caption", *caption);
	if (caption_entities.has_value())					messageJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (contact.has_value())							messageJsonObject.insert("contact", contact->toObject());
	if (dice.has_value())								messageJsonObject.insert("dice", dice->toObject());
	//if (game.has_value())								messageJsonObject.insert("game", *game);
	if (poll.has_value())								messageJsonObject.insert("poll", poll->toObject());
	if (venue.has_value())								messageJsonObject.insert("venue", venue->toObject());
	if (location.has_value())							messageJsonObject.insert("location", location->toObject());
	if (new_chat_members.has_value())					messageJsonObject.insert("new_chat_members", QVectorToQJsonArray(*new_chat_members));
	if (left_chat_member.has_value())					messageJsonObject.insert("left_chat_member", left_chat_member->toObject());
	if (new_chat_title.has_value())						messageJsonObject.insert("new_chat_title", *new_chat_title);
	if (new_chat_photo.has_value())						messageJsonObject.insert("new_chat_photo", QVectorToQJsonArray(*new_chat_photo));
	if (delete_chat_photo.has_value())					messageJsonObject.insert("delete_chat_photo", *delete_chat_photo);
	if (group_chat_created.has_value())					messageJsonObject.insert("group_chat_created", *group_chat_created);
	if (supergroup_chat_created.has_value())			messageJsonObject.insert("supergroup_chat_created", *supergroup_chat_created);
	if (channel_chat_created.has_value())				messageJsonObject.insert("channel_chat_created", *channel_chat_created);
	if (message_auto_delete_timer_changed.has_value())	messageJsonObject.insert("message_auto_delete_timer_changed", message_auto_delete_timer_changed->toObject());
	if (migrate_to_chat_id.has_value())					messageJsonObject.insert("migrate_to_chat_id", *migrate_to_chat_id);
	if (migrate_from_chat_id.has_value())				messageJsonObject.insert("migrate_from_chat_id", *migrate_from_chat_id);
	if (pinned_message.has_value())						messageJsonObject.insert("pinned_message", pinned_message.value()->toObject());
	//if (invoice.has_value())							messageJsonObject.insert("invoice", *invoice);
	//if (successful_payment.has_value())					messageJsonObject.insert("successful_payment", *successful_payment);
	if (connected_website.has_value())					messageJsonObject.insert("connected_website", *connected_website);
	//if (passport_data.has_value())						messageJsonObject.insert("passport_data", *passport_data);
	if (proximity_alert_triggered.has_value())			messageJsonObject.insert("proximity_alert_triggered", proximity_alert_triggered->toObject());
	if (voice_chat_scheduled.has_value())				messageJsonObject.insert("voice_chat_scheduled", voice_chat_scheduled->toObject());
	if (voice_chat_started.has_value())					messageJsonObject.insert("voice_chat_started", voice_chat_started->toObject());
	if (voice_chat_ended.has_value())					messageJsonObject.insert("voice_chat_ended", voice_chat_ended->toObject());
	if (voice_chat_participants_invited.has_value())	messageJsonObject.insert("voice_chat_participants_invited", voice_chat_participants_invited->toObject());
	if (reply_markup.has_value())						messageJsonObject.insert("reply_markup", reply_markup->toObject());

	return messageJsonObject;
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
