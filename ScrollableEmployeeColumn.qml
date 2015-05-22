import QtQuick 2.0
import QtQuick.Controls 1.2
import "assets" as MyAssets
Column{
    id: rootColumn
    spacing: 2
    MyAssets.Search{
        id: columnSearch
        width: parent.width
        height: 25
        property int increment;
        property string check: "";
//        onHasText: {
//            for(increment =0; artificalModel.get(increment)<=artificalModel.count; increment++){
//                check = searchText;
//                if(check != artificalModel.get(incriment))
//            }
//        }
    }
    ScrollView{
        id: myScrollView
        frameVisible: true
        height: parent.height-columnSearch.height
        ListView{
            id: artificalListView
            model: artificalModel
            delegate: artificalDelegate
        }
    }
    ListModel{
        id: artificalModel
        ListElement{
            name: "apple"
            colour: "red"
        }
        ListElement{
            name: "banana"
            colour: "yellow"
        }
        ListElement{
            name: "carrot"
            colour: "orange"
        }
        ListElement{
            name: "duran"
            colour: "brown"
        }
        ListElement{
            name: "apple"
            colour: "red"
        }
        ListElement{
            name: "banana"
            colour: "yellow"
        }
        ListElement{
            name: "carrot"
            colour: "orange"
        }
        ListElement{
            name: "duran"
            colour: "brown"
        }
        ListElement{
            name: "apple"
            colour: "red"
        }
    }
    Component{
        id: artificalDelegate
        Rectangle{
            width: rootColumn.width
            height: 75
            Text{
                anchors.fill: parent
                text: name
            }
            color: colour
        }
    }
}
