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

Telegram::MaskPosition::MaskPosition(const QJsonObject& jsonObject)
{
	auto GetMaskPositionPoint = [](const QJsonValue& maskPositionPoint) -> MaskPosition::Point
							{
								if (maskPositionPoint == "forehead")	return Point::FOREHEAD;
								else if (maskPositionPoint == "eyes")	return Point::EYES;
								else if (maskPositionPoint == "mouth")	return Point::MOUTH;
								else if (maskPositionPoint == "chin")	return Point::CHIN;
								else return Point::UNINITIALIZED_VALUE;
							};

	jsonObject.contains("point")   ? point = GetMaskPositionPoint(jsonObject["point"].toString()) : point = Point::UNINITIALIZED_VALUE;
	jsonObject.contains("x_shift") ? x_shift = jsonObject["x_shift"].toDouble()					  : x_shift = 0.0;
	jsonObject.contains("y_shift") ? y_shift = jsonObject["y_shift"].toDouble()					  : y_shift = 0.0;
	jsonObject.contains("scale")   ? scale = jsonObject["scale"].toDouble()						  : scale = 0.0;
}

QJsonObject Telegram::MaskPosition::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	auto GetMaskPositionPoint = [](const MaskPosition::Point& maskPositionPoint) -> QString
							{
								if (maskPositionPoint == Point::FOREHEAD)	return "forehead";
								else if (maskPositionPoint == Point::EYES)	return "eyes";
								else if (maskPositionPoint == Point::MOUTH)	return "mouth";
								else if (maskPositionPoint == Point::CHIN)	return "chin";
								else return "";
							};

	return QJsonObject{ {"point", GetMaskPositionPoint(point)}, {"x_shift", x_shift}, {"y_shift", y_shift}, {"scale", scale} };
}

bool Telegram::MaskPosition::isEmpty() const
{
	return point == Point::UNINITIALIZED_VALUE
		   and x_shift == 0.0
		   and y_shift == 0.0
		   and scale == 0.0;
}
