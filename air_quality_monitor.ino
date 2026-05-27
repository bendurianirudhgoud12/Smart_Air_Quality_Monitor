
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <ESP_Mail_Client.h>
WiFiClient client;
#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"
unsigned long channelID = YOUR CHANNEL ID;
const char* writeAPIKey = "YOUR WRITE APIKEY";


#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "SENDER'S GMAIL"
#define AUTHOR_PASSWORD "YOUR GMAIL APP PASSWORD"

#define RECIPIENT_EMAIL "RECEIVER'S MAIL"



WiFiClient tsclient;
SMTPSession smtp;
unsigned long lastEmailTime = 0;
const unsigned long emailInterval = 60000;

void setup() {

  Serial.begin(115200);

  randomSeed(analogRead(0));
  Serial.println();
  Serial.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(tsclient);

}
void loop() {


  int co2 = random(250, 3000);
  if (random(0, 10) > 7) {

    co2 += random(200, 1000);

  }

  int aqiCode;

  Serial.println();
  Serial.print("CO2 Level: ");
  Serial.print(co2);
  Serial.println(" ppm");

  if (co2 < 1000) {
    Serial.println("AQI Status: Good Ventilation");
    aqiCode = 1;
  }
  else if (co2 <= 2000) {
    Serial.println("AQI Status: Open windows / Increase ventilation");
    aqiCode = 2;
  }
  else {
    Serial.println("AQI Status: Poor Air Quality");
    Serial.println("ALERT: Ventilate Immediately!");
    aqiCode = 3;
  }
  ThingSpeak.setField(1, co2);
  ThingSpeak.setField(2, aqiCode);
 int response = ThingSpeak.writeFields(channelID, writeAPIKey);
 if (response == 200) {
    Serial.println("ThingSpeak Update Successful");
  }
  else {
    Serial.print("ThingSpeak Error: ");
    Serial.println(response);
  }
  if (co2 > 2000) {
    if (millis() - lastEmailTime > emailInterval) {
      sendEmail(co2);
      lastEmailTime = millis();
    }
  }
  Serial.println("--------------------------------");
  delay(15000);
}

void sendEmail(int co2Value) {

  smtp.callback(NULL);

  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;

  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  session.login.user_domain = "";

  SMTP_Message message;

  message.sender.name = "ESP8266 AQI Monitor";
  message.sender.email = AUTHOR_EMAIL;

  message.subject = "Air Quality Alert";

  message.addRecipient("User", RECIPIENT_EMAIL);

  String emailMessage = "WARNING!\n\n";
  emailMessage += "Poor Air Quality Detected.\n";
  emailMessage += "Current CO2 Level: ";
  emailMessage += String(co2Value);
  emailMessage += " ppm\n\n";
  emailMessage += "Please ventilate immediately.";

  message.text.content = emailMessage.c_str();
  session.time.ntp_server = "pool.ntp.org,time.nist.gov";
  Serial.println("Sending Email Alert...");
  if (!smtp.connect(&session)) {
    Serial.println("SMTP Connection Failed");
    return;
  }
  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Email Failed");
    Serial.println(smtp.errorReason());
  }
  else {
    Serial.println("Email Sent Successfully");
  }
  smtp.closeSession();
}