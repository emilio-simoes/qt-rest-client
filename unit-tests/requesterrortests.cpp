#include "requesterrortests.h"

RequestErrorTests::RequestErrorTests() {
}

void RequestErrorTests::initTestCase() {
}

void RequestErrorTests::cleanupTestCase() {
}

void RequestErrorTests::testSimpleErrorMessage() {
    const QString message = "Some error message";
    const QString result = "Some result message";

    RequestError error;
    error.setErrorMessage(message);
    error.setResult(result);

    QCOMPARE(error.errorMessage(), message);
    QCOMPARE(error.result(), result);
}

void RequestErrorTests::testErrorMessageWithNoResult() {
    const QString message = "Some error message";

    RequestError error;
    error.setErrorMessage(message);

    QCOMPARE(error.errorMessage(), message);
    QVERIFY(error.result().isEmpty());
}

void RequestErrorTests::testErrorMessageWithNoMessage() {
    const QString result = "Some result message";

    RequestError error;
    error.setResult(result);

    QVERIFY(error.errorMessage().isEmpty());
    QCOMPARE(error.result(), result);
}
