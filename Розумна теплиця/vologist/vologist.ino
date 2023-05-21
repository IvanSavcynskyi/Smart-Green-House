#define moisture_sensor A0 
#define moisture_sensor_power 16

int very_moist_value = 280;

void setup() {
pinMode (moisture_sensor_power, OUTPUT);
Serial.begin(115200);
}

void loop() {
digitalWrite (moisture_sensor_power, HIGH);
delay(10);
int moisture_value = analogRead (moisture_sensor);
digitalWrite(moisture_sensor_power, LOW);
int moisture_value_percent= map (moisture_value, very_moist_value, 1023, 100, 0);
Serial.print(String (moisture_value) + "=");
Serial.println(String (moisture_value_percent) + "%");
delay (30000);
}
