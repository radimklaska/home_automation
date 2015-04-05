#include <DHT11.h>
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// Temp sensor
int pin=2;
DHT11 dht11(pin);

// time interval in seconds
long interval = 30;
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

  // initialize the digital pin as an output for LED.
  pinMode(led, OUTPUT);

  // CSV output header
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
  int leddelay;
  int ledrepeats;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0)
  {
    Serial.print(temp);
    Serial.print(delimiter);
    Serial.print(humi);
    Serial.print(delimiter);
    Serial.print(dewPointFast(temp, humi));
    Serial.println();

    // 40=GOOD 65=BAD
    // 55 and more = open window!
    leddelay = map(humi, 30, 65, 500, 50);
    ledrepeats = map(humi, 50, 65, 1, 10);
//    Serial.print("leddelay: ");
//    Serial.println(leddelay);
//    Serial.print("ledrepeats: ");
//    Serial.println(ledrepeats);

    for (int i=1; i <= ledrepeats; i++){
      digitalWrite(led, HIGH);
      delay(20);
      digitalWrite(led, LOW);
      delay(leddelay);
    }

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


