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

import QtQuick 1.1
import Qt.labs.components.native 1.0

Loader {
    id: customLoader

    property bool debug: true
    property string path
    property string fileName

    //![Properties]
    property int attempt: 0
    property int largerDimension: Math.max(screen.displayWidth, screen.displayHeight)
    property int smallerDimension: Math.min(screen.displayWidth, screen.displayHeight)
    property int roundedDpi: Math.round(screen.dpi / 10) * 10
    property string mySource: path + "/" + largerDimension + "x" + smallerDimension + "/" + roundedDpi + "/" + fileName;
    //![Properties]

    signal loadError

    //![Display Categories]
    function displayCategory() {
        switch (screen.displayCategory) {
        case Screen.Small:
            return "Small";
        case Screen.Normal:
            return "Normal";
        case Screen.Large:
            return "Large";
        default:
            return "ExtraLarge";
        }
    }
    //![Display Categories]

    //![Density Categories]
    function densityCategory() {
        switch (screen.density) {
        case Screen.Low:
            return "Low";
        case Screen.Medium:
            return "Medium";
        case Screen.High:
            return "High";
        default:
            return "ExtraHigh";
        }
    }
    //![Density Categories]

    //![Loading]
    onMySourceChanged: {
        attempt = 0;
        if (customLoader.smallerDimension > 0 && customLoader.largerDimension > 0)
            source = mySource;
    }

    onStatusChanged: {
        if (customLoader.status == Loader.Error) {
            customLoader.attempt++;
            switch (customLoader.attempt) {
            case 1:
                source = path + "/" + largerDimension + "x" + smallerDimension + "/" + fileName;
                break;
            case 2:
                source = path + "/" + displayCategory() + "/" + densityCategory() + "/" + fileName;
                break;
            case 3:
                source = path + "/" + displayCategory() + "/" + fileName;
                break;
            case 4:
                source = path + "/" + fileName;
                break;
            default:
                customLoader.loadError();
                source = "";
            }
        } else {
            if (debug) console.log("CustomLoader: successfully loaded file: " + source);
        }
    }
    //![Loading]
}
