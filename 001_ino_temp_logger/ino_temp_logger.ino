#include <DHT11.h>
int pin=2;
DHT11 dht11(pin);

// Time interval in seconds
long interval = 60;
// CSV delimiter
String delimiter = "\t";


// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("temperature");
  Serial.print(delimiter);
  Serial.print("humidity");
  Serial.print(delimiter);
  Serial.print("dew_point");
  Serial.println();
}

void loop()
{
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0)
  {
    Serial.print(temp);
    Serial.print(delimiter);
    Serial.print(humi);
    Serial.print(delimiter);
    Serial.print(dewPointFast(temp, humi));
    Serial.println();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();
  }
  delay(interval*1000); //delay for reread
}

