//______________Setup WIFI Twilio __________________
#include "twilio.hpp"

static const char *ssid = ""; //Replace with network SSID
static const char *password = ""; //Replace with network password

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "";//Replace with Twilio Account SID
static const char *auth_token = "";//Replace with Twilio Authentication token
// Phone number should start with "+<countrycode>"
static const char *from_number = ""; //Replace with number being sent from

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = ""; //Replace with number being sent to
static const char *message=""; //message to change

int clickcount = 0;
int resetcount = 0;
int delaytimer = 0;

Twilio *twilio;


//_______________Setup Stepper code _______________
void setup() {
  // ___________ Connect to WIFI and send message ______________
  pinMode(16, INPUT_PULLUP);

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   // Serial.println("Connecting...");
    delay(500);
  }

}

void loop() {
 if(Serial.available()) {
    char data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcvd

    if(data_rcvd == '1'){
      twilio = new Twilio(account_sid, auth_token);
      delay(1000);
      delaytimer += 1000;
      message = "Congratulations on reaching your step count!
https://api.echo3d.co/webar?key=patient-resonance-8324&entry=aeba02e2-0207-447d-b965-956766c95927 \n
    https://api.echo3d.co/webar?key=patient-resonance-8324&entry=c5dfc84e-6add-40ce-aa4e-75695e61f7f3";
      bool success = twilio->send_message(to_number, from_number, message, response);

    }
  }

  
  //____________Check force to run stepper motor__________
  

      //Send Twilio Message
    
   }


  
