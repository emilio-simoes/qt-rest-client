#ifndef RESTURLBUILDERTESTS_H
#define RESTURLBUILDERTESTS_H

#include <QtTest>

#include "autotest.h"

#include "resturlbuilder.h"

class RestUrlBuilderTests : public QObject {
        Q_OBJECT

    public:
        RestUrlBuilderTests();

    private Q_SLOTS:
        void initTestCase();
        void cleanupTestCase();
        void testBasicUrlString();
        void testUrlParameterString();
        void testUrlParameterShort();
        void testUrlParameterInt();
        void testUrlParameterLong();
        void testUrlParameterFloat();
        void testUrlParameterDouble();
};

DECLARE_TEST(RestUrlBuilderTests)

#endif // RESTURLBUILDERTESTS_H
