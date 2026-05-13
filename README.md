# 🤖 DrillBot — ESP32 RC Car with Drill Mechanism

An ESP32-powered robot that combines mobility (4 DC motors) with a deployable drill
controlled by a servo and dedicated motor driver. Controlled via Bluetooth using the
Dabble gamepad app.

---

## 📸 Demo

> *(Add your photo or video here)*

---

## ⚙️ Features

- 4 DC motors for full directional movement
- Dedicated drill motor with independent L298N driver
- Servo motor for drill positioning (clockwise / counter-clockwise)
- Active buzzer feedback when drill is running
- Bluetooth control via Dabble app (ESP32 version)

---

## 🧰 Hardware Components

| Component | Quantity |
|---|---|
| ESP32 Dev Board | 1 |
| L298N Motor Driver | 2 |
| DC Gear Motors | 4 |
| High-torque DC Drill Motor | 1 |
| Continuous Rotation Servo | 1 |
| Active Buzzer | 1 |
| 18650 Battery Pack (3S) or LiPo 11.1V | 1 |
| Buck Converter (12V → 5V) | 1 |
| Acrylic Robot Chassis | 1 |

---

## 📌 Pin Map

| ESP32 GPIO | Function |
|---|---|
| 14, 27, 26, 25 | Car Motor IN1–IN4 |
| 33, 32 | Car Motor ENA, ENB |
| 18, 19 | Drill Motor IN1, IN2 |
| 23 | Drill Motor ENA |
| 13 | Servo Signal |
| 4 | Buzzer |

---

## 🔌 Wiring Diagram

![Wiring Diagram](wiring_diagram.svg)

---

## 📱 Gamepad Controls (Dabble App)

| Button | Action |
|---|---|
| ↑ Up | Move Forward |
| ↓ Down | Move Backward |
| ← Left | Turn Left |
| → Right | Turn Right |
| ✕ Cross | Servo Clockwise (lower drill) |
| □ Square | Servo Counter-CW (raise drill) |
| ○ Circle | Activate Drill Motor |

---

## 🔧 Libraries Required

Install these in Arduino IDE (Sketch → Include Library → Manage Libraries):

- `DabbleESP32` by STEMpedia
- `ESP32Servo` by Kevin Harrington

---

## 💡 Lessons Learned

- **Torque limitations** — small drill motor struggles with hard materials
- **Stability** — chassis needs weight distribution improvement
- **Power distribution** — separate regulators prevent voltage drops during peak load

---

## 🔜 Next Steps

- [ ] Stronger drill motor with gearbox
- [ ] PID-based stabilization
- [ ] Obstacle avoidance sensor
- [ ] OTA firmware updates

---

## 📄 License

MIT License — free to use and modify.
