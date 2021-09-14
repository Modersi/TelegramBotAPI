#include "Types/ProximityAlertTriggered.h"

#include "qjsonobject.h"

Telegram::ProximityAlertTriggered::ProximityAlertTriggered() :
	traveler(User()),
	watcher(User()),
	distance(0)
{}

Telegram::ProximityAlertTriggered::ProximityAlertTriggered(const User& traveler,
														   const User& watcher,
														   const qint32& distance) :
	traveler(traveler),
	watcher(watcher),
	distance(distance)
{}

Telegram::ProximityAlertTriggered::ProximityAlertTriggered(const QJsonObject& jsonObject)
{
	jsonObject.contains("traveler") ? traveler = User(jsonObject["traveler"].toObject()) : traveler = User();
	jsonObject.contains("watcher")	? watcher = User(jsonObject["watcher"].toObject())	 : watcher = User();
	jsonObject.contains("distance") ? distance = jsonObject["distance"].toInt()			 : distance = 0;
}

QJsonObject Telegram::ProximityAlertTriggered::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"traveler", traveler.toObject()}, {"watcher", watcher.toObject()}, {"distance", distance} };
}

bool Telegram::ProximityAlertTriggered::isEmpty() const
{
	return traveler.isEmpty() and watcher.isEmpty() and distance == 0;
}
