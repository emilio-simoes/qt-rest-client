/*
 * Qt REST Client
 * Copyright (C) 2014 Emílio Simões
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
