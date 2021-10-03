#include <ESP8266WiFi.h>

int role_pin = 2;

WiFiServer server(80);

const char *ssid = "Wifi Name";
const char *password = "Wifi Password";

int count = 0;
void setup()
{
  Serial.begin(115200);
  pinMode(role_pin, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  Serial.println("Wifi'ye Baglandi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Baglandi");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void ledYak() {
  digitalWrite(role_pin, HIGH);
}

void ledSon() {
  digitalWrite(role_pin, LOW);
}

void loop()
{
  WiFiClient client = server.available();

  if (client) {
    if (client.connected())
    {
      Serial.println("Kullanıcı Baglandi");
    }

    while (client.connected()) {
      while (client.available() > 0) {

        //Serial.println(client.read());

        char verim = client.read();


        //Serial.println(verim);

        if (verim == '1') {
          ledYak();
          Serial.println(verim);
        }
       
        else if (verim == '0') {
          ledSon();
          Serial.println(verim);
        }
      }
    }

    client.stop();
    Serial.println("Kullanıcı Deaktif");
  }
}
