#ifndef REQUESTERRORTESTS_H
#define REQUESTERRORTESTS_H

#include <QtTest>

#include "autotest.h"

#include "requesterror.h"

class RequestErrorTests : public QObject {
        Q_OBJECT

    public:
        explicit RequestErrorTests();

    private Q_SLOTS:
        void initTestCase();
        void cleanupTestCase();
        void testSimpleErrorMessage();
        void testErrorMessageWithNoResult();
        void testErrorMessageWithNoMessage();
};

DECLARE_TEST(RequestErrorTests)

#endif // REQUESTERRORTESTS_H
