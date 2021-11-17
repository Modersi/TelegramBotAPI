#ifndef TELEGRAM_BOTSETTINGS_H
#define TELEGRAM_BOTSETTINGS_H

#include "qhostaddress.h"
#include "qsslconfiguration.h"
#include "qstring.h"
#include "qvector.h"
#include "qdir.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This class represents your bot settings. Used to startup bot, setup encryption, payments, host adress, port and more
     * 
     */

    struct BotSettings
    {
        /** @brief Constructs BotSettings from file called bot_settings_file_name("BotSettings.json" by the default) located in bot_settings_file_path(project root folder by the default)
         *
         * If there is no such file in bot_settings_file_path - new "BotSettings.json" file with default settings is created */
        BotSettings(const QDir& bot_settings_file_path = QDir(),
                    const QString& bot_settings_file_name  = "BotSettings.json");

        /** @brief Constructs BotSettings from parameters */
        BotSettings(const QHostAddress& host_addres,
                    const quint16& port,
                    const QSslConfiguration& ssl_configuration,
                    const QString& bot_token,
                    const QString& payment_token);

 //** Bot settings **//

         /** @brief Local IP address for Webhook server to be listening for incoming connections. "127.0.0.1" by the default */
        QHostAddress host_addres;

        /** @brief Local port for Webhook server to be listening for incoming connections. "443" by the default */
        quint16 port;

        /** @brief Your encryption configuration. Empty SSL configuration by the default. */
        QSslConfiguration ssl_configuration;

        /** @brief Your bot token. Empty string by the default. */
        QString bot_token;

        /** @brief Your payment token. Empty string by the default. */
        QString payment_token;

    private:
        void CreateDefaultBotSettinngsFile(const QDir& file_path = QDir(), const QString& file_name = "BotSettings.json");
        void ConfigureSSL(const QString& certificate_file_path, const QString& private_key_file_path, const QVector<QString>& ca_certificates_files_paths);
    };
}

#endif // TELEGRAM_BOTSETTINGS_H
