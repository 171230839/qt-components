import Qt 4.6
import Components 1.0

Item {
    id: button;
    width: 200;
    height: 64;

    property alias checkable: model.checkable;
    property alias autoExclusive: model.autoExclusive;
    property alias text: label.text;

    BorderImage {
        id: releasedImage;
        anchors.fill: parent;
        visible: !model.buttonDown && !model.checked;
        source: "images/button.svg"

        border.left: 10;
        border.right: 10;
        border.top: 10;
        border.bottom: 10;
    }

    BorderImage {
        id: pressedImage;
        anchors.fill: parent;
        visible: model.buttonDown && !model.checked;
        source: "images/button-pressed.svg"

        border.left: 10;
        border.right: 10;
        border.top: 10;
        border.bottom: 10;
    }

    BorderImage {
        id: releasedSelectedImage;
        anchors.fill: parent;
        visible: !model.buttonDown && model.checked;
        source: "images/button-selected.svg"

        border.left: 10;
        border.right: 10;
        border.top: 10;
        border.bottom: 10;
    }

    BorderImage {
        id: pressedSelectedImage;
        anchors.fill: parent;
        visible: model.buttonDown && model.checked;
        source: "images/button-selected-pressed.svg"

        border.left: 10;
        border.right: 10;
        border.top: 10;
        border.bottom: 10;
    }

    Text {
        id: label;
        anchors.fill: parent;

        horizontalAlignment: "AlignHCenter";
        verticalAlignment: "AlignVCenter";

        font.family: "Nokia Sans";
        font.pixelSize: 24;
        color: releasedImage.visible ? "#000000" : "#FFFFFF";

        text: "Effect";
    }

    MouseArea {
        id: mouseArea;
        anchors.fill: parent;
    }

    ButtonModel {
        id: model;

        checkable: true;
        // autoExclusive: true;

        mousePressed: mouseArea.pressed;
        mouseOver: mouseArea.containsMouse;
    }
}
