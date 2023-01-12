#include "Types/InlineQueryResultGame.h"

Telegram::InlineQueryResultGame::InlineQueryResultGame() :
	id(),
	game_short_name(),
	reply_markup()
{
}

Telegram::InlineQueryResultGame::InlineQueryResultGame(const QString& id,
													   const QString& game_short_name,
													   const std::optional<InlineKeyboardMarkup>& reply_markup) :
	id(id),
	game_short_name(game_short_name),
	reply_markup(reply_markup)
{
}

QJsonObject Telegram::InlineQueryResultGame::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_game_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"game_short_name", game_short_name} };

	if (reply_markup.has_value()) inline_query_result_game_json_object.insert("reply_markup", reply_markup->toObject());

	return inline_query_result_game_json_object;
}

bool Telegram::InlineQueryResultGame::isEmpty() const {
	return id == ""
		   and game_short_name == ""
		   and reply_markup == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultGame::getType() const {
	return type;
}
