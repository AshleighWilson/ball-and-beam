#include <SimpleFOC.h>

// Configuration
#define MOTOR_POLE_PAIRS 11
#define PWM_PIN_A 9
#define PWM_PIN_B 5
#define PWM_PIN_C 6
#define ENABLE_PIN 8

// Create a BLDC motor and driver objects.
BLDCMotor motor = BLDCMotor(MOTOR_POLE_PAIRS);
BLDCDriver3PWM driver = BLDCDriver3PWM(PWM_PIN_A, PWM_PIN_B, PWM_PIN_C, ENABLE_PIN);

// Create the user command interface.
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&motor.target, cmd); }

void setup() {
  // Driver configuration.
  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);

  // Motor configuration.
  motor.phase_resistance = 5.8; // [Ohm]
  motor.current_limit = 2; // [Amps] - if phase resistance defined.
  motor.voltage_limit = 2 * motor.phase_resistance; // [V] - if phase resistance is not defined.
  motor.velocity_limit = 5; // [rad/s] ~50rpm.
  motor.controller = MotionControlType::velocity_openloop;
  motor.init();

  // Add a command to set the desired velocity.
  command.add('T', doTarget, "target velocity");

  // Start the serial comms.
  Serial.begin(115200);
  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  _delay(1000);
}

void loop() {
  // Move motor and process user command.
  motor.move();
  command.run();
}
