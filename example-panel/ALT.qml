import QtQuick 2.3

import "qrc:js/util.js" as Util
import QuickPanel 1.0

Item {
	property var altitude: quickpanel.getProperty('indicated_altitude_ft')
	property var pressure: quickpanel.getProperty('altimeter_setting_inhg')
	property double scaleFactor: 1.0

	width: 256 * scaleFactor
	height: 256 * scaleFactor
	
	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}

	clip: true

	Image {
		id: alt_inhg
		source: 'images/altimeter/altpres.png'
		transform: [
			Rotation {
				id: vsi_rot
				origin.x: 128
				origin.y: 128
				PropertyInterpolator on angle {
					propertyName: "altimeter_setting_inhg"
					interpolation: [
						[27.9, 210],
						[28.5, 150],
						[29.0, 100],
						[29.5, 50],
						[30.0, 0.0],
						[30.5, -50],
						[31.0, -100],
						[31.9, -149]
					]
				}
			}
		]
	}
	Image {
		id: alt_face
		source: 'images/altimeter/alt.png'
	}
	Image {
		id: alt_needle_10k
		source: "images/altimeter/needle_10k.png"
		transform: [
			Translate {
				x: 119
				y: 15
			},
			Rotation {
				origin.x: 130
				origin.y: 128
				angle: altitude.value * 0.0036
			}
		]
	}
	Image {
		id: alt_needle_1k
		source: "images/altimeter/needle_1k.png"
		transform: [
			Translate {
				x: 122
				y: 58
			},
			Rotation {
				origin.x: 130
				origin.y: 128
				angle: altitude.value * 0.036
			}
		]
	}
	SharedNeedle {
		id: alt_needle
		needleAngle: altitude.value * 0.36
	}
	Text {
		text: altitude.value + " | " + pressure.value
		x: 15
		y: 15
		color: '#ffffff'
	}
}
