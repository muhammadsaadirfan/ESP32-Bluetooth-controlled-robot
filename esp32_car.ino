#include "BluetoothSerial.h"
BluetoothSerial ESP_BT;

// Define GPIO pins for the L298N motor drivers
#define MOTOR_right_PIN1 13
#define MOTOR_right_PIN2 12
#define MOTOR_left_PIN1 14
#define MOTOR_left_PIN2 27

void setupMotors() {
  pinMode(MOTOR_right_PIN1, OUTPUT);
  pinMode(MOTOR_right_PIN2, OUTPUT);
  pinMode(MOTOR_left_PIN1, OUTPUT);
  pinMode(MOTOR_left_PIN2, OUTPUT);
}

// Function to stop the car
void stopCar() {
  digitalWrite(MOTOR_right_PIN1, LOW);
  digitalWrite(MOTOR_right_PIN2, LOW);
  digitalWrite(MOTOR_left_PIN1, LOW);
  digitalWrite(MOTOR_left_PIN2, LOW);
}

// Function to move the car forward
void moveForward() {
  digitalWrite(MOTOR_right_PIN1, HIGH);
  digitalWrite(MOTOR_right_PIN2, LOW);
  digitalWrite(MOTOR_left_PIN1, HIGH);
  digitalWrite(MOTOR_left_PIN2, LOW);
}

// Function to move the car backward
void moveBackward() {
  digitalWrite(MOTOR_right_PIN1, LOW);
  digitalWrite(MOTOR_right_PIN2, HIGH);
  digitalWrite(MOTOR_left_PIN1, LOW);
  digitalWrite(MOTOR_left_PIN2, HIGH);
}

// Function to turn the car left
void turnLeft() {
  digitalWrite(MOTOR_right_PIN1, HIGH);
  digitalWrite(MOTOR_right_PIN2, LOW);
  digitalWrite(MOTOR_left_PIN1, LOW);
  digitalWrite(MOTOR_left_PIN2, HIGH);
}

// Function to turn the car right
void turnRight() {
  digitalWrite(MOTOR_right_PIN1, LOW);
  digitalWrite(MOTOR_right_PIN2, HIGH);
  digitalWrite(MOTOR_left_PIN1, HIGH);
  digitalWrite(MOTOR_left_PIN2, LOW);
}

void setup() {
  Serial.begin(115200);
  ESP_BT.begin("Thunderbolt");  // Start Bluetooth with the name "Thunderbolt"
  Serial.println("Bluetooth Device is Ready to Pair");
  // Initialize the motor pins
  setupMotors();
  stopCar();
}

void loop() {
  if (ESP_BT.available()) {
    char incoming = ESP_BT.read();
    Serial.print("Received: ");
    Serial.println(incoming);
    
    // Control the car based on the received Bluetooth data
    switch (incoming) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopCar();
        break;
      default:
        break;
    }
  }
  delay(20);  // Delay for stability
}