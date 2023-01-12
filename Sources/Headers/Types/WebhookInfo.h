#ifndef TELEGRAM_TYPES_WEBHOOKINFO_H
#define TELEGRAM_TYPES_WEBHOOKINFO_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qvector.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct contains information about the current status of a webhook. Can be obtained via .getWebhookInfo()
     *
     */

    struct WebhookInfo
    {
        /** @brief Default constructor. Constructs an empty WebhookInfo object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        WebhookInfo();

        /** @brief Constructs WebhookInfo object from parameters */
        WebhookInfo(const QString& url,
                    const bool& has_custom_certificate,
                    const qint32& pending_update_count,
                    const std::optional<QString>& ip_address = std::nullopt,
                    const std::optional<qint32>& last_error_date = std::nullopt,
                    const std::optional<QString>& last_error_message = std::nullopt,
                    const std::optional<qint32>& max_connections = std::nullopt,
                    const std::optional<QVector<QString>>& allowed_updates = std::nullopt);

        /** @brief JSON constructor. Constructs WebhookInfo object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to WebhookInfo class fields. For example it should contain pairs such as "url" = "...",
         * "has_custom_certificate" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        WebhookInfo(const QJsonObject& json_object);


        /** @brief Returns WebhookInfo in form of JSON object. Returns empty QJsonObject if WebhookInfo is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if WebhookInfo is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const WebhookInfo&) const = default;


//** Fields **//

        /** @brief Webhook URL, may be empty if webhook is not set up */
        QString url;
        
        /** @brief True, if a custom certificate was provided for webhook certificate checks */
        bool has_custom_certificate;
        
        /** @brief Number of updates awaiting delivery */
        qint32 pending_update_count;
        
        /** @brief Optional. Currently used webhook IP address */
        std::optional<QString> ip_address;
        
        /** @brief Optional. Unix time for the most recent error that happened when trying to deliver an update via webhook */
        std::optional<qint32> last_error_date;
        
        /** @brief Optional. Error message in human-readable format for the most recent error that happened when trying to deliver an update via webhook */
        std::optional<QString> last_error_message;
        
        /** @brief Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery */
        std::optional<qint32> max_connections;
        
        /** @brief Optional. A list of update types the bot is subscribed to. Defaults to all update types except chat_member */
        std::optional<QVector<QString>> allowed_updates;
    };
}

#endif // TELEGRAM_TYPES_WEBHOOKINFO_H

