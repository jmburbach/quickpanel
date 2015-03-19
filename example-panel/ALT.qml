import QtQuick 2.3
import QtGraphicalEffects 1.0
import QuickPanel 1.0

Item {
	property var altitude: quickpanel.getProperty('indicated_altitude_ft')
	property var pressure: quickpanel.getProperty('altimeter_setting_inhg')

	width: 256 * scaleFactor
	height: 256 * scaleFactor
	
	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}

	clip: true
	
	Image {
		id: face_lit
		source: 'images/face-lit.png'
		opacity: lighting
	}
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
	Blend {
		width: 256
		height: 256
		foregroundSource: face_lit
		source: alt_inhg
		mode: 'lighten'
		opacity: lighting
	}

	Image {
		id: face
		source: 'images/altimeter/alt.png'
	}
	Blend {
		width: 256
		height: 256
		foregroundSource: face_lit
		source: face
		mode: 'lighten'
		opacity: lighting
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
