#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>

#include <QUrl>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>

#include "requesterror.h"
#include "auth/credentials.h"

class RestClient : public QObject {
        Q_OBJECT
        Q_ENUMS(AuthenticationMode)
        Q_PROPERTY(AuthenticationMode authenticationMode READ authenticationMode WRITE setAuthenticationMode NOTIFY
                   authenticationModeChanged)
        Q_PROPERTY(QString contentType READ contentType WRITE setContentType NOTIFY contentTypeChanged)
        Q_PROPERTY(QString* accept READ accept WRITE setAccept NOTIFY acceptChanged)
        Q_PROPERTY(int statusCode READ statusCode WRITE setStatusCode NOTIFY statusCodeChanged)
        Q_PROPERTY(QString statusMessage READ statusMessage WRITE setStatusMessage NOTIFY statusMessageChanged)

    public:
        enum class AuthenticationMode { None, Basic, Token };

        static const QString Json;
        static const QString Form;
        static const QString Xml;

    public:
        explicit RestClient(QObject* parent = 0);
        ~RestClient();

        QJsonDocument* getJson(const QUrl& url);
        void getResource(const QUrl& url);

        QJsonDocument* deleteJson(const QUrl& url);
        void deleteResource(const QUrl& url);

        QJsonDocument* postJson(const QUrl& url, const QJsonDocument& document);
        void postResource(const QUrl& url, const QJsonDocument& document);

        QJsonDocument* putJson(const QUrl& url, const QJsonDocument& document);
        void putResource(const QUrl& url, const QJsonDocument& document);

        AuthenticationMode authenticationMode() const;
        QString contentType() const;
        QString* accept() const;
        int statusCode() const;
        QString statusMessage() const;
        void setCredentials(Credentials* credentials);

        void addCustomHeader(const QString& name, const QString& value);
        void clearCustomHeaders();

    public slots:
        void setAuthenticationMode(AuthenticationMode mode);
        void setContentType(QString contentType);
        void setAccept(QString* accept);
        void setStatusCode(int statusCode);
        void setStatusMessage(QString statusMessage);

    private slots:
        void finishedRequest(QNetworkReply* reply);

    signals:
        void onJsonRequestExecuted(QJsonDocument* result);
        void onRequestExecuted(QByteArray result);
        void onRequestError(RequestError* error);

        void authenticationModeChanged(AuthenticationMode authenticationMode);
        void contentTypeChanged(QString contentType);
        void acceptChanged(QString* accept);
        void statusCodeChanged(int statusCode);

        void statusMessageChanged(QString arg);

    private:
        QNetworkAccessManager* _manager;
        bool _isAsync;
        AuthenticationMode _authenticationMode;
        Credentials* _credentials;
        QString _contentType;
        QString* _accept;
        int _statusCode;
        QString _statusMessage;

        QMap<QString, QString> _headers;

        QNetworkReply* doGet(const QUrl& url);
        QNetworkReply* doDelete(const QUrl& url);
        QNetworkReply* doPost(const QUrl& url, const QByteArray& body);
        QNetworkReply* doPut(const QUrl& url, const QByteArray& body);
        QJsonDocument* processJsonReply(QNetworkReply* reply, bool sendParseError, QByteArray* result);
        void sendError(const QString& error, const QString& result);
        void setBasicAuthentication(QNetworkRequest& request);
        void setAccept(QNetworkRequest& request);
        void setContentType(QNetworkRequest& request);
        void setCustomHeaders(QNetworkRequest& request);
        int getStatusCode(QNetworkReply* reply);
};

#endif // RESTCLIENT_H
