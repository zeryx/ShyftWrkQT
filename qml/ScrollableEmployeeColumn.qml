import QtQuick 2.0
import QtQuick.Controls 1.2
import "assets" as MyAssets

Column{
    id:rootColumn
    property alias listView: myListView
    MyAssets.Search{
        id: columnSearch
        width: rootColumn.width
        height: 25
        z:12
    }

        ListView
        {
            id: myListView
            model: searchFilteredModel
            width: rootColumn.width
            height: rootColumn.height-columnSearch.height
            delegate: searchDelegate
            highlightFollowsCurrentItem: true
            spacing: 2
            z:0
            signal unHideAAG(var index, var name, var score)
            onUnHideAAG: {aAgLoader.timeToLoad(index, name, score)}
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
            MyAssets.Clickable{
                id: portraitText
                source: model.portrait
                smooth: true
                antialiasing: true
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                height: 150
                fillMode: Image.PreserveAspectFit
                overlayOpacity: 0.4
                onClicked: {
                    myListView.unHideAAG(index, model.name, model.score)
                    myListView.currentIndex = index
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

            Text{
                id:scoreText
                text: model.score
                anchors.top: positionText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}


