#ifndef RESTCLIENTTESTS_H
#define RESTCLIENTTESTS_H

#include <QtTest>

#include "autotest.h"

#include "restclient.h"
#include "auth/credentials.h"
#include "auth/basiccredentials.h"

class RestClientTests : public QObject {
        Q_OBJECT

    public:
        RestClientTests();

    private Q_SLOTS:
        void initTestCase();
        void cleanupTestCase();
        void testGet();
        void testPost();
        void testPut();
        void testDelete();
        void testAuthenticatedGet();
        void testTokenAuthenticatedGet();
        void testHeaders();
};

DECLARE_TEST(RestClientTests)

#endif // RESTCLIENTTESTS_H
