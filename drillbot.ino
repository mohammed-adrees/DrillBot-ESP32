#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>

// --- Car Motor Driver ---
#define IN1  14
#define IN2  27
#define IN3  26
#define IN4  25
#define ENA  33
#define ENB  32

// --- Drill Motor Driver ---
#define DRILL_IN1  18
#define DRILL_IN2  19
#define DRILL_ENA  23

// --- Servo ---
#define SERVO_PIN  13

// --- Buzzer ---
#define BUZZER_PIN  4

// --- PWM ---
#define PWM_FREQ       1000
#define PWM_RESOLUTION 8
#define CH_ENA   0
#define CH_ENB   1
#define CH_DRILL 2

// --- Speeds ---
#define CAR_SPEED    200
#define TURN_SPEED   160
#define DRILL_SPEED  220

// --- Continuous Servo values ---
#define SERVO_STOP        90
#define SERVO_CLOCKWISE   0
#define SERVO_COUNTER     180

Servo drillServo;

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  ledcSetup(CH_ENA, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENA, CH_ENA);
  ledcSetup(CH_ENB, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENB, CH_ENB);

  pinMode(DRILL_IN1, OUTPUT);
  pinMode(DRILL_IN2, OUTPUT);
  ledcSetup(CH_DRILL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(DRILL_ENA, CH_DRILL);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  drillServo.attach(SERVO_PIN);
  drillServo.write(SERVO_STOP);

  Dabble.begin("DrillBot");
  stopCar();
  stopDrillMotor();

  Serial.println("Ready!");
}

void loop() {
  Dabble.processInput();

  // --- Servo: hold to spin, release to stop ---
  if (GamePad.isCrossPressed()) {
    drillServo.write(SERVO_CLOCKWISE);
    Serial.println("Servo CW");
  }
  else if (GamePad.isSquarePressed()) {
    drillServo.write(SERVO_COUNTER);
    Serial.println("Servo CCW");
  }
  else {
    drillServo.write(SERVO_STOP);
  }

  // --- Drill motor: hold O = ON with pip pip pip, release = OFF ---
  if (GamePad.isCirclePressed()) {
    digitalWrite(DRILL_IN1, HIGH);
    digitalWrite(DRILL_IN2, LOW);
    ledcWrite(CH_DRILL, DRILL_SPEED);

    // pip pip pip
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);

  } else {
    stopDrillMotor();
    digitalWrite(BUZZER_PIN, LOW);
  }

  // --- Car movement ---
  if (GamePad.isUpPressed())         moveForward();
  else if (GamePad.isDownPressed())  moveBackward();
  else if (GamePad.isLeftPressed())  turnLeft();
  else if (GamePad.isRightPressed()) turnRight();
  else                               stopCar();
}

// --- Car functions ---
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  ledcWrite(CH_ENA, CAR_SPEED);
  ledcWrite(CH_ENB, CAR_SPEED);
}
void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  ledcWrite(CH_ENA, CAR_SPEED);
  ledcWrite(CH_ENB, CAR_SPEED);
}
void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  ledcWrite(CH_ENA, TURN_SPEED);
  ledcWrite(CH_ENB, TURN_SPEED);
}
void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  ledcWrite(CH_ENA, TURN_SPEED);
  ledcWrite(CH_ENB, TURN_SPEED);
}
void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  ledcWrite(CH_ENA, 0);
  ledcWrite(CH_ENB, 0);
}

// --- Drill stop ---
void stopDrillMotor() {
  digitalWrite(DRILL_IN1, LOW);
  digitalWrite(DRILL_IN2, LOW);
  ledcWrite(CH_DRILL, 0);
}
