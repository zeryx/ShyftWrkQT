import QtQuick 2.0
import QtGraphicalEffects 1.0
Image {
    id: root
    visible: true
    focus: true
    smooth: true
    fillMode: Image.PreserveAspectFit
    property color color: "white"
    property color hoverColor: "#aaaaaa"
    property color pressColor: "slategray"
    property int fontSize: 10
    property int borderWidth: 1
    property int borderRadius: 2
    property real overlayOpacity: 1
    scale: state === "Pressed" ? 0.96 : 1.0
    onEnabledChanged: state = ""
    signal clicked

    //an easier way to change the dimensions of the button
    Behavior on scale{
        NumberAnimation{
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }




    //defining the mouse area signals for the button
    MouseArea{
        id: rootMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {root.state='Hovering'}
        onExited: {root.state=''}
        onPressed:{root.state='Pressed'}
        onReleased:{
            if(containsMouse)
                root.state="Hovering";
            else
                root.state="";
        }
        onClicked: {root.clicked();}
    }
    //define the color changing states for the button using the colorOverlay
    states: [
        State{
            name: "Hovering"
            PropertyChanges {
                target: rootOverlay
                color: hoverColor
            }
        },
        State{
            name: "Pressed"
            PropertyChanges {
                target: rootOverlay
                color: pressColor
            }
        }
    ]
    //define how the colors & geometry transitions for each state

    transitions: [
        Transition{
            from: ""; to:"Hovering"
            ColorAnimation {
                duration: 2000
                easing.type: Easing.InOutQuad
            }
        },
        Transition{
            from: "*"; to: "Pressed"
            ColorAnimation{
                duration: 100
                easing.type: Easing.InOutQuad
            }
        }
    ]
    ColorOverlay{
        id: rootOverlay
        anchors.fill:root
        source: root
        color: "transparent"
        opacity: overlayOpacity
        z:1
    }
}
