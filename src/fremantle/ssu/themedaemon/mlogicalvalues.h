/***************************************************************************
**
** Copyright (C) 2010, 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef MLOGICALVALUES_H
#define MLOGICALVALUES_H

#include <QStringList>

typedef QHash<QByteArray, QVariant> Values;
typedef QHash<QByteArray, Values> Groups;

class MLogicalValuesPrivate;

//! \internal
class MLogicalValues
{
public:
    MLogicalValues();
    ~MLogicalValues();

    void load(const QStringList &themeInheritance, const QString &locale = QString());
    bool append(const QString &fileName, const QString &theme = QString());

    bool findKey(const QByteArray &key, QByteArray &group, QVariant &value) const;
    bool value(const QByteArray &group, const QByteArray &key, QVariant &value) const;

    Groups data() const;
    QList<QByteArray> groups() const;
    QHash<QByteArray, QVariant> values(const QByteArray &group) const;

    QList<uint> timestamps() const;

protected:
    MLogicalValuesPrivate *const d_ptr;

private:
    Q_DISABLE_COPY(MLogicalValues)
    Q_DECLARE_PRIVATE(MLogicalValues)
};
//! \internal_end

#endif
