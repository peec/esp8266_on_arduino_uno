

#include <SoftwareSerial.h>
#define DEBUG true
#define dbg Serial  // USB local debug

const int PUSH_BUTTON = 2;

// DIGITAL PORT 11 and 12 on the UNO..
SoftwareSerial esp(11, 12); // RX,TX


String ssid = "PEISENETT_GJEST";

String pass = "dirtymovie";

String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  esp.print(command); // send the read character to the esp8266
  long int time = millis();
  while ( (time + timeout) > millis()) {
    while (esp.available()) {
      // The esp has data so display its output to the serial window
      char c = esp.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}





void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT); // For debugging purposes w/o USB
  // Set baud rates
  digitalWrite(13, HIGH);
  esp.begin(9600);
  dbg.begin(9600);
  dbg.println("DEBUG: Running Setup");



  sendData("AT+RST\r\n", 2000, DEBUG); // reset module
  sendData("AT\r\n", 2000, DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // configure as access point
  sendData("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"\r\n", 6000, DEBUG); // configure as access point
  sendData("AT+CIPMUX=0\r\n", 2000, DEBUG); // reset module
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // get ip address

  dbg.println("DEBUG: Setup complete\n\n");
}


void loop() {
  if (digitalRead(2) == 1) {
    sendData("AT+CIPSTART=\"TCP\",\"148.123.25.55\",80\r\n", 1000, DEBUG); // get ip address
  
    String httpRequest = "GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\nHost: cse.dmu.ac.uk\r\nAccept: */*\r\n\r\n";        //test file on my web
  
    String cmd = "AT+CIPSEND=";
    cmd += httpRequest.length();
    cmd += "\r\n";
    sendData(cmd, 1000, DEBUG);
    sendData(httpRequest + "\r\n", 1000, DEBUG);
    sendData("AT+CIPCLOSE\r\n", 1000, DEBUG);
  }
  
  
  // END - Borrowed Code
}

