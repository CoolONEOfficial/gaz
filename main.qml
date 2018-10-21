

/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6
import cpp 1.0
import QtQuick.Controls 1.2

Window {
    id: window
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
        locales: "ru_RU"
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    property var component;
    property var sprite;

    function addPoint(params, listener) {
        addComponent("component_point.qml", params, listener)
    }

    function addPolyline(params, listener) {
        addComponent("component_polyline.qml", params, listener)
    }

    function addTimePoint(params, listener) {
        addComponent("component_timepoint.qml", params, listener)
    }

    function addComponent(filename, params, listener) {

        var finished = (
                    function() {
                        if(component.status == Component.Ready) {
                            sprite = component.createObject(map, params);

                            if(sprite == null)
                                console.log("shit")
                            else {
                                map.addMapItem(sprite)

                                if(typeof listener !== "undefined") {
                                    console.debug("Listener executed")
                                    listener(sprite);
                                }
                            }

                        } else if(component.status == Component.Error)
                            console.log("Error loading component:", component.errorString());
                    }
                    );

        component = Qt.createComponent(filename);

        if(component.status == Component.Ready)
            finished();
        else
            component.statusChanged.connect(finished);
    }

    function latlng2distance(lat1, long1, lat2, long2) {
        //радиус Земли
        var R = 6372795;
        //перевод коордитат в радианы
        lat1 *= Math.PI / 180;
        lat2 *= Math.PI / 180;
        long1 *= Math.PI / 180;
        long2 *= Math.PI / 180;
        //вычисление косинусов и синусов широт и разницы долгот
        var cl1 = Math.cos(lat1);
        var cl2 = Math.cos(lat2);
        var sl1 = Math.sin(lat1);
        var sl2 = Math.sin(lat2);
        var delta = long2 - long1;
        var cdelta = Math.cos(delta);
        var sdelta = Math.sin(delta);
        //вычисления длины большого круга
        var y = Math.sqrt(Math.pow(cl2 * sdelta, 2) + Math.pow(cl1 * sl2 - sl1 * cl2 * cdelta, 2));
        var x = sl1 * sl2 + cl1 * cl2 * cdelta;
        var ad = Math.atan2(y, x);
        var dist = ad * R; //расстояние между двумя координатами в метрах
        return dist
    }

    function checkCollision(one, two) {
        return latlng2distance(one.latitude, one.longitude, two.latitude, two.longitude) < 100
    }

    Connections {
        id: conn

        property var vinArr: []
        property var start
        property var end
        property var timelen

        property var switchPoint

        target: backend

        onDoSwitchPoint: {
            if(switchPoint != null)
                switchPoint.destroy()

            console.log("vpoint=", vpoint)

            addPoint({"center": vpoint}, function(sprite){switchPoint = sprite})

            map.center.latitude = vpoint.latitude
            map.center.longitude = vpoint.longitude
        }

        onDoAddTrack: {

            addPolyline({"path":vtrack.points, "line.color": vtrack.color})
//            var points = []
//            for(var mId in vtrack.points) {
//////                for(var mPointId in points)
//////                    if(checkCollision(points[mPointId], vtrack.points[mId]))
//////                        break;

//////                points.push(vtrack.points[mId])
////                addPoint({"center": QtPositioning.coordinate(vtrack.points[mId].latitude, vtrack.points[mId].longitude)})
//            }

            map.center = QtPositioning.coordinate(vtrack.points[0].latitude,vtrack.points[0].longitude)

            var vinExists = false
            var vinId
            for(var mVinId in vinArr)
                if(vinArr[mVinId] == vtrack.vin) {
                    vinExists = true;
                    vinId = mVinId
                    break;
                }

            if(!vinExists) {
                vinArr.push(vtrack.vin);
                vinId = vinArr.length
            }


            start = vtrack.points[0].timestamp
            end = vtrack.points[vtrack.points.length-1].timestamp
            timelen = end - start

//            for(var mId in vtrack.points) {
//                var mPoint = vtrack.points[mId]
//                var mTime = mPoint.timestamp - start
//                addTimePoint(
//                            {
//                                "parent": timeline,
//                                x: (5 + (mTime / timelen * (window.width - 16))),
//                                y: timeline.height / (vinArr.length+1) * vinId - 3,
//                                color: vtrack.color
//                            }
//                            )
//            }

        }
    }

    function getTimestamp(alpha)
    {
        return conn.start + alpha * (conn.end - conn.start)
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(56.33794666666667,
                                         43.881080000000004
                    ) // Gaz tech
        zoomLevel: 14

        Component.onCompleted: backend.onMapComplete()

        Rectangle {
            z: 99
            id: timeline
            color: "black"
            opacity: 0.5
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50


            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: false
                hoverEnabled: true
                preventStealing: true
            }

            Rectangle {
                id: time_slider
                color: "white"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 8
                x: parent.width / 2 - width / 2

                MouseArea{
                    id: time_slider_mouse
                    anchors.fill: parent
                    drag.target: time_slider
                    drag.axis: Drag.XAxis
                    drag.minimumX: 0
                    drag.maximumX: window.width

                    drag.onActiveChanged: {

                        console.log("mouseX=",time_slider_mouse.mouseX);
                        console.log("width=",window.width);
                        console.log("conn.timelen=",conn.timelen);

                        var pos = time_slider.x

                        console.log("pos=", pos)
                        var alpha = pos / window.width

                        if(alpha < 0)
                            alpha = 0;
                        if(alpha>1)
                            alpha = 1;

                        var ts = getTimestamp(alpha)

                        backend.onTimeSlider(ts)
                    }
                }
            }
        }
    }

    Backend{
        id: backend
    }

//    ListModel {
//        id: model
//        ListElement {
//            name:'abc'
//            number:'123'
//        }
//        ListElement {
//            name:'efg'
//            number:'456'
//        }
//        ListElement {
//            name:'xyz'
//            number:'789'
//        }
//    }



    Rectangle {
        width: 200
        height: 100
        y: 120

        ListModel {
            id: dataModel

            ListElement {
                color: "orange"
                text: "X9600000000000068"
                val: "aaa"
            }
            ListElement {
                color: "lightgreen"
                text: "X9600000000000225"
                val: "bbb"
            }
            ListElement {
                color: "orchid"
                text: "X9600000000000430"
                val: "ccc"
            }
        }

        ListView {
            id: view

            anchors.margins: 2
            anchors.fill: parent
            spacing: 2
            model: dataModel
            clip: true

            highlight: Rectangle {
                color: "skyblue"
            }
            highlightFollowsCurrentItem: true

            delegate: Item {
                id: listDelegate

                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                width: view.width
                height: 30

                Rectangle {
                    anchors.margins: 5
                    anchors.fill: parent
                    radius: height / 2
                    color: model.color
                    border {
                        color: "black"
                        width: 1
                    }

                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {view.currentIndex = model.index;
                                    console.log(model.index, model.text, model.val);
                            backend.onVinSelect(model.text)

                        }
                    }
                }
            }
        }
    }

//------------------------


    Rectangle {
        width: 200
        height: 70
        y: 50

        ListModel {
            id: dataModelMenu

            ListElement {
                color: "red"
                text: "Fuel control"
                val: "aaa"
            }
            ListElement {
                color: "blue"
                text: "Speed info"
                val: "bbb"
            }

        }

        ListView {
            id: viewMenu

            anchors.margins: 2
            anchors.fill: parent
            spacing: 2
            model: dataModelMenu
            clip: true

            highlight: Rectangle {
                color: "skyblue"
            }
            highlightFollowsCurrentItem: true

            delegate: Item {
                id: listDelegateMenu

                property var view: ListView.viewMenu
                property var isCurrent: ListView.isCurrentItem

                width: viewMenu.width
                height: 30

                Rectangle {
                    anchors.margins: 5
                    anchors.fill: parent
                    radius: height / 2
                    color: model.color
                    border {
                        color: "black"
                        width: 1
                    }

                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {viewMenu.currentIndex = model.index;
                                    console.log(model.index, model.text, model.val);}
                    }
                }
            }
        }
    }




//    Button {
//        x:5
//        y:100
//        text: "Button"
//        onClicked:
//            backend.test()
//    }

}
