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

#include "msystemdirectories.h"

#include <QString>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include <cstdlib>

namespace {
QString cacheDirPrefix = QString();
QString themeDirPrefix = QString();
bool prefixChanged = false;
}

QString MSystemDirectories::systemThemeDirectory()
{
    static QString themeDir;
    themeDir = qgetenv("M_THEME_DIR");

    if (themeDir.isEmpty() || prefixChanged) {
        themeDir  = themeDirPrefix;
        themeDir += THEME_DIR;
    }
    return themeDir;
}

QString MSystemDirectories::systemThemeCacheDirectory()
{
    return cacheDirectory();
}

QString MSystemDirectories::cacheDirectory()
{
    static QString cacheDir;
    if (cacheDir.isEmpty() || prefixChanged) {
        cacheDir = cacheDirPrefix;
        cacheDir += CACHE_DIR;

        // first check if we can write to CACHEDIR
        QDir().mkpath(cacheDir);
        QFileInfo cacheDirInfo(cacheDir);
        if (!(cacheDirInfo.isWritable() && cacheDirInfo.isDir())) {
            // now we try a standard cache location
            cacheDir = cacheDirPrefix + QDesktopServices::storageLocation(QDesktopServices::CacheLocation) + QDir::separator() + QLatin1String("meegotouch");
            QDir().mkpath(cacheDir);
            cacheDirInfo.setFile(cacheDir);
            if (!cacheDirInfo.isWritable() && cacheDirInfo.isDir()) {
                qCritical() << "No writable cache directory found. Make sure that either" << QString(CACHE_DIR) << "or" << cacheDir << "are writable.";
                //_exit(EXIT_FAILURE);
            }
        }

        prefixChanged = false;
    }
    return cacheDir;
}

void MSystemDirectories::setPrefix(const QString &prefix)
{
    cacheDirPrefix = prefix;
    themeDirPrefix = prefix;
    prefixChanged = true;
}

