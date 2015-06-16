// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?req-dontexist="));
    QVERIFY(!GUIUtil::parseOnlineURI(uri, &rv));

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?dontexist="));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?amount=0.001"));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?amount=1.001"));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseOnlineURI("online://oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?message=Wikipedia Example Address", &rv));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));
    QVERIFY(rv.address == QString("oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseOnlineURI(uri, &rv));

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseOnlineURI(uri, &rv));

    uri.setUrl(QString("online:oYyAuiXAXfeceL5EYeoBshoryvqDtKSCxy?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseOnlineURI(uri, &rv));
}
