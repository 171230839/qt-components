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

#include "mdeclarativescalableimage.h"

#include <MScalableImage>
#include <MWidgetStyle>

Q_DECLARE_METATYPE(const MScalableImage *)

MDeclarativeScalableImage::MDeclarativeScalableImage(QDeclarativeItem *parent) :
    MDeclarativePrimitive(parent), m_image(0)
{
}

MDeclarativeScalableImage::~MDeclarativeScalableImage()
{
}

QString MDeclarativeScalableImage::imageProperty() const
{
    return m_imageProperty;
}

void MDeclarativeScalableImage::setImageProperty(const QString &imageProperty)
{
    if (m_imageProperty == imageProperty)
        return;

    m_imageProperty = imageProperty;
    updateStyleData();
}

void MDeclarativeScalableImage::clearStyleData()
{
    m_image = 0;
    setImplicitWidth(0);
    setImplicitHeight(0);
}

void MDeclarativeScalableImage::fetchStyleData(const MStyle *style)
{
    const QVariant imageVariant = style->property(m_imageProperty.toAscii());
    m_image = imageVariant.value<const MScalableImage *>();

    setImplicitWidth(0);
    setImplicitHeight(0);
}

bool MDeclarativeScalableImage::hasPendingPixmap()
{
    if (!m_image)
        return false;

    // Note that we assume that a 1x1 pixmap means an unloaded pixmap. This will fail if there
    // are actual 1x1 pixmaps in the theme.
    if (m_image->pixmap()->size() != QSize(1, 1)) {
        setImplicitWidth(m_image->pixmap()->width());
        setImplicitHeight(m_image->pixmap()->height());
        return false;
    }

    return true;
}

void MDeclarativeScalableImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!m_image)
        return;

    // XXX respect minimum size here...
    m_image->draw(boundingRect().toRect(), painter);
}

