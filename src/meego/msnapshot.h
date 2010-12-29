/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

#ifndef MSNAPSHOT_H
#define MSNAPSHOT_H

#include <qdeclarativeitem.h>
#include <qglobal.h>
#include <qpixmap.h>

class MSnapshot : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(int snapshotWidth READ snapshotWidth WRITE setSnapshotWidth NOTIFY snapshotWidthChanged)
    Q_PROPERTY(int snapshotHeight READ snapshotHeight WRITE setSnapshotHeight NOTIFY snapshotHeightChanged)

public:
    MSnapshot(QDeclarativeItem *parent = 0);
    virtual ~MSnapshot();

    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    int snapshotWidth() const;
    int snapshotHeight() const;

    void setSnapshotWidth(int width);
    void setSnapshotHeight(int height);

public Q_SLOTS:
    void take();
    void free();

Q_SIGNALS:
    void snapshotWidthChanged();
    void snapshotHeightChanged();

private:
    Q_DISABLE_COPY(MSnapshot)

    QPixmap snapshot;
    int sWidth;
    int sHeight;
};

QML_DECLARE_TYPE(MSnapshot)
#endif
