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
#include "restclienttests.h"

RestClientTests::RestClientTests() {
}

void RestClientTests::initTestCase() {
}

void RestClientTests::cleanupTestCase() {
}

void RestClientTests::testGet() {
    RestClient client;
    QJsonDocument* jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/colors")));
    QCOMPARE(client.statusCode(), 200);

    QJsonObject jsonRootObject = jsonResponse->object();

    QJsonValue value = jsonRootObject.value("data");
    QJsonArray jsonArray = value.toArray();

    QCOMPARE(jsonArray.count(), 6);

    foreach (const QJsonValue& current, jsonArray) {
        QVERIFY(!current.toObject().value("name").toString().isEmpty());
        QVERIFY(!current.toObject().value("value").toString().isEmpty());
    }

    delete jsonResponse;

    jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/colors/red")));
    QCOMPARE(client.statusCode(), 200);

    QJsonObject jsonObject = jsonResponse->object();

    QCOMPARE(jsonObject.value("name").toString(), QString("red"));
    QCOMPARE(jsonObject.value("value").toString(), QString("#f00"));

    delete jsonResponse;
}

void RestClientTests::testPost() {
    QJsonObject object;
    object.insert("name", QJsonValue("violet"));
    object.insert("value", QJsonValue("#800080"));

    QJsonDocument document(object);
    RestClient client;
    client.setAuthenticationMode(RestClient::AuthenticationMode::Basic);

    BasicCredentials* credentials = new BasicCredentials();
    credentials->setUsername(new QString("eu"));
    credentials->setPassword(new QString("123"));
    client.setCredentials(credentials);

    QJsonDocument* jsonResponse = client.postJson(QUrl(QString("http://localhost:5000/api/colors")), document);
    QCOMPARE(client.statusCode(), 201);

    QJsonObject jsonObject = jsonResponse->object();

    QCOMPARE(jsonObject.value("name").toString(), QString("violet"));
    QCOMPARE(jsonObject.value("value").toString(), QString("#800080"));

    delete jsonResponse;
}

void RestClientTests::testPut() {
    QJsonObject object;
    object.insert("name", QJsonValue("violet"));
    object.insert("value", QJsonValue("#810081"));

    QJsonDocument document(object);
    RestClient client;
    client.setAuthenticationMode(RestClient::AuthenticationMode::Basic);

    BasicCredentials* credentials = new BasicCredentials();
    credentials->setUsername(new QString("eu"));
    credentials->setPassword(new QString("123"));
    client.setCredentials(credentials);

    QJsonDocument* jsonResponse = client.putJson(QUrl(QString("http://localhost:5000/api/colors/violet")), document);
    QCOMPARE(client.statusCode(), 200);

    QJsonObject jsonObject = jsonResponse->object();

    QCOMPARE(jsonObject.value("name").toString(), QString("violet"));
    QCOMPARE(jsonObject.value("value").toString(), QString("#810081"));

    delete jsonResponse;
}

void RestClientTests::testDelete() {
    RestClient client;
    client.setAuthenticationMode(RestClient::AuthenticationMode::Basic);

    BasicCredentials* credentials = new BasicCredentials();
    credentials->setUsername(new QString("eu"));
    credentials->setPassword(new QString("123"));
    client.setCredentials(credentials);

    QJsonDocument* jsonResponse = client.deleteJson(QUrl(QString("http://localhost:5000/api/colors/violet")));
    QCOMPARE(client.statusCode(), 200);

    QJsonObject jsonRootObject = jsonResponse->object();

    QCOMPARE(jsonRootObject.value("name").toString(), QString("violet"));
    QCOMPARE(jsonRootObject.value("value").toString(), QString("#810081"));

    delete jsonResponse;

    jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/colors")));
    QCOMPARE(client.statusCode(), 200);

    jsonRootObject = jsonResponse->object();

    QJsonValue value = jsonRootObject.value("data");
    QJsonArray jsonArray = value.toArray();

    QCOMPARE(jsonArray.count(), 6);

    foreach (const QJsonValue& current, jsonArray) {
        QVERIFY(!current.toObject().value("name").toString().isEmpty());
        QVERIFY(!current.toObject().value("value").toString().isEmpty());
    }

    delete jsonResponse;
}

void RestClientTests::testAuthenticatedGet() {
    RestClient client;
    client.setAuthenticationMode(RestClient::AuthenticationMode::Basic);

    BasicCredentials* credentials = new BasicCredentials();
    credentials->setUsername(new QString("eu"));
    credentials->setPassword(new QString("123"));
    client.setCredentials(credentials);

    QJsonDocument* jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/token")));
    QCOMPARE(client.statusCode(), 200);
    if (!jsonResponse) {
        QFAIL("Request execution failed");
    }

    QJsonObject jsonRootObject = jsonResponse->object();

    QCOMPARE(jsonRootObject.value("duration").toInt(), 600);
    QVERIFY(!jsonRootObject.value("token").toString().isEmpty());
}

void RestClientTests::testTokenAuthenticatedGet() {
    RestClient client;
    client.setAuthenticationMode(RestClient::AuthenticationMode::Basic);

    BasicCredentials* credentials = new BasicCredentials();
    credentials->setUsername(new QString("eu"));
    credentials->setPassword(new QString("123"));
    client.setCredentials(credentials);

    QJsonDocument* jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/token")));
    QCOMPARE(client.statusCode(), 200);
    if (!jsonResponse) {
        QFAIL("Request execution failed");
    }

    QJsonObject jsonRootObject = jsonResponse->object();

    QCOMPARE(jsonRootObject.value("duration").toInt(), 600);
    QVERIFY(!jsonRootObject.value("token").toString().isEmpty());

    delete credentials;
    delete jsonResponse;

    QString token = jsonRootObject.value("token").toString();
    credentials = new BasicCredentials();
    credentials->setUsername(&token);
    credentials->setPassword(new QString("unused"));
    client.setCredentials(credentials);

    jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/resource")));
    QCOMPARE(client.statusCode(), 200);
    if (!jsonResponse) {
        QFAIL("Request execution failed");
    }

    jsonRootObject = jsonResponse->object();

    QCOMPARE(jsonRootObject.value("data").toString(), QString("Hello, eu!"));

    delete jsonResponse;
}

void RestClientTests::testHeaders() {
    RestClient client;
    client.setAuthenticationMode(RestClient::AuthenticationMode::Basic);
    QString accept(RestClient::Json);
    client.setAccept(&accept);
    client.addCustomHeader("Date", QDateTime::currentDateTime().toString(Qt::DateFormat::RFC2822Date));

    BasicCredentials* credentials = new BasicCredentials();
    credentials->setUsername(new QString("eu"));
    credentials->setPassword(new QString("123"));
    client.setCredentials(credentials);

    QJsonDocument* jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/token")));
    QCOMPARE(client.statusCode(), 200);
    if (!jsonResponse) {
        QFAIL("Request execution failed");
    }

    QJsonObject jsonRootObject = jsonResponse->object();

    QCOMPARE(jsonRootObject.value("duration").toInt(), 600);
    QVERIFY(!jsonRootObject.value("token").toString().isEmpty());

    delete jsonResponse;
}
