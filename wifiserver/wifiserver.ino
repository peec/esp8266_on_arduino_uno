

#include <SoftwareSerial.h>
#define DEBUG true
#define dbg Serial  // USB local debug
String loopCmd;

// DIGITAL PORT 11 and 12 on the UNO..
SoftwareSerial esp(11, 12); // RX,TX


String ssid = "PEISENETT_GJEST";
String pass = "dirtymovie";



void webserver(char connectionId, String queryString) {

  if (queryString=="/turnonlights") {
     // Do something 
  }

  http(connectionId, "OK");

  String msg = "AT+CIPCLOSE=";
  msg += connectionId;
  sendAndWait(msg, "", 500);
}





void setup() {
  pinMode(13, OUTPUT); // For debugging purposes w/o USB
  // Set baud rates
  digitalWrite(13, HIGH);
  esp.begin(9600);
  dbg.begin(9600);
  dbg.println("DEBUG: Running Setup");


  sendData("AT+RST\r\n", 1000, DEBUG);
  sendData("AT\r\n", 1000, DEBUG);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  sendData("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"\r\n", 4000, DEBUG);
  sendData("AT+CIPMUX=1\r\n", 2000, DEBUG);
  sendData("AT+CIFSR\r\n", 1000, DEBUG);

  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);

  dbg.println("DEBUG: Setup complete\n\n");
}


void loop() {
  while (esp.available())
  {
    char c = esp.read();
    if (c == '\n')
    {
      if (loopCmd.indexOf("+IPD") != -1) {
        dbg.println(loopCmd);
        char connectionId = loopCmd.charAt(5);

        String queryString = loopCmd.substring(loopCmd.indexOf("GET ") + 4, loopCmd.indexOf("HTTP"));

        webserver(connectionId, queryString);
      }
      loopCmd = "";
    }
    else if (c != '\r')loopCmd += c;
  }
}



void http(char connectionId, String output)
{
  String msg = "AT+CIPSEND=";
  msg += connectionId;
  msg += ",";
  msg += output.length();
  esp.println(msg);
  if (esp.find(">"))
  {
    sendAndWait(output, "SEND OK", 10);
  }
}


boolean sendAndWait(String AT_Command, char *AT_Response, int wait) {
  dbg.print(AT_Command);
  esp.println(AT_Command);
  delay(wait);
  while ( esp.available() > 0 ) {
    if ( esp.find(AT_Response)  ) {
      dbg.print(" --> ");
      dbg.println(AT_Response);
      return 1;
    }
  }
  dbg.println(" fail!");
  return 0;
}


String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  esp.print(command);
  long int time = millis();
  while ( (time + timeout) > millis()) {
    while (esp.available()) {
      char c = esp.read();
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}

