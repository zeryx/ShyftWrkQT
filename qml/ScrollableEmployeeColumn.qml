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
            property var lastIndex;
            onCurrentIndexChanged: {
                if(lastIndex || myListView.currentIndex !==0){
                    aAgLoader.timeToLoad(myListView.currentIndex)
                    lastIndex = currentIndex
                }
            }
        }

    Component{
        id: searchDelegate
        Rectangle{
            id: delRectangle
            height: 250
            width: myListView.width
            border.width: 2
            border.color: myListView.currentIndex === index ? Qt.lighter("#0781D9") : "transparent"
            MyAssets.Clickable{
                id: portraitText
                source: portrait
                smooth: true
                antialiasing: true
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                height: 150
                fillMode: Image.PreserveAspectFit
                overlayOpacity: 0.4
                onClicked: {
                    myListView.currentIndex = index;
                }
            }
            Text{
                id: nameText
                text: name
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: portraitText.bottom
            }
            Text{
                id: positionText
                anchors.top: nameText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: position
            }
            Text{
                id:scoreText
                anchors.top: positionText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: score
            }
        }
    }
}


