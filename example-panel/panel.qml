import QtQuick 2.3

Item {
	width: childrenRect.width
	height: childrenRect.height

	ASI {
		id: asi
		scaleFactor: 1.25
	}

	MDI {
		id: mdi
		x: asi.width
		y: asi.height
		scaleFactor: 1.25;
	}

	VSI {
		id: vsi
		x: asi.width + mdi.width
		y: asi.height
		scaleFactor: 1.25
	}

	ALT {
		id: alt
		x: asi.width + mdi.width
		scaleFactor: 1.25
	}
	
	MouseArea {
		anchors.fill: parent
		onClicked: {
			Qt.quit();
		}
	}
}
