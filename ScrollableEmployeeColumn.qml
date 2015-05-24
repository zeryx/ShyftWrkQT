import QtQuick 2.0
import QtQuick.Controls 1.2
import "assets" as MyAssets
Column{
    id: rootColumn
    spacing: 2
    signal removeInst;
    MyAssets.Search{
        id: columnSearch
        width: parent.width
        height: 25
        property int incrementIndex;
        property int incrementString;
        property int ind: 0
        property int searchTextSize;
        property int visibleItr;
        property bool called;
        //when search has text, check all model data to see if the names match, if they don't, remove from view
        onHasText: {
            for(incrementIndex =0; incrementIndex < artificalModel.count; incrementIndex++){
                searchTextSize = searchText.length
                console.log("current item: " + artificalModel.get(incrementIndex).fruitName + " index #"+incrementIndex)
                for(incrementString=0; incrementString <= searchTextSize; incrementString++)
                {
                    console.log("search letter: " + searchText.charAt(incrementString))
                    console.log("model letter: "+ artificalModel.get(incrementIndex).fruitName.charAt(incrementString))

                    if(searchText.charAt(incrementString) !== artificalModel.get(incrementIndex).fruitName.charAt(incrementString) && searchText.charAt(incrementString) !== "")
                    {
                        artificalModel.get(incrementIndex).visibleItem = false;
                        break;
                    }
                }
            }
        }
            // need a way to mask listModels based on visibleItem bool, will figure out later
    }
    ScrollView{
        id: myScrollView
        frameVisible: true
        height: parent.height-columnSearch.height
        ListView{
            id: artificalListView
            model: artificalModel
            delegate: artificalDelegate
            addDisplaced: Transition{
                NumberAnimation{ properties: "x,y"; duration: 500;}
            }
        }
    }


    ListModel{
        id: artificalModel
        ListElement{
            fruitName: "apple"
            fruitColor: "red"
            visibleItem: true
        }
        ListElement{
            fruitName: "banana"
            fruitColor: "yellow"
            visibleItem: true
        }
        ListElement{
            fruitName: "apricot"
            fruitColor: "orange"
            visibleItem: true
        }
        ListElement{
            fruitName: "duran"
            fruitColor: "brown"
            visibleItem: true
        }
        ListElement{
            fruitName: "apple"
            fruitColor: "red"
            visibleItem: true
        }
    }
    ListModel{
        id: temporaryModel
    }

    Component{
        id: artificalDelegate
        Rectangle{
            width: rootColumn.width
            height: 75
            Text{
                anchors.fill: parent
                text: fruitName
            }
            property bool visibleItem;
            color: fruitColor
        }
    }
}
