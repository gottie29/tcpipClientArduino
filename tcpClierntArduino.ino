#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFiClient client;

const char* ssid = "your ssid";
const char* password = "yout password";
const char* host = "server ip";
uint16_t port = 4681; // server port

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

}

void loop()
{
    WiFiClient client;

    if (!client.connect(host, port)) {

        Serial.println("Connection to host failed");

        delay(1000);
        return;
    }

    Serial.println("Connected to server successful!");
    

    // Integrate here what you want to send to the server
    // e.g. OpenSpaceProject
    StaticJsonDocument<200> doc;
    doc["topic"] = 1;
    doc["type"] = "luascript";
    JsonObject payload = doc.createNestedObject("payload");
    //payload["script"] = "openspace.printInfo(\"Hello World\")";
    payload["script"] = "openspace.navigation.addGlobalRoll(50)";
    //serializeJson(doc, Serial);
    serializeJson(doc, client);
    // Ende of sending


    Serial.println("Disconnecting...");
    client.stop();

    delay(10000);
}