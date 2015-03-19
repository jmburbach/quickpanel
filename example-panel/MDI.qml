import QtQuick 2.3
import QtGraphicalEffects 1.0

Item {
	property var heading: quickpanel.getProperty('indicated_heading_deg')

	width: 256 * scaleFactor
	height: 256 * scaleFactor

	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}
	Image {
		id: face_lit
		source: 'images/face-lit.png'
		opacity: lighting
	}

	Item {
		id: face
		width: 256
		height: 256

		Image {
			id: mdi_compass
			source: "images/mdi/compass_mdi.png"
			rotation: -parseFloat(heading.value)
		}
		Image {
			id: mdi_shadow
			source: "images/mdi/compass_mdi_shadow.png"
			opacity: 1
		}
		Image {
			id: mdi_face
			source: "images/mdi/compass_mdi_face.png"
		}
	}
	Blend {
		width: 256
		height: 256
		foregroundSource: face_lit
		source: face
		mode: 'lighten'
		opacity: lighting
	}
	Text {
		text: heading.value
		x: 15
		y: 15
		color: '#ffffff'
	}
}
