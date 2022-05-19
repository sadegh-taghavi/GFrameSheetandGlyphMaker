import QtQuick 2.3
import QtMultimedia 5.5

Item{
    objectName:"anim"
    property alias bGNDSource: img.source;
    property alias bGNDVisible: img.visible;
    property alias bGNDColor: rec.color;
    property alias source: ani.source;
    property alias frameWidth: ani.frameWidth;
    property alias frameHeight: ani.frameHeight;
    property alias frameCount: ani.frameCount;
    property alias frameRate: ani.frameRate;
    property alias interpolate: ani.interpolate;
    property alias loops: ani.loops;
    property alias paused: ani.paused;
    property alias running: ani.running;
    property alias reverse: ani.reverse;

    function zoomIn()
    {
        ani.scale += 0.1;
    }
    function zoomOut()
    {
        if( ani.scale <= 0.2 )
            return;
        ani.scale -= 0.1;
    }
    function zoom11()
    {
        ani.scale = 1.0;
    }

    function playForce()
    {
        if( ani.paused === true )
            ani.paused = false;
        else
            ani.running = true;
    }
    function nF()
    {
        if( ani.currentFrame >= ani.frameCount )
            return;
        ani.currentFrame++;
    }
    function bF()
    {
        if( ani.currentFrame <= 0 )
            return;
        ani.currentFrame--;
    }

    Rectangle{
        id:rec;
        anchors.fill: parent
        color: "black"
    }

    Image {
            id:img;
            anchors.fill: parent;
            visible:false;
        }
    AnimatedSprite{
        id:ani
        anchors.fill: parent
        frameWidth: 256
        frameHeight: 256
        frameCount: 16
        frameRate: 16
        interpolate: true
        loops: -1;
        running: true;
//        onRunningChanged: {
//            if( !running )
//                running = true;
//        }


    }


}
