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
