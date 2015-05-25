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
        property int incrIndex;
        property int searchTextSize;
        property int incrStr;
        //when search has text, check all model data to see if the names match, if they don't, remove from view
        onHasText: {
//            searchTextSize = searchText.length-1
//            for(incrIndex =0; incrIndex < columnModel.count; incrIndex++){

//                for(incrStr=0; incrStr<=searchTextSize; incrStr++)
//                {

//                    if(searchText.charAt(incrStr) !== columnModel.get(incrIndex).fruitName.charAt(incrStr))
//                    {
//                        columnModel.get(incrIndex).visibleItem = false;
//                        break;
//                    }
//                    //but if they do, make sure its visible
//                    else{
//                        columnModel.get(incrIndex).visibleItem = true;
//                    }
//                }
//                //if the textbox is empty, everything should be visible (not sure why line 22 wouldn't notice this
//                if(searchText.charAt(searchTextSize) == "")
//                    columnModel.get(incrIndex).visibleItem = true;
//            }
        }
    }
    ScrollView{
        id: myScrollView
        frameVisible: true
        height: parent.height-columnSearch.height
        ListView{
            id: artificalListView
            model: MyModel
            delegate: searchDelegate
        }
    }

    Component{
        id: searchDelegate
        Rectangle{
            height: 75
            width: rootColumn.width
            Text{
                anchors.fill: parent
                text:modelData.myName
            }
            color: modelData.myColor
        }
    }
}
