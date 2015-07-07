import QtQuick 2.0
import QtQuick.Controls 1.1
Flickable{
    flickableDirection: Flickable.HorizontalFlick
    Row{
        id: root
        anchors.fill: parent
        spacing: 50
        Component.onCompleted: {
            var headers = headerList
            var model = tableModel
            var temp = []
            for(var i=0; i<headers.length; i++)
            {
                var newModel = model[i]
                temp.push(dynamicComponent.createObject(root,
                                                        {
                                                            "listModel":newModel,
                                                            "headerName":headers[i]
                                                        }))
            }
            return temp
        }

        Component{ //dynamically repeated column object
            id: dynamicComponent
            Column{
                id:thisColumn
                property string headerName //globally defined properties + signal so that components can read/write to this space
                property var listModel
                signal newLoaderSelection(var model)
                height: root.height
                width: 150
                spacing: 15
                onNewLoaderSelection: {
                    if(model)
                    {
                        thisSelectionLoader.loaderModel = model
                        thisSelectionLoader.active = false
                        thisSelectionLoader.sourceComponent = selectedComponent
                        thisSelectionLoader.active = true
                    }
                    else
                    {
                        thisSelectionLoader.active = false
                        thisSelectionLoader.sourceComponent = placeholderLoaderComponent
                        thisSelectionLoader.active = true
                    }
                }

                Loader{
                    id: thisSelectionLoader //loader for displaying selected/deselected employees for this column
                    property var loaderModel
                    width: thisColumn.width
                    height: thisColumn.width+10
                    sourceComponent: placeholderLoaderComponent
                    BorderImage {
                        id: loaderBorder
                        source: "searchbox.jpg"
                        anchors.centerIn: parent
                        width: parent.width+10; height: parent.width+20
                        border.left: 5; border.top: 5
                        border.right: 5; border.bottom: 5
                    }
                }

                ListView{
                    id: thisListView
                    delegate: tableDelegate
                    height: thisColumn.height - thisSelectionLoader.height
                    width: thisColumn.width
                    spacing: 10
                    model: thisColumn.listModel
                    header: Rectangle{
                        width: 100
                        height: 25
                        radius: 2
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "light blue"
                        Text{
                            id: headerText
                            anchors.centerIn: parent
                            text: qsTr(thisColumn.headerName)
                        }

                    }
                }

                Component{
                    id:placeholderLoaderComponent
                    Rectangle {
                        id: selectionPlaceholder
                    }
                }

                Component{
                    id:selectedComponent
                    Rectangle{
                        id:rootRectangle
                        Image{
                            id:deselectButton
                            anchors.top: parent.top
                            anchors.right: parent.right
                            source:"close_button.zvg"
                            fillMode: Image.PreserveAspectFit
                            height: 25
                            width: 25
                            z:1
                            opacity: 0.4
                            MouseArea{
                                id:deslectMouseArea
                                anchors.fill: parent
                                onReleased: thisColumn.newLoaderSelection(0)
                            }
                        }
                        Image{
                            id: portraitText
                            source: thisSelectionLoader.loaderModel.portrait
                            smooth: true
                            antialiasing: true
                            anchors.top: parent.top
                            height:100
                            width: 100
                            anchors.horizontalCenter: parent.horizontalCenter
                            fillMode: Image.PreserveAspectCrop
                        }

                        Text{
                            id: nameText
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: portraitText.bottom
                            text: qsTr(thisSelectionLoader.loaderModel.name)
                        }
                        Text{
                            id: positionText
                            anchors.top: nameText.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr(thisSelectionLoader.loaderModel.position)
                        }
                        Text{
                            id:scoreText
                            anchors.top: positionText.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: thisSelectionLoader.loaderModel.score
                        }
                    }
                }

                Component{
                    id: tableDelegate
                    Rectangle{
                        id: delRectangle
                        radius: 6
                        color: "white"
                        height: 150
                        width: parent.width
                        z:1

                        MouseArea{
                            id: tableDelegateMouseArea
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            onReleased:{
                                thisColumn.newLoaderSelection(model);
                            }
                        }

                        Image{
                            id: portraitText
                            source: model.portrait
                            smooth: true
                            antialiasing: true
                            anchors.top: parent.top

                            anchors.horizontalCenter: parent.horizontalCenter
                            height: 100
                            width: 100
                            fillMode: Image.PreserveAspectCrop
                        }

                        Text{
                            id: nameText
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: portraitText.bottom
                            text: qsTr(model.name)
                        }
                        Text{
                            id: positionText
                            anchors.top: nameText.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr(model.position)
                        }
                        Text{
                            id:scoreText
                            anchors.top: positionText.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: model.score
                        }
                    }
                }
            }
        }
    }
}
