import QtQuick 2.0
import QtQml.Models 2.12
import Qt.SafeRenderer 1.2

QtObject {

    id: root

    enum Telltales {
        Headlights,
        Battery,
        Coolant,
        Oil,
        Parkinglights,
        Warning
    }

    property ObjectModel showingTelltales: ObjectModel {

    }

    property ObjectModel allTelltales: ObjectModel {
        HeadlightTelltale { width: 70; height: 70; type: TelltaleManager.Telltales.Headlights }
        PictureTelltale { width: 70; height: 70; type: TelltaleManager.Telltales.Battery; source: "telltales/battery.svg" }
        PictureTelltale { width: 70; height: 70; type: TelltaleManager.Telltales.Coolant; source: "telltales/engine-coolant.svg" }
        PictureTelltale { width: 70; height: 70; type: TelltaleManager.Telltales.Oil; source: "telltales/oil.svg" }
        PictureTelltale { width: 70; height: 70; type: TelltaleManager.Telltales.Parkinglights; source: "telltales/parking-lights.svg" }
        PictureTelltale { width: 70; height: 70; type: TelltaleManager.Telltales.Warning; source: "telltales/warning.svg" }

    }

    signal setTelltale(int telltale, bool stateOn, var stateData)

    onSetTelltale: {
        // is this a real telltale ?
        if (telltale < 0 || telltale > allTelltales.count) {
            console.log("NOT A REAL TELLTALE")
        } else {
            var isAlreadyShowing = modelContains(showingTelltales, telltale)
            var telltaleItem = allTelltales.get(telltale)
            if (!!telltaleItem) {
                telltaleItem.setState(stateData)
                safeconnect.setTelltale(telltale, stateOn, stateData)
                if (stateOn && !isAlreadyShowing) {
                    showingTelltales.append(telltaleItem)
                    telltaleItem.openAnimation()
                }
                else if (!stateOn && isAlreadyShowing) {
                    var indexToGo = modelIndexOf(showingTelltales, telltale)
                    if (!(indexToGo < 0)) {
                        showingTelltales.remove(indexToGo)
                    }
                }
            }
        }
    }

    function modelIndexOf(model, telltale) {
        for (var i = 0; i < model.count; i++) {
            var part = model.get(i)
            if (!!part && part.type === telltale)
                return i
        }
        return -1
    }

    function modelContains(model, index) {
        for (var i = 0; i < model.count; i++) {
            var part = model.get(i)
            if (!!part && part.type === index)
                return true
        }
        return false
    }
}
