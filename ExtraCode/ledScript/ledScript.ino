#define red 4
#define green 2

void setup() {
  // put your setup code here, to run once:
  pinMode(red, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = digitalRead(red);
  Serial.println(x);
}
