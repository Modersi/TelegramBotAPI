#include "Types/PollOption.h"

#include "qjsonobject.h"

Telegram::PollOption::PollOption() :
	text(),
	voter_count()
{}

Telegram::PollOption::PollOption(const QString& text,
								 const qint32& voter_count) :
	text(text),
	voter_count(voter_count)
{}

Telegram::PollOption::PollOption(const QJsonObject& jsonObject)
{
	jsonObject.contains("text")			? text = jsonObject["text"].toString()			  : text = "";
	jsonObject.contains("voter_count")	? voter_count = jsonObject["voter_count"].toInt() : voter_count = 0;
}

QJsonObject Telegram::PollOption::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"text", text}, {"voter_count", voter_count} };
}

bool Telegram::PollOption::isEmpty() const
{
	return text == "" and voter_count == 0;
}
