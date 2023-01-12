#include "Types/MaskPosition.h"

Telegram::MaskPosition::MaskPosition() :
	point(),
	x_shift(),
	y_shift(),
	scale()
{}

Telegram::MaskPosition::MaskPosition(const Point& point,
									 const float& x_shift,
									 const float& y_shift,
									 const float& scale) : 
	point(point),
	x_shift(x_shift),
	y_shift(y_shift),
	scale(scale)
{}

Telegram::MaskPosition::MaskPosition(const QJsonObject& json_object) {
	json_object.contains("point")   ? point = static_cast<decltype(point)>(QMetaEnum::fromType<decltype(point)>().keyToValue(json_object["point"].toString().toUpper().toUtf8())) : point = decltype(point)::NULL_ENUMERATOR;
	json_object.contains("x_shift") ? x_shift = json_object["x_shift"].toDouble()																									: x_shift = 0.0;
	json_object.contains("y_shift") ? y_shift = json_object["y_shift"].toDouble()																									: y_shift = 0.0;
	json_object.contains("scale")   ? scale = json_object["scale"].toDouble()																										: scale = 0.0;
}

QJsonObject Telegram::MaskPosition::toObject() const {
	if (isEmpty()) return {};

	return { {"point", QString(QMetaEnum::fromType<decltype(point)>().valueToKey(static_cast<int>(point))).toLower()}, {"x_shift", x_shift}, {"y_shift", y_shift}, {"scale", scale} };
}

bool Telegram::MaskPosition::isEmpty() const {
	return point == decltype(point)::NULL_ENUMERATOR
		   and x_shift == 0.0
		   and y_shift == 0.0
		   and scale == 0.0;
}
