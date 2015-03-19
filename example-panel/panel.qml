import QtQuick 2.3

Item {
	width: childrenRect.width
	height: childrenRect.height

	property var lightingProp: quickpanel.getProperty("panel_lighting")
	property double lighting: parseFloat(lightingProp.value)
	property double scaleFactor: 1.25

	ASI {
		id: asi
	}

	MDI {
		id: mdi
		x: asi.width
		y: asi.height
	}

	VSI {
		id: vsi
		x: asi.width + mdi.width
		y: asi.height
	}

	ALT {
		id: alt
		x: asi.width + mdi.width
	}

	MP12 {
		id: mp12
		x: alt.x + alt.width
	}
	MP34 {
		id: mp34
		x: mp12.x + mp12.width
	}

	RPM12 {
		id: rpm12
		x: mp12.x
		y: mp12.y + height
	}
	RPM34 {
		id: rpm34
		x: rpm12.x + width
		y: rpm12.y
	}

	MouseArea {
		anchors.fill: parent
		onClicked: {
			Qt.quit();
		}
	}
}
