#include "Types/Poll.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::Poll::Poll() :
	id(""),
	question(""),
	options(QVector<PollOption>()),
	total_voter_count(0),
	is_closed(false),
	is_anonymous(false),
	type(Type::UNINITIALIZED_VALUE),
	allows_multiple_answers(false),
	correct_option_id(std::nullopt),
	explanation(std::nullopt),
	explanation_entities(std::nullopt),
	open_period(std::nullopt),
	close_date(std::nullopt)
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

Telegram::Poll::Poll(const QJsonObject& jsonObject)
{
	auto GetPollType = [](const QJsonValue& pollType) -> Poll::Type
								{
									if (pollType == "quiz") return Type::QUIZ;
									if (pollType == "regular") return Type::REGULAR;
									else return Type::UNINITIALIZED_VALUE;
								};

	jsonObject.contains("id")						? id = jsonObject["id"].toString()																		   : id = "";
	jsonObject.contains("question")					? question = jsonObject["question"].toString()															   : question = "";																												   
	jsonObject.contains("options")					? options = QJsonArrayToQVector<PollOption>(jsonObject["options"].toArray())							   : options = QVector<PollOption>();
	jsonObject.contains("total_voter_count")		? total_voter_count = jsonObject["total_voter_count"].toInt()											   : total_voter_count = 0;
	jsonObject.contains("is_closed")				? is_closed = jsonObject["is_closed"].toBool()															   : is_closed = false;
	jsonObject.contains("is_anonymous")				? is_anonymous = jsonObject["is_anonymous"].toBool()													   : is_anonymous = false;
	jsonObject.contains("type")						? type = GetPollType(jsonObject["type"])																   : type = Type::UNINITIALIZED_VALUE;
	jsonObject.contains("allows_multiple_answers")	? allows_multiple_answers = jsonObject["allows_multiple_answers"].toBool()								   : allows_multiple_answers = false;
	jsonObject.contains("correct_option_id")		? correct_option_id = jsonObject["correct_option_id"].toInt()											   : correct_option_id = std::nullopt;
	jsonObject.contains("explanation")				? explanation = jsonObject["explanation"].toString()													   : explanation = std::nullopt;
	jsonObject.contains("explanation_entities")		? explanation_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["explanation_entities"].toArray())  : explanation_entities = std::nullopt;
	jsonObject.contains("open_period")				? open_period = jsonObject["open_period"].toInt()														   : open_period = std::nullopt;
	jsonObject.contains("close_date")				? close_date = jsonObject["close_date"].toInt()															   : close_date = std::nullopt;
}

QJsonObject Telegram::Poll::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	auto GetPollTypeInString = [](const Poll::Type& pollType) -> QString
								{
									if (pollType == Type::QUIZ) return "quiz";
									if (pollType == Type::REGULAR) return "regular";
									else return "";
								};

	QJsonObject pollJsonObject{ {"id", id}, {"question", question}, {"options", QVectorToQJsonArray(options)}, {"total_voter_count", total_voter_count},
								{"is_closed", is_closed}, {"is_anonymous", is_anonymous}, {"type", GetPollTypeInString(type)}, {"allows_multiple_answers", allows_multiple_answers} };

	if (correct_option_id.has_value())		pollJsonObject.insert("correct_option_id", *correct_option_id);
	if (explanation.has_value())			pollJsonObject.insert("explanation", *explanation);
	if (explanation_entities.has_value())	pollJsonObject.insert("explanation_entities", QVectorToQJsonArray(*explanation_entities));
	if (open_period.has_value())			pollJsonObject.insert("open_period", *open_period);
	if (close_date.has_value())				pollJsonObject.insert("close_date", *close_date);

	return pollJsonObject;
}

bool Telegram::Poll::isEmpty() const
{
	return id == ""
		   and question == ""
		   and options.isEmpty()
		   and total_voter_count == 0
		   and is_closed == false
		   and is_anonymous == false
		   and type == Type::UNINITIALIZED_VALUE
		   and allows_multiple_answers == false
		   and correct_option_id == std::nullopt
		   and explanation == std::nullopt
		   and explanation_entities == std::nullopt
		   and open_period == std::nullopt
		   and close_date == std::nullopt;
}
