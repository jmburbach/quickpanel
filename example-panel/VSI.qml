import QtQuick 2.3
import QtGraphicalEffects 1.0
import QuickPanel 1.0


Item {
	property var verticalSpeed: quickpanel.getProperty('vertical_speed_fpm')

	width: 256 * scaleFactor
	height: 256 * scaleFactor
	
	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}

	Image {
		id: face
		source: "images/vsi/vsi.png"
	}
	Image {
		id: face_lit
		source: 'images/face-lit.png'
		opacity: lighting
	}
	Blend {
		width: 256
		height: 256
		foregroundSource: face_lit
		source: face
		mode: 'lighten'
		opacity: lighting
	}
	SharedNeedle {
		id: vsi_needle;
		initialRotation: -90.0
		Interpolation on needleAngle {
			input: verticalSpeed.value
			interpolation: [
				[-6000, -170],
				[-4000, -125],
				[-2000, -80],
				[-1000, -40],
				[0, 0],
				[1000, 40],
				[2000, 80],
				[4000, 125],
				[6000, 170],
			]
		}
	}
	Text {
		text: verticalSpeed.value
		x: 15
		y: 15
		color: '#ffffff'
	}
}
