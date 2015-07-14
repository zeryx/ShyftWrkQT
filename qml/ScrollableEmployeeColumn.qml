import QtQuick 2.3
import QtQuick.Controls 1.3
import "assets" as MyAssets

Column{
    id:rootColumn
    property alias listView: myListView
    Component.onCompleted: initialize.windowChange();
    z:-1
    MyAssets.Search{
        id: columnSearch
        width: rootColumn.width
        height: 25
        textPromptInfo: "Search"
        z:12
    }
    ListView
    {
        boundsBehavior: ListView.StopAtBounds
        id: myListView
        model: searchModel
        width: rootColumn.width
        height: rootColumn.height-columnSearch.height-addStaffButton.height-10
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
                id: viewItem
                text:qsTr("View")
                onTriggered: {
                    var viewerComponent = "MenuWidgets/ViewerWindow.qml"
                    mainWindowContext.swapApps(viewerComponent, rightclickMenu.m_model)
                }
            }

            MenuItem{
                id: editItem
                text:qsTr("Edit")
                onTriggered: {
                    var editorComponent = "MenuWidgets/EditorWindow.qml"
                    mainWindowContext.swapApps(editorComponent, rightclickMenu.m_model)
                }
            }
        }
    }
    Rectangle{
        id: addStaffBkgrd
        color: Qt.darker("grey")
        width: rootColumn.width
        height: 35
        z:1
        MyAssets.Clickable{
            id: addStaffButton
            source: "assets/icons/user-add-512px.svg"
            height: 25
            width: 25
            anchors.centerIn: parent
            onClicked:{
                var editorComponent = "MenuWidgets/EditorWindow.qml"
                mainWindowContext.swapApps(editorComponent)
            }
        }
    }

    Component{
        id: searchDelegate
        Rectangle{
            id: delRectangle
            height: portrait.height+nameText.height+15
            width: myListView.width
            border.width: 2
            border.color: myListView.currentIndex === index ? Qt.lighter("#0781D9") : "transparent"
            Rectangle{id: background; anchors.fill: parent; color: Qt.lighter(Qt.lighter("#5caa15")); z:0}
            Image{
                id: portrait
                source: model.portrait
                smooth: true
                antialiasing: true
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                height: 150
                width: 150
                fillMode: Image.PreserveAspectCrop
                onStatusChanged: {
                    if(portrait.status== Image.Loading)
                        loadingIndicator.running = true
                else if(portrait.status== Image.Ready)
                        loadingIndicator.running = false;
                }
            }
            BusyIndicator{
                z:1
                id: loadingIndicator
                anchors.centerIn: portrait
            }

            MouseArea{
                id: searchDelegateMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked:{
                    if(mouse.button === Qt.LeftButton)
                        myListView.currentIndex = index
                    else if(mouse.button === Qt.RightButton)
                    {
                        rightclickMenu.passItem(model)
                        rightclickMenu.popup()
                    }
                }
                onDoubleClicked: {
                    if(mouse.button === Qt.LeftButton){
                        rightclickMenu.passItem(model)
                        viewItem.trigger()
                    }
                }
            }

            Text{
                id: nameText
                text:{ qsTr(model.name)}
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: portrait.bottom
            }

            //            Text{
            //                id: positionText
            //                text: {qsTr(model.position)}
            //                anchors.top: nameText.bottom
            //                anchors.horizontalCenter: parent.horizontalCenter
            //            }

        }
    }
}


