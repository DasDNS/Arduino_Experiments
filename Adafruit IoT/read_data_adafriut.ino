#include "AdafruitIO_WiFi.h"
#define IO_USERNAME "**********"
#define IO_KEY "*******************************"
#define WIFI_SSID "DNS"
#define WIFI_PASS "12345678"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#define FEED_OWNER "dns_das"
AdafruitIO_Feed *sharedFeed = io.feed("var", FEED_OWNER);

int val=0;
#define LED_PIN1 13

void setup() {
   Serial.begin(115200);
  io.connect();
  sharedFeed->onMessage(handleMessage);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  pinMode(LED_PIN1,OUTPUT);
   pinMode(LED_PIN1,OUTPUT);
    
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  sharedFeed->get();

}

void loop() {

   io.run();
void handleMessage(AdafruitIO_Data *data);

}

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <-  ");
  val=data->toInt();//read data
  Serial.println(val);
  
}
