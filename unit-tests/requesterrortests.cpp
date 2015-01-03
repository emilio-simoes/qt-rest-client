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
