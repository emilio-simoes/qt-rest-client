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
#include "basiccredentialstests.h"

#include <QDebug>

BasicCredentialsTests::BasicCredentialsTests() {
}

void BasicCredentialsTests::initTestCase() {
}

void BasicCredentialsTests::cleanupTestCase() {
}

void BasicCredentialsTests::testBasicCredentials() {
    BasicCredentials* credentials = new BasicCredentials();
    QString username("name");
    QString password("pass");
    credentials->setUsername(&username);
    credentials->setPassword(&password);

    QCOMPARE(*credentials->username(), QString("name"));
    QCOMPARE(*credentials->password(), QString("pass"));
}

void BasicCredentialsTests::testCredentialsEncoding() {
    BasicCredentials* credentials = new BasicCredentials();
    QString username("name");
    QString password("pass");
    credentials->setUsername(&username);
    credentials->setPassword(&password);

    QCOMPARE(*credentials->asBase64(), QString("bmFtZTpwYXNz"));
}
