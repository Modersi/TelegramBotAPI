#ifndef TELEGRAM_TYPES_POLL_H
#define TELEGRAM_TYPES_POLL_H

#include "qvector.h"

#include "PollOption.h"
#include "MessageEntity.h"

namespace Telegram
{
    /**
     *
     * @brief This object contains information about a poll
     *
     */

    struct Poll
    {
        /** @brief Enum that represents all available types of poll */
        enum class Type
        {
            UNINITIALIZED_VALUE,
            QUIZ,
            REGULAR
        };

        /** @brief Default constructor. Constructs an empty Poll object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Poll();

        /** @brief Constructs Poll object from parameters */
        Poll(const QString& id,
             const QString& question,
             const QVector<PollOption>& options,
             const qint32& total_voter_count,
             const bool& is_closed,
             const bool& is_anonymous,
             const Type& type,
             const bool& allows_multiple_answers,
             const std::optional<qint32>& correct_option_id = std::nullopt,
             const std::optional<QString>& explanation = std::nullopt,
             const std::optional<QVector<MessageEntity>>& explanation_entities = std::nullopt,
             const std::optional<qint32>& open_period = std::nullopt,
             const std::optional<qint32>& close_date = std::nullopt);

        /** @brief JSON constructor. Constructs Poll object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Poll class fields. For example it should contain pairs such as "id" = "...",
         * "question" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Poll(const QJsonObject& jsonObject);

        /* @brief Returns Poll in form of JSON object. Returns empty QJsonObject if Poll is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Poll is empty */
        bool isEmpty() const;

//** Fields **//

        /** @brief Unique poll identifier */
        QString id;
        
        /** @brief Poll question, 1-300 characters */
        QString question;
        
        /** @brief List of poll options */
        QVector<PollOption> options;
        
        /** @brief Total number of users that voted in the poll */
        qint32 total_voter_count;
        
        /** @brief True, if the poll is closed */
        bool is_closed;
        
        /** @brief True, if the poll is anonymous */
        bool is_anonymous;
        
        /** @brief Poll type */
        Type type;
        
        /** @brief True, if the poll allows multiple answers */
        bool allows_multiple_answers;
        
        /** @brief Optional. 0-based identifier of the correct answer option
         * 
         * Available only for polls in the quiz mode, which are closed, or was sent (not forwarded) by the bot or to the private chat with the bot */
        std::optional<qint32> correct_option_id;
        
        /** @brief Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters */
        std::optional<QString> explanation;
        
        /** @brief Optional. Special entities like usernames, URLs, bot commands, etc. that appear in the explanation */
        std::optional<QVector<MessageEntity>> explanation_entities;
        
        /** @brief Optional. Amount of time in seconds the poll will be active after creation */
        std::optional<qint32> open_period;
        
        /** @brief Optional. Point in time (Unix timestamp) when the poll will be automatically closed */
        std::optional<qint32> close_date;
    };
}

#endif // TELEGRAM_TYPES_POLL_H
