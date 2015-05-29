import QtQuick 2.0
import QtQuick.Controls 1.2
import "assets" as MyAssets

Column{
    id: rootColumn
    spacing: 2
    function nassert(aId, a, bId, b){
        console.log(aId + " equals: " + a + "\n"+ bId + " equals: " + b);
        console.count("nassert called")
    }

    MyAssets.Search{
        id: columnSearch
        width: parent.width
        height: 25
    }
    ScrollView{
        id: myScrollView
        frameVisible: true
        height: parent.height-columnSearch.height
        ListView{
            id: myListView
            model: searchFilteredModel
            delegate: searchDelegate
            highlightFollowsCurrentItem: true
            spacing: 2
            highlight: Rectangle{
                color:"transparent"
                z:1
                border.color: Qt.lighter('blue')
                border.width: 1
                radius:4
            }
            highlightMoveDuration: 0

        }
    }

    Component{
        id: searchDelegate
        Rectangle{
            id: delRectangle
            height: 250
            z:0
            width: myListView.width
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
