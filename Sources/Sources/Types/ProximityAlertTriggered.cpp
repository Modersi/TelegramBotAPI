#include "Types/ProximityAlertTriggered.h"

Telegram::ProximityAlertTriggered::ProximityAlertTriggered() :
	traveler(),
	watcher(),
	distance()
{}

Telegram::ProximityAlertTriggered::ProximityAlertTriggered(const User& traveler,
														   const User& watcher,
														   const qint32& distance) :
	traveler(traveler),
	watcher(watcher),
	distance(distance)
{}

Telegram::ProximityAlertTriggered::ProximityAlertTriggered(const QJsonObject& json_object) {
	json_object.contains("traveler") ? traveler = User(json_object["traveler"].toObject())   : traveler = User();
	json_object.contains("watcher")	 ? watcher = User(json_object["watcher"].toObject())	 : watcher = User();
	json_object.contains("distance") ? distance = json_object["distance"].toInt()			 : distance = 0;
}

QJsonObject Telegram::ProximityAlertTriggered::toObject() const {
	if (isEmpty()) return {};

	return { {"traveler", traveler.toObject()}, {"watcher", watcher.toObject()}, {"distance", distance} };
}

bool Telegram::ProximityAlertTriggered::isEmpty() const {
	return traveler.isEmpty() and watcher.isEmpty() and distance == 0;
}
