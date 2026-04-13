# direct_air_capture

Arduino-based direct air capture system for extracting CO₂ from ambient air and storing it in a tank.  
🚀 A prototype showing hardware control, sensor monitoring, gas capture logic, and CAD-supported enclosure design.

![Prototype schematic or mockup](./assets/prototype-image.png)

## Project Summary

This repository contains the main Arduino sketch and supporting design assets for a direct air capture prototype. The system uses pressure, temperature, and CO₂ sensors to manage air flow, vacuum, heating, and storage stages.

The project demonstrates:

- 🧠 embedded Arduino control logic
- 🧪 analog sensor monitoring and serial debugging
- 💨 actuator control for fans, valves, heater, and vacuum
- 🛠️ CAD-based hardware design and assembly planning
- 📁 documentation-ready structure for prototyping

## What the System Does

- 🌡️ reads pressure, temperature, CO₂, and chamber pressure sensors
- 🌀 controls air flow, vacuum creation, heating, and storage
- 🧾 routes captured air through the sorbent/collection assembly
- 📡 displays live values on a 16x2 LCD and sends telemetry over Serial

## Key Files

- `Mega_Project_Final_Code.ino` — main Arduino sketch
- `README.md` — project overview and usage guide
- `Documents/3D Design/` — CAD parts for the sorbent panel and assembly

## Hardware Components

Typical components used in this prototype:

- 🧠 Arduino board (Uno, Nano, Mega, etc.)
- 🌿 CO₂ sensor module connected to `A2`
- 🧪 pressure sensors on `A0` and `A3`
- 🌡️ temperature sensor on `A1`
- 💨 fan or pump driver on pin `23`
- 🔧 solenoid valves `SV1`–`SV5` on pins `27`, `31`, `35`, `39`, `43`
- 🔋 vacuum compressor driver on pin `47`
- 🔌 heater control on pin `29`
- 🖥️ 16x2 LCD display wired via `LiquidCrystal` pins

## System Workflow

1. ⚙️ `setup()` initializes the LCD, serial port, sensors, and actuators.
2. 🔄 `loop()` cycles through:
   - `dis()` — read sensors and update LCD/Serial
   - `Air_Flow()` — open flow path and circulate air
   - `vacuum()` — close valves and engage vacuum
   - `heat()` — heat the chamber and monitor temperature
   - `store()` — manage final pressurization and storage
3. 🧭 Control decisions are based on measured analog values and safety thresholds.

## Operational Stages

- `Air_Flow()` — configures valves and fan to direct air through capture assembly
- `vacuum()` — closes flow valves, starts compressor, and creates negative pressure
- `heat()` — powers heater while monitoring temperature
- `store()` — manages final storage flow and chamber pressure

## 3D Design Assets

The `Documents/3D Design/` folder contains CAD files for the mechanical parts of the prototype, including:

- `sorbent panel.IGS`
- `I-section of sorbent panel.IGS`
- `100mm.CATPart`
- `150mm.CATPart`
- `left.CATPart`
- `right.CATPart`
- `Part1.CATPart`

These files can be used to visualize or manufacture the capture assembly and support structure.

## How to Use

1. 📝 Open `Mega_Project_Final_Code.ino` in Arduino IDE.
2. 🔌 Connect the Arduino to your PC.
3. 🔧 Wire the sensors and actuators according to the pin assignments in the sketch.
4. 🖥️ Select the correct board and COM port.
5. 📤 Upload the sketch.
6. 📟 Open Serial Monitor at `9600` baud and watch the LCD for live data.

## Recommended Enhancements

To make the project stronger and more portfolio-ready:

- 📊 add actual sensor mapping and calibration formulas
- 🧾 document the exact wiring and pin mapping
- 🧰 include a bill of materials (BOM)
- 📐 add a wiring diagram or schematic image
- 🎥 include photos or a demo video of the prototype
- 💾 add data logging or SD card export

## Notes

- ✅ Verify sensor wiring before powering the system.
- ⚠️ Calibrate the CO₂ sensor and temperature probe for accurate readings.
- 🔌 Ensure safe power, valve, and heater connections.

## License

This project is available for learning and experimentation. Add a license file if you want to define reuse terms explicitly.
