import QtQuick 2.3
import QtQuick.Controls 1.2
import "assets" as MyAssets

Column{
    id:rootColumn
    property alias listView: myListView
    MyAssets.Search{
        id: columnSearch
        width: rootColumn.width
        height: 25
        textPromptInfo: "Search"
        z:12
    }

    ListView
    {
        id: myListView
        model: searchFilteredModel
        width: rootColumn.width
        height: rootColumn.height-columnSearch.height
        delegate: searchDelegate
        spacing: 2
        focus: true
        z:0

        highlight: Rectangle {
            width: 180; height: 40
            color: "lightsteelblue"; radius: 5
            }


        Menu{
            id: rightclickMenu
            property var m_model
            signal passItem(var model)
            onPassItem: {m_model = model}
            MenuItem{
                text:qsTr("View")
                onTriggered: {
                    var viewerComponent = "MenuWidgets/ViewerWindow.qml"
                    mainWindowContext.swapApps(viewerComponent, rightclickMenu.m_model)
                }
            }

            MenuItem{
                text:qsTr("Edit")
                property string editorComponent
                onTriggered: {
                    editorComponent = "MenuWidgets/EditorWindow.qml"
                    mainWindowContext.swapApps(editorComponent, rightclickMenu.m_model)
                }
            }
        }
    }

    Component{
        id: searchDelegate
        Rectangle{
            id: delRectangle
            height: 220
            width: myListView.width
            border.width: 2
            border.color: myListView.currentIndex === index ? Qt.lighter("#0781D9") : "transparent"
            Rectangle{id: background; anchors.fill: parent; color: Qt.lighter(Qt.lighter("#5caa15")); z:0}
            Image{
                id: portraitText
                source: model.portrait
                smooth: true
                antialiasing: true
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                height: 150
                width: 150
                fillMode: Image.PreserveAspectCrop
            }
            MouseArea{
                id: searchDelegateMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onReleased:{
                    if(mouse.button === Qt.LeftButton)
                        myListView.currentIndex = index
                    else if(mouse.button === Qt.RightButton)
                    {
                        rightclickMenu.passItem(model)
                        rightclickMenu.popup()
                    }
                }
            }

            Text{
                id: nameText
                text:{ qsTr(model.name)}
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: portraitText.bottom
            }

            Text{
                id: positionText
                text: {qsTr(model.position)}
                anchors.top: nameText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }

        }
    }
}


