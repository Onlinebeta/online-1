// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ONLINE_QT_TEST_URITESTS_H
#define ONLINE_QT_TEST_URITESTS_H

#include <QObject>
#include <QTest>

class URITests : public QObject
{
    Q_OBJECT

private slots:
    void uriTests();
};

#endif // ONLINE_QT_TEST_URITESTS_H
