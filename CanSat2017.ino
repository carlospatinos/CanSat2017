#define SERIESRESISTOR 10000    
#define THERMISTOR_PIN A0 
#define PIEZORESISTOR_PIN A1
void setup() {
  Serial.begin(9600);
}

void loop(){
  float voltage = getThemperature();
  float pressure = getPressure();
  printData(pressure, voltage);
  delay(2000);
}

/*
* 1.79 -> 3 C outside. 8 inside
* 1.69 -> 8 C ourside. 12 inside
* 1.10 -> 20
*/

float _in[] = {1.90, 1.88, 1.85, 1.79, 1.69, 1.50, 1.40, 1.36};
float _out[] = {3.0, 5.0, 8.0, 10.0, 12.00, 15.0, 30.0, 40.0};
int size = 8;

float getThemperature() {
  int sensorValue = analogRead(THERMISTOR_PIN);
  float voltage = sensorValue * (5.0/1023.0);
  
  if (voltage >= _in[0]) return _out[0];
  if (voltage <= _in[size-1]) return _out[size-1];
  
  uint8_t pos = 1;  // _in[0] allready tested
  while(voltage < _in[pos]) pos++;
  
  float temp = ((_out[pos] + _out[pos-1])/2.0);
  
  return temp;
}

/* Reads pressure from the given pin.
 * Returns a value in hPa or millibars
 http://www.met.ie/latest/reports.asp
 */
float getPressure() {
  int sensorValue = analogRead(PIEZORESISTOR_PIN);
  float pressure = ((sensorValue/1024.0) + 0.095) / 0.0009;
  return pressure;
}

void printData(float p, float t){
  Serial.print("T=");
  Serial.print(t);
  Serial.print(";");
  Serial.print("P=");
  Serial.print(p);
  Serial.println(";");
}
