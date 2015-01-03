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
#include "resturlbuilder.h"

RestUrlBuilder::RestUrlBuilder(QObject* parent) : QObject(parent) {
    _pathsBuffer = new QStringList();
    _parametersBuffer = new QStringList();
    _protocol = Protocol::Http;
    _host = Strings::Empty;
    _port = -1;

    _pathValues << "/"
                << "?"
                << "&"
                << "="
                << ":";
}

RestUrlBuilder::~RestUrlBuilder() {
    if (_pathsBuffer) {
        delete _pathsBuffer;
        _pathsBuffer = NULL;
    }
    if (_parametersBuffer) {
        delete _parametersBuffer;
        _parametersBuffer = NULL;
    }
}

const QString RestUrlBuilder::Http = "http";

const QString RestUrlBuilder::Https = "https";

RestUrlBuilder& RestUrlBuilder::appendPath(const QString& path) {
    QString value(path);
    value = cleanValue(value);

    _pathsBuffer->append(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendPath(const QChar& path) {
    QString value(path);
    appendPath(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendPath(short path) {
    QString value = QString::number(path);
    appendPath(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendPath(int path) {
    QString value = QString::number(path);
    appendPath(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendPath(long path) {
    QString value = QString::number(path);
    appendPath(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendPath(float path) {
    QString value = QString::number(path, 'g', 10);
    appendPath(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendPath(double path) {
    QString value = QString::number(path, 'g', 10);
    appendPath(value);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::resetPaths() {
    _pathsBuffer->clear();

    return *this;
}

RestUrlBuilder& RestUrlBuilder::appendParameter(const QString& parameter, const QString& value) {
    QString checkedParameter(parameter);
    checkedParameter = cleanValue(checkedParameter);
    QString checkedValue(value);
    checkedValue = cleanValue(checkedValue);

    QString result = QString(checkedParameter).append("=").append(checkedValue);
    _parametersBuffer->append(result);

    return *this;
}

RestUrlBuilder& RestUrlBuilder::resetParameters() {
    _parametersBuffer->clear();

    return *this;
}

QUrl RestUrlBuilder::build() {
    QString result = urlString();

    return QUrl(result);
}

QString RestUrlBuilder::urlString() {
    QString result = buildHostUrl();

    if (!result.endsWith("/")) {
        result.append("/");
    }

    if (_pathsBuffer->length() > 0) {
        result.append(_pathsBuffer->join("/"));
    }

    if (_parametersBuffer->length() > 0) {
        result.append("?");
        result.append(_parametersBuffer->join("&"));
    }

    return result;
}

QString RestUrlBuilder::host() const {
    return _host;
}

RestUrlBuilder& RestUrlBuilder::appendHost(const QString& host) {
    if (host.isNull() || host.isEmpty()) {
        _host = Strings::Empty;
        return *this;
    }

    QString value(host);
    value = value.trimmed();
    _host = cleanValue(value);

    if (_host.isNull() || _host.isEmpty()) {
        _host = Strings::Empty;
    }

    return *this;
}

RestUrlBuilder::Protocol RestUrlBuilder::protocol() const {
    return _protocol;
}

RestUrlBuilder& RestUrlBuilder::appendProtocol(Protocol protocol) {
    if (protocol == Protocol::None) {
        _protocol = Protocol::Http;
    } else {
        _protocol = protocol;
    }

    return *this;
}

int RestUrlBuilder::port() {
    return _port;
}

RestUrlBuilder& RestUrlBuilder::appendPort(int port) {
    if (port < 0 || port > 65535) {
        _port = -1;
    } else {
        _port = port;
    }

    return *this;
}

QString RestUrlBuilder::buildHostUrl() {
    if (_host.isEmpty()) {
        return Strings::Empty;
    }

    QString hostUrl;

    if (_protocol == Protocol::None || _protocol == Protocol::Http) {
        hostUrl = hostUrl.append(Http);
    } else {
        hostUrl.append(Https);
    }
    hostUrl.append("://").append(_host);

    if (_port >= 0) {
        hostUrl.append(":").append(QString::number(_port));
    }

    return hostUrl;
}

QString& RestUrlBuilder::cleanValue(QString& source) {
    while (Strings::startsWithAny(source, _pathValues)) {
        source = source.mid(1);
    }

    while (Strings::endsWithAny(source, _pathValues)) {
        source = source.mid(0, source.length() - 1);
    }

    return source;
}
