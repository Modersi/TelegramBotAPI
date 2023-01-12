#include "Types/PollOption.h"

Telegram::PollOption::PollOption() :
	text(),
	voter_count()
{}

Telegram::PollOption::PollOption(const QString& text,
								 const qint32& voter_count) :
	text(text),
	voter_count(voter_count)
{}

Telegram::PollOption::PollOption(const QJsonObject& json_object) {
	json_object.contains("text")		? text = json_object["text"].toString()				: text = "";
	json_object.contains("voter_count")	? voter_count = json_object["voter_count"].toInt()	: voter_count = 0;
}

QJsonObject Telegram::PollOption::toObject() const {
	if (isEmpty()) return {};

	return { {"text", text}, {"voter_count", voter_count} };
}

bool Telegram::PollOption::isEmpty() const {
	return text == "" and voter_count == 0;
}
