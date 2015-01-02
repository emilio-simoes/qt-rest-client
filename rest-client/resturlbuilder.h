#ifndef RESTURLBUILDER_H
#define RESTURLBUILDER_H

#include <QObject>
#include <QStringList>
#include <QUrl>

#include "utils/strings.h"

class RestUrlBuilder : public QObject {
        Q_OBJECT
        Q_ENUMS(Protocol)

    public:
        enum class Protocol { None, Http, Https };

    public:
        explicit RestUrlBuilder(QObject* parent = 0);
        ~RestUrlBuilder();

        RestUrlBuilder& appendPath(const QString& path);
        RestUrlBuilder& appendPath(const QChar& path);
        RestUrlBuilder& appendPath(short path);
        RestUrlBuilder& appendPath(int path);
        RestUrlBuilder& appendPath(long path);
        RestUrlBuilder& appendPath(float path);
        RestUrlBuilder& appendPath(double path);
        RestUrlBuilder& resetPaths();
        RestUrlBuilder& appendParameter(const QString& paramenter, const QString& value);
        RestUrlBuilder& resetParameters();

        QUrl build();
        QString urlString();

        QString host() const;
        RestUrlBuilder& appendHost(const QString& host);

        Protocol protocol() const;
        RestUrlBuilder& appendProtocol(Protocol protocol);

        int port();
        RestUrlBuilder& appendPort(int port);

    private:
        static const QString Http;
        static const QString Https;

        QStringList* _pathsBuffer;
        QStringList* _parametersBuffer;

        QStringList _pathValues;

        QString _host;
        Protocol _protocol;
        int _port;

        QString buildHostUrl();
        QString& cleanValue(QString& source);
};

#endif // RESTURLBUILDER_H
