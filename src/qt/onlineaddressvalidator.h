// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ONLINE_QT_ONLINEADDRESSVALIDATOR_H
#define ONLINE_QT_ONLINEADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class OnlineAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit OnlineAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Online address widget validator, checks for a valid online address.
 */
class OnlineAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit OnlineAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ONLINE_QT_ONLINEADDRESSVALIDATOR_H
