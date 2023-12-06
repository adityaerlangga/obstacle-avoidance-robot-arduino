
const int trigLeft = 4;
const int echoLeft = 5;
long durationLeft;
int distanceLeft;

const int trigFront = A4;
const int echoFront = A5;
long durationFront;
int distanceFront;

const int trigRight = 3;
const int echoRight = 2;
long durationRight;
int distanceRight;

// Define motor control pins
#define in1 7
#define in2 8
#define ena 9

#define in3 11
#define in4 12
#define enb 10

void setup()
{
  Serial.begin(9600);

  pinMode(trigLeft, OUTPUT);  
  pinMode(echoLeft, INPUT);
  pinMode(trigFront, OUTPUT);  
  pinMode(echoFront, INPUT);
  pinMode(trigRight, OUTPUT);  
  pinMode(echoRight, INPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);


  // ============================ START RULES ============================

  // SensorLeft	SensorFront	SensorRight	Output
  // Far	Far	Far	Maju
  // Far	Far	Near	Maju
  // Far	Near	Far	Belok Kiri
  // Far	Near	Near	Belok Kiri
  // Near	Far	Far	Belok Kanan
  // Near	Far	Near	Belok Kanan
  // Near	Near	Far	Mundur
  // Near	Near	Near	Mundur

  // ============================ END RULES ==============================
}

void loop()
{
  // SENSOR HC KIRI
  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeft, LOW);
  durationLeft = pulseIn(echoLeft, HIGH);
  distanceLeft = durationLeft * 0.034 / 2;

  // SENSOR HC DEPAN
  digitalWrite(trigFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFront, LOW);
  durationFront = pulseIn(echoFront, HIGH);
  distanceFront = durationFront * 0.034 / 2;

  // SENSOR HC KANAN
  digitalWrite(trigRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRight, LOW);
  durationRight = pulseIn(echoRight, HIGH);
  distanceRight = durationRight * 0.034 / 2;

  Serial.print("Sensor Kiri :");
  Serial.print(distanceLeft);
  Serial.println(" cm");

  Serial.print("Sensor Depan :");
  Serial.print(distanceFront);
  Serial.println(" cm");

  Serial.print("Sensor Kanan :");
  Serial.print(distanceRight);
  Serial.println(" cm");

  if(distanceLeft > 25 && distanceFront > 25 && distanceRight > 25) { // RULE 1
    Serial.println("Motor Maju");
    moveForward();
  } else if(distanceLeft > 25 && distanceFront > 25 && distanceRight <= 25) { // RULE 2    
    Serial.println("Mundur");
    moveBackward();
    delay(300);
    Serial.println("Belok Kiri");
    turnLeft();
    delay(1000);
  } else if(distanceLeft > 25 && distanceFront <= 25 && distanceRight > 25) { // RULE 3
    Serial.println("Mundur");
    moveBackward();
    delay(300);
    Serial.println("Belok Kanan");
    turnRight();
    delay(1000);
  } else if(distanceLeft > 25 && distanceFront <= 25 && distanceRight <= 25) { // RULE 4
    Serial.println("Belok Kiri");
    turnLeft();
  } else if(distanceLeft <= 25 && distanceFront > 25 && distanceRight > 25) { // RULE 5
    Serial.println("Mundur");
    moveBackward();
    delay(300);
    Serial.println("Belok Kanan");
    turnRight();
    delay(1000);
  } else if(distanceLeft <= 25 && distanceFront > 25 && distanceRight <= 25) { // RULE 6
    Serial.println("Belok Kanan");
    turnRight();
  } else if(distanceLeft <= 25 && distanceFront <= 25 && distanceRight > 25) { // RULE 7
    Serial.println("Belok Kanan");
    turnRight();
  } else if(distanceLeft <= 25 && distanceFront <= 25 && distanceRight <= 25) { // RULE 8
    Serial.println("Mundur");
    moveBackward();
    delay(300);
    turnRight();
    delay(1000);
  }


  // Add a delay to control the loop rate
  delay(10); // Adjust the delay based on your requirements
}

void moveForward() {
  // Set motor A to move forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 90);

  // Set motor B to move forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 90);
}

void moveBackward() {
  // Set motor A to move backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 90);

  // Set motor B to move backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 90);
}

void turnLeft() {
  // Set motor A to move backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 0);

  // Set motor B to move forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 90);
}

void turnRight() {
  // Set motor A to move forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 90);

  // Set motor B to move backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 0);
}