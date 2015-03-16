import QtQuick 2.3

import "qrc:js/util.js" as Util

Item {
	property var heading: quickpanel.getProperty('indicated_heading_deg')
	property double scaleFactor: 1.0

	width: 256 * scaleFactor
	height: 256 * scaleFactor

	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}

	Image {
		id: mdi_compass
		source: "images/mdi/compass_mdi.png"
		rotation: -(parseFloat(heading.value)||360)
	}
	Image {
		id: mdi_shadow
		source: "images/mdi/compass_mdi_shadow.png"
		opacity: 0.65
	}
	Image {
		id: mdi_face
		source: "images/mdi/compass_mdi_face.png"
	}
	Text {
		text: heading.value
		x: 15
		y: 15
		color: '#ffffff'
	}
}
