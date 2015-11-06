////
//
// General code from http://www.pushingbox.com for Arduino + Ethernet Shield (official) v1.2
//
////

#include <SPI.h>
#include <Ethernet.h>

  /////////////////
 // MODIFY HERE //
/////////////////

// Be sure this address is unique in your network
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x19 };
// DeviceID: https://www.pushingbox.com/scenarios.php
char DEVID1[] = "TODO";
// The analog reading from the sensor when the LED is on
int threshold = 400;
// How long (ms) is the bell indicating (prevents multiple notification on one ring)
int bell_duration = 4000;
// The cell and 10K pulldown are connected to a0
int photocellPin = 0;

// Debug mode
boolean DEBUG = true;

  //////////////
 //   End    //
//////////////

char serverName[] = "api.pushingbox.com";
// State of the connection last time through the main loop
boolean lastConnected = false;
boolean photocellPinState = false;                // Save the last state of the Pin for DEVID1
int photocellReading;     // the analog reading from the sensor divider

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  Serial.begin(9600);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  else{
    Serial.println("Ethernet ready");
    // print the Ethernet board/shield's IP address:
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop()
{
      // Maintain DHCP lease
      Ethernet.maintain();

      ////
      // Listening for the photocellPin state
      ////
      photocellReading = analogRead(photocellPin);
      if(DEBUG){Serial.print("photocellReading is ");}
      if(DEBUG){Serial.println(photocellReading);}

      if (photocellReading > threshold && photocellPinState == false) // switch on pinDevid1 is ON
      {
        if(DEBUG){Serial.println("photocellPin is HIGH");}
        photocellPinState = true;
        //Sending request to PushingBox when the pin is HIGH
        sendToPushingBox(DEVID1);

        delay(bell_duration);
      }
       if (photocellReading < threshold && photocellPinState == true) // switch on pinDevid1 is OFF
      {
        if(DEBUG){Serial.println("photocellPin is LOW");}
        photocellPinState = false;
        //Sending request to PushingBox when the pin is LOW
        //sendToPushingBox(DEVID1);    //Here you can run an other scenario by creating a DEVID2 variable
      }


      //DEBUG part
      // this write the respons from PushingBox Server.
      // You should see a "200 OK"
      if (client.available()) {
        char c = client.read();
        if(DEBUG){Serial.print(c);}
      }

      // if there's no net connection, but there was one last time
      // through the loop, then stop the client:
      if (!client.connected() && lastConnected) {
        if(DEBUG){Serial.println();}
        if(DEBUG){Serial.println("disconnecting.");}
        client.stop();
      }
      lastConnected = client.connected();
}

//Function for sending the request to PushingBox
void sendToPushingBox(char devid[]){
  client.stop();
  if(DEBUG){Serial.println("connecting...");}

  if (client.connect(serverName, 80)) {
    if(DEBUG){Serial.println("connected");}

    if(DEBUG){Serial.println("sendind request");}
    client.print("GET /pushingbox?devid=");
    client.print(devid);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino");
    client.println();
  }
  else {
    if(DEBUG){Serial.println("connection failed");}
  }
}
