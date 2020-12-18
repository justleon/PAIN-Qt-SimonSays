import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import "logic.js" as Logic

Window {
    id: root
    width: 600
    height: 750
    visible: true
    title: "Simon Says!"

    property int panelSize: 3
    property double score: 0.0
    property double combo: 1.0
    property int lives: 3
    property int attempts: 0
    property bool isPlayerTurn: false
    property bool isGamePlayed: false

    property variant aiSequence: []
    property variant playAiSequence: []
    property variant playerSequence: []

    //GUI
    GridLayout {
        id: mainLayout
        anchors.fill: parent
        rows: 2

        //tool bar
        Rectangle {
            Layout.row: 0
            Layout.fillWidth: true
            Layout.minimumHeight: root.height * 0.15

            id: settings
            width: root.width
            height: root.height * 0.12

            anchors.top: root.top
            color: "lightgray"

            RowLayout {
                anchors.fill: parent

                Button {
                    id: startButton
                    text: "Start"
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: Logic.startNew()
                }

                Button {
                    id: stopButton
                    text: "Stop"
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: Logic.stopGame()
                }

                Button {
                    id: propertiesButton
                    text: "Properties"
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: {
                        Logic.stopGame()
                        propertiesDialog.open()
                    }
                }

                Button {
                    id: exitButton
                    text: "Exit"
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: Qt.quit()
                }
            }
        }

        //buttons panel
        Grid {
            Layout.row: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            id: buttonsGrid
            rows: root.panelSize
            columns: root.panelSize
            spacing: 5
            anchors.margins: 5

            property real buttonWidth: (width - (columns - 1) * spacing) / columns
            property real buttonHeight: (height - (rows - 1) * spacing) / rows
            property int lightUpTime: 750

            Repeater {
                id: buttonsPanel
                model: root.panelSize * root.panelSize

                Rectangle {
                    id: button
                    property int idx: index
                    property alias animAccess: lightUp

                    height: buttonsGrid.buttonHeight
                    width: buttonsGrid.buttonWidth
                    color: ma.pressed ? "darkred" : "gray"
                    radius: width * 0.1

                    MouseArea {
                        id: ma
                        anchors.fill: parent
                        onClicked: Logic.playerTurn(idx)
                    }

                    SequentialAnimation on color {
                        id: lightUp
                        running: false
                        onRunningChanged: {
                            if(!lightUp.running) Logic.checkSequence()
                        }

                        ColorAnimation {
                            to: "darkgreen"
                            duration: buttonsGrid.lightUpTime
                        }

                        ColorAnimation {
                            to: "gray"
                            duration: buttonsGrid.lightUpTime
                        }
                    }
                }
            }
        }

        //stats bar
        Rectangle {
            Layout.row: 2
            Layout.fillWidth: true
            Layout.minimumHeight: root.height*0.1

            id: statisticsBar
            width: root.width
            height: root.height * 0.1

            anchors.top: root.bottom
            Layout.leftMargin: 1
            Layout.rightMargin: 1
            color: "lightgray"

            RowLayout {
                anchors.fill: parent
                spacing: 10

                Repeater {
                    id: statistics
                    model: [
                        "Combo: " + root.combo.toFixed(1),
                        root.score,
                        "Tries: " + (root.lives - root.attempts)
                    ]

                    Text {
                        width: settings.width
                        height: settings.height
                        horizontalAlignment: Text.AlignHCenter
                        fontSizeMode: Text.Fit
                        font.pixelSize: parent.height/2
                        text: modelData

                        Layout.fillWidth: true
                        Layout.minimumWidth: 25
                        Layout.preferredWidth: 25
                        Layout.maximumHeight: settings.height/2
                    }
                }
            }
        }
    }

    //settings window
    Dialog {
        id: propertiesDialog
        modality: Qt.WindowModal
        title: "Properties"

        onButtonClicked: {
            if(clickedButton === StandardButton.Ok) {
                root.panelSize = settingSize.currentValue
                root.lives = settingLives.currentValue
                buttonsGrid.lightUpTime = settingLightUpTime.currentValue
            }
        }

        ColumnLayout {
            width: parent.width

            //panel size
            Label {
                text: "Panel size"
                Layout.fillWidth: true
            }

            ComboBox {
                id: settingSize
                model: ["2", "3", "4"]
                currentIndex: 1
                Layout.fillWidth: true
            }

            //button light up time
            Label {
                text: "Button light up time"
                Layout.fillWidth: true
            }

            ComboBox {
                id: settingLightUpTime
                model: ["500", "750", "1000"]
                currentIndex: 1
                Layout.fillWidth: true
            }

            //maximum tries
            Label {
                text: "Possible attempts"
                Layout.fillWidth: true
            }

            ComboBox {
                id: settingLives
                model: ["1", "2", "3", "4", "5"]
                currentIndex: 2
                Layout.fillWidth: true
            }
        }
    }

    //game over window
    Dialog {
        id: gameOverDialog
        modality: Qt.WindowModal
        title: "Game Over!"

        ColumnLayout {
            width: parent.width

            Label {
                text: "Game Over!\nYou did your best!"
                horizontalAlignment: Label.AlignHCenter
                Layout.fillWidth: true
            }
        }
    }
}
