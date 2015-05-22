import QtQuick 2.0
import QtGraphicalEffects 1.0

FocusScope {
    id: root
    signal hasText
    property alias searchText: textInput.text
    BorderImage {
        id: searchBorder
        source: "searchbox.jpg"
        width: parent.width
        height: parent.height
        border.left: 5; border.top: 5
        border.right: 5; border.bottom: 5
    }
        ColorOverlay{
            id: colorOverlay
            anchors.fill: searchBorder
            source: searchBorder
            color:"transparent"

        }

    Text{
        id:textPrompt
        anchors.fill: parent
        anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter
        text: "Who're you looking for?"
        color:"grey"
        font.family: "abel"
    }
    TextInput{
        id: textInput
        anchors.fill: searchBorder
        activeFocusOnPress: false
        z:1
        onTextChanged: {
            if(textInput.text != "")
                    root.hasText();
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(!textInput.activeFocus){
                    textInput.forceActiveFocus();
                    colorOverlay.color = "#CACACF"
                }else{
                    textInput.focus=false;
                    colorOverlay.color = "transparent"
                }
            }
        }
    }
    Image{
        id: clear
        anchors{right: parent.right; rightMargin: 8; verticalCenter:  parent.verticalCenter;}
        source: "icons/arrow_left.svg"
        opacity: 0
        MouseArea{
            anchors.fill: parent
            onClicked: {
                textInput.text = "";
                focusScope.focus = true;
            }
        }
    }
    states: State{
        name: "hasText";
        when: textInput.text != ''
        PropertyChanges {
            target: textPrompt
            opacity: 0
        }
        PropertyChanges {
            target: clear
            opacity: 1
        }
    }
    transitions:[
        Transition{
            from: ""; to: "hasText"
            NumberAnimation{
                exclude: textPrompt
                properties: "opacity"
            }
        },
        Transition{
            from: "hasText"; to: ""
            NumberAnimation{
                properties: "opacity"
            }
        }
    ]
}

