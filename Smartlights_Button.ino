#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>
#include <ezButton.h>

#define _SSID ""      // Your WiFi SSID
#define _PASSWORD ""  // Your WiFi Password
#define KEY ""        // Webhooks Key
#define EVENT1 ""     // Webhooks Event Name 1
#define EVENT2 ""     // Webhooks Event Name 2  

Webhook webhook_ON(KEY, EVENT1);    // Create an object.
Webhook webhook_OFF(KEY, EVENT2);

const uint8_t BUTTON_PIN = D2;
ezButton button(BUTTON_PIN);
bool prev_press_state = 0;
bool curr_press_state = 0;

void setup() {

  button.setDebounceTime(50);

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

//================================================================//
//================================================================//

  // Trigger with 3 values.
  //webhook_ON.trigger("value1","value2","value3");
  //delay(5000);

  // Trigger with 3 values.
  //webhook_OFF.trigger("ABC","XYZ","ABC");
  //delay(5000);
}

void loop() {
  
  button.loop();
  
  if(button.isPressed()) {
    Serial.println("The button is pressed");
    curr_press_state = !curr_press_state; // Update that the button was pressed
    prev_press_state = curr_press_state;
  
    if(curr_press_state == 1){
           //Trigger the ON Webhook
           Serial.println("On Button");
           webhook_ON.trigger("value1","value2","value3");
      }
    else{
         //Trigger the OFF Webhook
           Serial.println("Off Button");
           webhook_OFF.trigger("ABC","XYZ","ABC");
      }
    }

  
}