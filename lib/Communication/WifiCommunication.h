#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

class WifiCommunication
{
private:
  WebServer *server;

public:
  String LastData = "";
  WifiCommunication(char *ssid, char *password);
  ~WifiCommunication();
  void RefreshData();
};

WifiCommunication::WifiCommunication(char *ssid, char *password)
{

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32"))
  {
    Serial.println("MDNS responder started");
  }

  server = new WebServer(80);

  server->on("/", [this]() {
    server->send(200, "text/plain", LastData);
  });

  server->on("/{}", [this]() {
    String data = server->pathArg(0);
    LastData = String(data);
    server->send(200, "text/plain", "data recieved");
  });

  server->begin();
}

WifiCommunication::~WifiCommunication()
{
}

void WifiCommunication::RefreshData()
{
  server->handleClient();
}
