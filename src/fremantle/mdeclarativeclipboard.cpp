/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project.
**
** $QT_BEGIN_LICENSE:BMD$
** You may use this file under the terms of the BMD license as follows:
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

#include "mdeclarativeclipboard.h"

#include <QApplication>
#include <QClipboard>

#include <QDebug>

class MDeclarativeClipboardPrivate
{
public:
  QClipboard *clipboard;
  QString clipboard_text;
  MDeclarativeClipboardPrivate() {}
};

MDeclarativeClipboard::MDeclarativeClipboard(QObject *parent) :
    QObject(parent),
    d_ptr(new MDeclarativeClipboardPrivate)
{
    Q_D(MDeclarativeClipboard);

    QApplication *application = qobject_cast<QApplication*>(QApplication::instance());
    d->clipboard = application->clipboard();

    QObject::connect(d->clipboard, SIGNAL(dataChanged()), this, SLOT(onChanged()));
}

MDeclarativeClipboard::~MDeclarativeClipboard()
{
    delete d_ptr;
}

QString MDeclarativeClipboard::text() const
{
  return d_ptr->clipboard->text();
}

void MDeclarativeClipboard::setText(const QString &newTheme)
{
  Q_D(MDeclarativeClipboard);
  d->clipboard->setText(newTheme);
}

void MDeclarativeClipboard::onChanged()
{
  QString current;
  Q_D(MDeclarativeClipboard);
  
  current = this->text();
  if (d->clipboard_text != current) {
    d->clipboard_text = current;
    emit textChanged();
  }
}
