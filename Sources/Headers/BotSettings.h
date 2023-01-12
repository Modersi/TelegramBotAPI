#ifndef TELEGRAM_BOTSETTINGS_H
#define TELEGRAM_BOTSETTINGS_H

#include <memory>
#include <optional>

#include "qhostaddress.h"
#include "qsslconfiguration.h"
#include "qstring.h"
#include "qvector.h"
#include "qdir.h"
class QFile;

namespace Telegram
{
    /**
     *
     * @brief This class represents your bot settings. Used to startup bot, set up encryption, payments, host addres, port, and more
     * 
     */

    struct BotSettings
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to "" or std::nullopt */
        BotSettings();

        /** @brief Constructs BotSettings */
        BotSettings(const QString& bot_token,
                    const std::optional<QString> webhook_url = std::nullopt,
                    const std::optional<QSslConfiguration> ssl_configuration = std::nullopt,
                    const std::optional<std::shared_ptr<QFile>> public_key = std::nullopt,
                    const std::optional<QString> webhook_ip_addres = std::nullopt,
                    const std::optional<qint32> max_connections = std::nullopt,
                    const std::optional<QVector<QString>>& allowed_updates = std::nullopt,
                    const std::optional<QHostAddress>& host_addres = std::nullopt,
                    const std::optional<quint16> port = std::nullopt,
                    const std::optional<QString> payment_token = std::nullopt);

        /** @brief Constructs BotSettings from the file bot_settings_file_name("BotSettings.json" by default) located in bot_settings_file_path(project root folder by default)
         *
         * If there is no such file in bot_settings_file_path - new "BotSettings.json" file with default settings is created */
        static std::shared_ptr<BotSettings> makeFromFile(const QDir& bot_settings_file_path = QDir(), const QString& bot_settings_file_name = "BotSettings.json");

 //** Bot settings **//

        /** @brief Your bot token */
        QString bot_token;

        /** @brief Required if you want to use the bot with webhooks. HTTPS URL to send updates to. Use an empty string to remove webhook integration. Use std::nullopt(or null in JSON) if you want to use the bot with long polling technique */
        std::optional<QString> webhook_url;

        /** @brief Required if you want to use the bot with webhooks. Your encryption configuration. Use std::nullopt(or null in JSON) if you want use bot with long polling */
        std::optional<QSslConfiguration> ssl_configuration;

        /** @brief Required if you use self-signed SSL certificate. Your PEM encoded (ASCII BASE64) public key. Use std::nullopt(or null in JSON) if you use normal certificate */
        std::optional<std::shared_ptr<QFile>> public_key;

        /** @brief Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS. */
        std::optional<QString> webhook_ip_addres;

        /** @brief Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40. Use lower values to limit the load on your bot's server, and higher values to increase your bot's throughput */
        std::optional<qint32> max_connections;

        /** @brief Optional. A list of the update types you want your bot to receive. For example, specify { “message”, “edited_channel_post”, “callback_query” } to only receive updates of these types. See Update.h for a complete list of available update types. Specify an empty list to receive all update types except chat_member(default). If not specified, the previous setting will be used.
         *
         *  Please note that this parameter doesn't affect updates created before the call to the setWebhook, so unwanted updates may be received for a short period of time. */
        std::optional<QVector<QString>> allowed_updates;

        /** @brief Optional. Pass True to drop all pending updates */
        std::optional<bool> drop_pending_updates;

        /** @brief Optional. Local IP address for Webhook server to be listening for incoming connections. "127.0.0.1" by default */
        std::optional<QHostAddress> host_addres;

        /** @brief Optional. Local port for Webhook server to be listening for incoming connections. "443" by default */
        std::optional<quint16> port;

        /** @brief Optional. Your payment token */
        std::optional<QString> payment_token;
    };
}

#endif // TELEGRAM_BOTSETTINGS_H
