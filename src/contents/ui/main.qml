// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 illusion <vladyslav.makarov1@nure.ua>

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.Kirigami_DB 1.0

Kirigami.ApplicationWindow {
    id: root

    title: i18n("Kirigami_DB")

    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    onClosing: App.saveWindowGeometry(root)

    onWidthChanged: saveWindowGeometryTimer.restart()
    onHeightChanged: saveWindowGeometryTimer.restart()
    onXChanged: saveWindowGeometryTimer.restart()
    onYChanged: saveWindowGeometryTimer.restart()

    Component.onCompleted: App.restoreWindowGeometry(root)

    // This timer allows to batch update the window size change to reduce
    // the io load and also work around the fact that x/y/width/height are
    // changed when loading the page and overwrite the saved geometry from
    // the previous session.
    Timer {
        id: saveWindowGeometryTimer
        interval: 1000
        onTriggered: App.saveWindowGeometry(root)
    }

    property int counter: 0

    globalDrawer: Kirigami.GlobalDrawer {
        title: i18n("Kirigami_DB")
        titleIcon: "applications-graphics"
        isMenu: !root.isMobile
        actions: [
            Kirigami.Action {
                text: "Plus One"
                icon.name: "list-add"
                onTriggered: {
                    counter += 1
                }
            },
            Kirigami.Action {
                text: "About Kirigami_DB"
                icon.name: "help-about"
                onTriggered: pageStack.layers.push('qrc:About.qml')
            },
            Kirigami.Action {
                text: "Quit"
                icon.name: "application-exit"
                onTriggered: Qt.quit()
            }
        ]
    }

    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: page

    Kirigami.ScrollablePage {
        id: page

        Layout.fillWidth: true

        title: "Stones"

        ListView
        {

            interactive: true

            spacing: 30
            clip: true
            header: Kirigami.ItemViewHeader {
                backgroundImage.source: "https://www.wallpaperup.com/uploads/wallpapers/2012/09/03/12512/0729517a901dbcbe959a6ddaaea2a0fe.jpg"
                title: page.title
            }

            headerPositioning: ListView.OverlayHeader

            model: DBModel

            delegate: Kirigami.AbstractCard {
                implicitWidth: page.width*0.9
                clip: true
                contentItem: Item {
                    implicitWidth: page.width*0.9
                    implicitHeight: delegateLayout.implicitHeight
                    GridLayout {
                        id: delegateLayout
                        anchors {
                            left: parent.left
                            top: parent.top
                            right: parent.right
                            //IMPORTANT: never put the bottom margin
                        }
                        rowSpacing: Kirigami.Units.largeSpacing
                        columnSpacing: Kirigami.Units.largeSpacing
                        columns: width > Kirigami.Units.gridUnit * 20 ? 4 : 2

                        Kirigami.Icon {
                            source: "https://freepngimg.com/thumb/minecraft/11-2-minecraft-diamond-png.png"
                            Layout.fillHeight: true
                            Layout.maximumHeight: Kirigami.Units.iconSizes.huge
                            Layout.preferredWidth: height
                        }
                        ColumnLayout {
                            Kirigami.Heading {
                                level: 2
                                text: model.display
                            }
                            Kirigami.Separator {
                                Layout.fillWidth: true
                            }
                            Controls.Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: model.description
                            }
                        }
                        Controls.Button {
                            Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
                            Layout.columnSpan: 2
                            text: "Show more"
                        }
                    }
                }

            }
        }
    }
}
