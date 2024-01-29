#include "Types/Poll.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::Poll::Poll() :
	id(),
	question(),
	options(),
	total_voter_count(),
	is_closed(),
	is_anonymous(),
	type(),
	allows_multiple_answers(),
	correct_option_id(),
	explanation(),
	explanation_entities(),
	open_period(),
	close_date()
{
}

Telegram::Poll::Poll(const QString& id,
					 const QString& question,
					 const QVector<PollOption>& options,
					 const qint32& total_voter_count,
					 const bool& is_closed,
					 const bool& is_anonymous,
					 const Type& type,
					 const bool& allows_multiple_answers,
					 const std::optional<qint32>& correct_option_id,
					 const std::optional<QString>& explanation,
					 const std::optional<QVector<MessageEntity>>& explanation_entities,
					 const std::optional<qint32>& open_period,
					 const std::optional<qint32>& close_date) :
	id(id),
	question(question),
	options(options),
	total_voter_count(total_voter_count),
	is_closed(is_closed),
	is_anonymous(is_anonymous),
	type(type),
	allows_multiple_answers(allows_multiple_answers),
	correct_option_id(correct_option_id),
	explanation(explanation),
	explanation_entities(explanation_entities),
	open_period(open_period),
	close_date(close_date)
{}

Telegram::Poll::Poll(const QJsonObject& json_object) {
	json_object.contains("id")						? id = json_object["id"].toString()																										 : id = "";
	json_object.contains("question")				? question = json_object["question"].toString()																							 : question = "";																												   
	json_object.contains("options")					? options = Utility::QVectorInserter<PollOption>::make(json_object["options"].toArray())												 : options = QVector<PollOption>();
	json_object.contains("total_voter_count")		? total_voter_count = json_object["total_voter_count"].toInt()																			 : total_voter_count = 0;
	json_object.contains("is_closed")				? is_closed = json_object["is_closed"].toBool()																							 : is_closed = false;
	json_object.contains("is_anonymous")			? is_anonymous = json_object["is_anonymous"].toBool()																					 : is_anonymous = false;
	json_object.contains("type")					? type = static_cast<decltype(type)>(QMetaEnum::fromType<decltype(type)>().keyToValue(json_object["type"].toString().toUpper().toUtf8())) : type = decltype(type)::NULL_ENUMERATOR;
	json_object.contains("allows_multiple_answers")	? allows_multiple_answers = json_object["allows_multiple_answers"].toBool()																 : allows_multiple_answers = false;
	json_object.contains("correct_option_id")		? correct_option_id = json_object["correct_option_id"].toInt()																			 : correct_option_id = std::nullopt;
	json_object.contains("explanation")				? explanation = json_object["explanation"].toString()																					 : explanation = std::nullopt;
	json_object.contains("explanation_entities")	? explanation_entities = Utility::QVectorInserter<MessageEntity>::make(json_object["explanation_entities"].toArray())					 : explanation_entities = std::nullopt;
	json_object.contains("open_period")				? open_period = json_object["open_period"].toInt()																						 : open_period = std::nullopt;
	json_object.contains("close_date")				? close_date = json_object["close_date"].toInt()																						 : close_date = std::nullopt;
}

QJsonObject Telegram::Poll::toObject() const {
	if (isEmpty()) return {};

	QJsonObject poll_json_object{ {"id", id}, {"question", question}, {"options", Utility::QJsonArrayInserter::make(options)}, {"total_voter_count", total_voter_count},
								{"is_closed", is_closed}, {"is_anonymous", is_anonymous}, {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"allows_multiple_answers", allows_multiple_answers} };

	if (correct_option_id.has_value())		poll_json_object.insert("correct_option_id", *correct_option_id);
	if (explanation.has_value())			poll_json_object.insert("explanation", *explanation);
	if (explanation_entities.has_value())	poll_json_object.insert("explanation_entities", Utility::QJsonArrayInserter::make(*explanation_entities));
	if (open_period.has_value())			poll_json_object.insert("open_period", *open_period);
	if (close_date.has_value())				poll_json_object.insert("close_date", *close_date);

	return poll_json_object;
}

bool Telegram::Poll::isEmpty() const {
	return id == ""
		   and question == ""
		   and options.isEmpty()
		   and total_voter_count == 0
		   and is_closed == false
		   and is_anonymous == false
		   and type == decltype(type)::NULL_ENUMERATOR
		   and allows_multiple_answers == false
		   and correct_option_id == std::nullopt
		   and explanation == std::nullopt
		   and explanation_entities == std::nullopt
		   and open_period == std::nullopt
		   and close_date == std::nullopt;
}
