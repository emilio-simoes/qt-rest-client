#include "stringstests.h"

StringsTests::StringsTests() {
}

void StringsTests::initTestCase() {
    list << "/"
         << "?"
         << "&"
         << "=";
}

void StringsTests::cleanupTestCase() {
    list.clear();
}

void StringsTests::testStartsWithAny() {
    QString testString = "/path";
    QVERIFY(Strings::startsWithAny(testString, list));

    testString = "?path";
    QVERIFY(Strings::startsWithAny(testString, list));

    testString = "&path";
    QVERIFY(Strings::startsWithAny(testString, list));

    testString = "=path";
    QVERIFY(Strings::startsWithAny(testString, list));
}

void StringsTests::testNotStartsWithAny() {
    QString testString = "\\path";
    QVERIFY(!Strings::startsWithAny(testString, list));

    testString = "path/";
    QVERIFY(!Strings::startsWithAny(testString, list));

    testString = "path?";
    QVERIFY(!Strings::startsWithAny(testString, list));

    testString = "path&";
    QVERIFY(!Strings::startsWithAny(testString, list));

    testString = "path=";
    QVERIFY(!Strings::startsWithAny(testString, list));
}

void StringsTests::testEndsWithAny()
{
    QString testString = "path/";
    QVERIFY(Strings::endsWithAny(testString, list));

    testString = "path?";
    QVERIFY(Strings::endsWithAny(testString, list));

    testString = "path&";
    QVERIFY(Strings::endsWithAny(testString, list));

    testString = "path=";
    QVERIFY(Strings::endsWithAny(testString, list));
}

void StringsTests::testNotEndsWithAny()
{
    QString testString = "path%";
    QVERIFY(!Strings::endsWithAny(testString, list));

    testString = "/path";
    QVERIFY(!Strings::endsWithAny(testString, list));

    testString = "?path";
    QVERIFY(!Strings::endsWithAny(testString, list));

    testString = "&path";
    QVERIFY(!Strings::endsWithAny(testString, list));

    testString = "=path";
    QVERIFY(!Strings::endsWithAny(testString, list));
}
