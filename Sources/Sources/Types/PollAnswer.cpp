#include "Types/PollAnswer.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

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

Telegram::PollAnswer::PollAnswer(const QJsonObject& jsonObject)
{
	jsonObject.contains("poll_id")	  ? poll_id = jsonObject["poll_id"].toString()							   : poll_id = "";
	jsonObject.contains("user")		  ? user = User(jsonObject["user"].toObject())							   : user = User();
	jsonObject.contains("option_ids") ? option_ids = QJsonArrayToQVector<qint32>(jsonObject["option_ids"].toArray()) : option_ids = QVector<qint32>();
}

QJsonObject Telegram::PollAnswer::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"poll_id", poll_id}, {"user", user.toObject()}, {"option_ids", QVectorToQJsonArray(option_ids)} };
}

bool Telegram::PollAnswer::isEmpty() const
{
	return poll_id == "" and user.isEmpty() and option_ids.isEmpty();
}
