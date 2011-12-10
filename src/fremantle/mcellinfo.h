/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MCELLINFO_H
#define MCELLINFO_H

#include <QtCore/qscopedpointer.h>
#include <QtDeclarative/qdeclarativeitem.h>

class MCellInfoPrivate;

class MCellInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool offline READ offline NOTIFY offlineChanged)

    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString provider READ networkOperator NOTIFY operatorChanged)
    Q_PROPERTY(QString mode READ radioMode NOTIFY radioModeChanged)

    Q_PROPERTY(int strength READ signalStrength NOTIFY signalStrengthChanged)

public:
    explicit MCellInfo(QObject *parent = 0);
    ~MCellInfo();

    bool active() const;
    bool offline() const;
    QString status() const;

    QString networkOperator() const;
    QString radioMode() const;

    int signalStrength() const;

Q_SIGNALS:
    void activeChanged();
    void offlineChanged();

    void statusChanged();
    void operatorChanged();
    void radioModeChanged();

    void signalStrengthChanged();

protected:
    MCellInfoPrivate* d_ptr;

private:
    Q_DISABLE_COPY(MCellInfo)
    Q_DECLARE_PRIVATE(MCellInfo)
};

QML_DECLARE_TYPE(MCellInfo)

#endif // MCELLINFO_H