#ifndef BASICCREDENTIALSTESTS_H
#define BASICCREDENTIALSTESTS_H

#include <QtTest>

#include "autotest.h"

#include "auth/basiccredentials.h"

class BasicCredentialsTests : public QObject {
        Q_OBJECT

    public:
        explicit BasicCredentialsTests();

    private Q_SLOTS:
        void initTestCase();
        void cleanupTestCase();
        void testBasicCredentials();
        void testCredentialsEncoding();
};

DECLARE_TEST(BasicCredentialsTests)

#endif // BASICCREDENTIALSTESTS_H
