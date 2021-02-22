## Description

### File *interact_led_panel.ino*

With that script you can create different action on a **MAX7219 Module**.
Interact with this module using a **Membrane Switch Module** & **Joystick Module**.

### Module connection
#### - MAX7219
	 VCC: 5V
	 GND: GND
	 DIN: 12 (digital)
	 CS: 10 (digital)
	 CLK: 11 (digital)

#### - Joystick
	 +5V: 5V
	 GND: GND
	 VRx: A0 (analog)
	 VRy: A1 (analog)
	 CLK: A2 (analog)

#### - Membrane Switch
	 2 (digital) to 9 (digital)


### File *game.ino*

With that script you can create different action on a **MAX7219 Module**.
Interact with this module using **Joystick Module** and 4 buttons.

### Module connection
#### - MAX7219
	 VCC: 5V
	 GND: GND
	 DIN: 12 (digital)
	 CS: 10 (digital)
	 CLK: 11 (digital)

#### - Joystick
	 +5V: 5V
	 GND: GND
	 VRx: A0 (analog)
	 VRy: A1 (analog)
	 CLK: A2 (analog)

#### - 4 buttons
	Top Left: 5V
	Bottom Right: 2, 4, 8, 9 (digital)
	Bottom Left: 10k ohm


### File *remote_control_panel.ino*

With that script you can create different action on a **MAX7219 Module**.
Interact with this module using a **Remote Controller Module** & **Joystick Module**.

### Module connection
#### - MAX7219
	 VCC: 5V
	 GND: GND
	 DIN: 12 (digital)
	 CS: 10 (digital)
	 CLK: 11 (digital)

#### - Joystick
	 +5V: 5V
	 GND: GND
	 VRx: A0 (analog)
	 VRy: A1 (analog)
	 CLK: A2 (analog)

#### - Remote Controller
	 R: 5V
	 G: GND
	 Y: 7 (digital)
