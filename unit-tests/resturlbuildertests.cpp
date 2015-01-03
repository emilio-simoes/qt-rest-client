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
#include "resturlbuildertests.h"

RestUrlBuilderTests::RestUrlBuilderTests() {
}

void RestUrlBuilderTests::initTestCase() {
}

void RestUrlBuilderTests::cleanupTestCase() {
}

void RestUrlBuilderTests::testBasicUrlString() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    builder.appendProtocol(RestUrlBuilder::Protocol::Http);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "https://localhost/";

    builder.appendProtocol(RestUrlBuilder::Protocol::Https);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost:6000/";

    builder.appendProtocol(RestUrlBuilder::Protocol::None);
    builder.appendPort(6000);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/";

    builder.appendPort(-1);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}

void RestUrlBuilderTests::testUrlParameterString() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/path";

    builder.appendPath("path");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    builder.resetPaths();
    builder.appendPath("/path");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    builder.resetPaths().appendPath("&path/");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}

void RestUrlBuilderTests::testUrlParameterShort() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/123";

    short value = 123;
    builder.resetPaths().appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}

void RestUrlBuilderTests::testUrlParameterInt() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/123456";

    int value = 123456;
    builder.resetPaths().appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}

void RestUrlBuilderTests::testUrlParameterLong() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/123456000000000";

    long value = 123456000000000;
    builder.resetPaths().appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost:3215/123456000000000";

    builder.resetPaths().appendPort(3215).appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}

void RestUrlBuilderTests::testUrlParameterFloat() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/123.25";

    float value = 123.25f;
    builder.resetPaths().appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost:9000/123.25";

    builder.appendPort(9000).resetPaths().appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}

void RestUrlBuilderTests::testUrlParameterDouble() {
    RestUrlBuilder builder;
    QString baseUrl = "http://localhost/";

    builder.appendHost("localhost");
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);

    baseUrl = "http://localhost/123456.5586";

    double value = 123456.5586;
    builder.resetPaths().appendPath(value);
    qDebug() << builder.urlString();
    QCOMPARE(builder.urlString(), baseUrl);
}
