#ifndef STRINGSTESTS
#define STRINGSTESTS

#include <QString>
#include <QStringList>
#include <QtTest>

#include "autotest.h"

#include "utils/strings.h"

class StringsTests : public QObject {
        Q_OBJECT

    public:
        StringsTests();

    private Q_SLOTS:
        void initTestCase();
        void cleanupTestCase();
        void testStartsWithAny();
        void testNotStartsWithAny();
        void testEndsWithAny();
        void testNotEndsWithAny();

    private:
        QStringList list;
};

DECLARE_TEST(StringsTests)

#endif // STRINGSTESTS
