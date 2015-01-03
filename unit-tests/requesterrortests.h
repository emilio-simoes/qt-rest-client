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
