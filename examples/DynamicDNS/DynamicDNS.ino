#include <NexusOS.h>
                                           // 9 bytes
#include <HardwareSerial.h>                // 88 bytes
#include <SPI.h>                           // 89 bytes
#include <Client.h>                        // 107 bytes
#include <EthernetClient.h>                // 151 bytes
#include <Ethernet.h>                      // 151 bytes


byte mac[] = {                             // 6 bytes
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 0, 177);            // 6 bytes

EthernetClient client;


void setup()
{
    Serial.begin(9600);

    Ethernet.begin(mac, ip);               // 22 bytes  DHCP 244 bytes
    Serial.println(Ethernet.localIP());

    delay(1000);

    //const char server[] = "dynupdate.no-ip.com"; 
    const char server[] = "mike-austin.com"; 

    if (client.connect(server, 80))
    {
        //client << F("GET /nic/update?hostname=nexusos.ddns.net HTTP/1.0") << endl;
        client << F("GET /index.html HTTP/1.0") << endl;
        //client << F("Host: dynupdate.no-ip.com") << endl;
        client << F("Host: mike-austin.com") << endl;
        //client << F("Authorization: Basic bWlrZV9la2ltMTAyNDoxMjhkWHhYeCFAIyQ=") << endl;
        client << F("User Agent: NexusOS Update Client/v1.0 mike_ekim@yahoo.com") << endl;
        client << endl;
    }
}

void loop()
{
    if (client.available())
    {
        Serial << (char) client.read();
    }
}