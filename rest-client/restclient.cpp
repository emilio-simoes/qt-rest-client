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
/*!
 * \class RestClient
 * \since 1.0
 *
 * This class is a simple REST client for use with Qt/C++.
 * It supports the most common HTTP verbs like GET, POST, PUT and DELETE.
 * It also contains support for Basic HTTP Autentication.
 */
#include "restclient.h"

#include <QEventLoop>

/*!
  \fn RestClient::RestClient(QObject *parent)
 * \brief Constructor for the RestClient.
 * \param parent The parent QObject for the RestClient.
 */
RestClient::RestClient(QObject* parent) : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedRequest(QNetworkReply*)));

    _isAsync = false;
    _authenticationMode = AuthenticationMode::None;
    _credentials = NULL;
    _contentType = Form;
    _accept = NULL;
    _statusCode = 0;
    _statusMessage = QString();
}

/*!
  \fn RestClient::~RestClient()
 * \brief Destructor for the RestClient.
 */
RestClient::~RestClient() {
    if (_manager) {
        delete _manager;
        _manager = NULL;
    }
}

const QString RestClient::Json = "application/json";

const QString RestClient::Form = "application/x-www-form-urlencoded";

const QString RestClient::Xml = "application/xml";

QJsonDocument* RestClient::getJson(const QUrl& url) {
    _isAsync = false;

    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply* reply = doGet(url);
    eventLoop.exec();

    disconnect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    return processJsonReply(reply, true, NULL);
}

void RestClient::getResource(const QUrl& url) {
    _isAsync = true;

    doGet(url);
}

QJsonDocument* RestClient::deleteJson(const QUrl& url) {
    _isAsync = false;

    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply* reply = doDelete(url);
    eventLoop.exec();

    disconnect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    return processJsonReply(reply, true, NULL);
}

void RestClient::deleteResource(const QUrl& url) {
    _isAsync = true;

    doDelete(url);
}

QJsonDocument* RestClient::postJson(const QUrl& url, const QJsonDocument& document) {
    _isAsync = false;

    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    setContentType(Json);
    QNetworkReply* reply = doPost(url, document.toJson());
    eventLoop.exec();

    disconnect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    return processJsonReply(reply, true, NULL);
}

void RestClient::postResource(const QUrl& url, const QJsonDocument& document) {
    _isAsync = true;

    doPost(url, document.toJson());
}

QJsonDocument* RestClient::putJson(const QUrl& url, const QJsonDocument& document) {
    _isAsync = false;

    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    setContentType(Json);
    QNetworkReply* reply = doPut(url, document.toJson());
    eventLoop.exec();

    disconnect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    return processJsonReply(reply, true, NULL);
}

void RestClient::putResource(const QUrl& url, const QJsonDocument& document) {
    _isAsync = true;

    doPut(url, document.toJson());
}

RestClient::AuthenticationMode RestClient::authenticationMode() const {
    return _authenticationMode;
}

QString RestClient::contentType() const {
    return _contentType;
}

QString* RestClient::accept() const {
    return _accept;
}

int RestClient::statusCode() const {
    return _statusCode;
}

QString RestClient::statusMessage() const {
    return _statusMessage;
}

void RestClient::setCredentials(Credentials* credentials) {
    _credentials = credentials;
}

void RestClient::addCustomHeader(const QString& name, const QString& value) {
    _headers.insert(QString(name), QString(value));
}

void RestClient::clearCustomHeaders() {
    _headers.clear();
}

void RestClient::setAuthenticationMode(RestClient::AuthenticationMode mode) {
    if (_authenticationMode == mode) {
        return;
    }

    _authenticationMode = mode;
    emit authenticationModeChanged(mode);
}

void RestClient::setContentType(QString contentType) {
    if (_contentType == contentType) {
        return;
    }

    _contentType = contentType;
    emit contentTypeChanged(contentType);
}

void RestClient::setAccept(QString* accepts) {
    if (_accept == accepts) {
        return;
    }

    _accept = accepts;
    emit acceptChanged(accepts);
}

void RestClient::setStatusCode(int statusCode) {
    if (_statusCode == statusCode) {
        return;
    }

    _statusCode = statusCode;
    emit statusCodeChanged(statusCode);
}

void RestClient::setStatusMessage(QString statusMessage) {
    if (_statusMessage == statusMessage) {
        return;
    }

    _statusMessage = statusMessage;
    emit statusMessageChanged(statusMessage);
}

void RestClient::finishedRequest(QNetworkReply* reply) {
    _statusCode = getStatusCode(reply);

    if (!_isAsync) {
        return;
    }

    QByteArray output;
    QJsonDocument* result = processJsonReply(reply, false, &output);

    if (result) {
        emit onJsonRequestExecuted(result);
    }
    emit onRequestExecuted(output);
}

QNetworkReply* RestClient::doGet(const QUrl& url) {
    _statusCode = 0;
    QNetworkRequest request(url);
    setBasicAuthentication(request);
    setAccept(request);
    setCustomHeaders(request);
    QNetworkReply* reply = _manager->get(request);
    return reply;
}

QNetworkReply* RestClient::doDelete(const QUrl& url) {
    _statusCode = 0;
    QNetworkRequest request(url);
    setBasicAuthentication(request);
    setAccept(request);
    setCustomHeaders(request);
    QNetworkReply* reply = _manager->deleteResource(request);
    return reply;
}

QNetworkReply* RestClient::doPost(const QUrl& url, const QByteArray& body) {
    _statusCode = 0;
    QNetworkRequest request(url);
    setBasicAuthentication(request);
    setAccept(request);
    setCustomHeaders(request);
    setContentType(request);
    QNetworkReply* reply = _manager->post(request, body);
    return reply;
}

QNetworkReply* RestClient::doPut(const QUrl& url, const QByteArray& body) {
    _statusCode = 0;
    QNetworkRequest request(url);
    setBasicAuthentication(request);
    setAccept(request);
    setCustomHeaders(request);
    setContentType(request);
    QNetworkReply* reply = _manager->put(request, body);
    return reply;
}

QJsonDocument* RestClient::processJsonReply(QNetworkReply* reply, bool sendParseError, QByteArray* result) {
    if (!reply) {
        return NULL;
    }

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseBytes = reply->readAll();
        QString response(responseBytes);

        QJsonParseError error;
        QJsonDocument* document = new QJsonDocument(QJsonDocument::fromJson(response.toUtf8(), &error));
        delete reply;

        if (error.error == QJsonParseError::NoError) {
            return document;
        }

        if (sendParseError) {
            sendError("Bad response format" + error.error, response);
        } else if (result) {
            (*result).clear();
            (*result).append(response);
        }

        delete document;
        return NULL;
    }

    sendError("Request error", reply->errorString());
    delete reply;
    return NULL;
}

void RestClient::sendError(const QString& errorMessage, const QString& result) {
    RequestError* error = new RequestError();
    error->setErrorMessage(errorMessage);
    error->setResult(result);
    emit onRequestError(error);
}

void RestClient::setBasicAuthentication(QNetworkRequest& request) {
    if (_authenticationMode == AuthenticationMode::Basic && _credentials) {
        QString headerValue("Basic ");
        headerValue.append(_credentials->asBase64());
        QByteArray value = headerValue.toLatin1();
        request.setRawHeader("Authorization", value);
    }
}

void RestClient::setAccept(QNetworkRequest& request) {
    if (!_accept) {
        return;
    }

    QByteArray value = (*_accept).toLatin1();
    request.setRawHeader("Accept", value);
}

void RestClient::setContentType(QNetworkRequest& request) {
    if (_contentType.isEmpty()) {
        _contentType = Form;
    }

    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, _contentType);
}

void RestClient::setCustomHeaders(QNetworkRequest& request) {
    if (_headers.isEmpty()) {
        return;
    }

    foreach (QString key, _headers.keys()) {
        QByteArray name = key.toLatin1();
        QByteArray value = _headers[name].toLatin1();
        request.setRawHeader(name, value);
    }
}

int RestClient::getStatusCode(QNetworkReply* reply) {
    QVariant statusCode = reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute);
    if (!statusCode.isValid()) {
        return 0;
    }

    _statusCode = statusCode.toInt();
    if (_statusCode < 200 || _statusCode > 299) {
        _statusMessage = reply->attribute(QNetworkRequest::Attribute::HttpReasonPhraseAttribute).toString();
    } else {
        _statusMessage = QString();
    }

    return _statusCode;
}
