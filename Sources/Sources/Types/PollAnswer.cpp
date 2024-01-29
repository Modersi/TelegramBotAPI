#include "Types/PollAnswer.h"

#include "qjsonarray.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

Telegram::PollAnswer::PollAnswer() :
	poll_id(),
	user(),
	option_ids()
{}

Telegram::PollAnswer::PollAnswer(const QString& poll_id,
								 const User& user,
								 const QVector<qint32>& option_ids) :
	poll_id(poll_id),
	user(user),
	option_ids(option_ids)
{}

Telegram::PollAnswer::PollAnswer(const QJsonObject& json_object) {
	json_object.contains("poll_id")		? poll_id = json_object["poll_id"].toString()									: poll_id = "";
	json_object.contains("user")		? user = User(json_object["user"].toObject())									: user = User();
	json_object.contains("option_ids")	? option_ids = Utility::QVectorInserter<qint32>::make(json_object["option_ids"].toArray())	: option_ids = QVector<qint32>();
}

QJsonObject Telegram::PollAnswer::toObject() const {
	if (isEmpty()) return {};

	return { {"poll_id", poll_id}, {"user", user.toObject()}, {"option_ids", Utility::QJsonArrayInserter::make(option_ids)} };
}

bool Telegram::PollAnswer::isEmpty() const {
	return poll_id == "" and user.isEmpty() and option_ids.isEmpty();
}
