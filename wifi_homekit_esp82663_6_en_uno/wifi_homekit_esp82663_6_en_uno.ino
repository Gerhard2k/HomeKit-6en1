#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>


IPAddress server(192, 168, 0, 56); // IP de la raspberry Pi
const char* ssid     = "SSID"; // Your ssid
const char* pass = "PASSWORD"; // Your Password
const char* host = "esp6en1"; // nombre del entorno

int salida1 = 0;
int salida2 = 2;
int salida3 = 12;
int salida4 = 13;
int salida5 = 14;
int salida6 = 16;

boolean estado_salida1 = 0;
boolean estado_salida2 = 0;
boolean estado_salida3 = 0;
boolean estado_salida4 = 0;
boolean estado_salida5 = 0;
boolean estado_salida6 = 0;

#define BUFFER_SIZE 100



WiFiClient wclient;
PubSubClient client(wclient, server);

void callback(const MQTT::Publish& pub) {
  Serial.println (pub.payload_string());
    if(pub.payload_string() == "on1")
    {
      digitalWrite(salida1, HIGH); 
      estado_salida1=1;
      Serial.println("Salida 1 On");        
    }
    if(pub.payload_string() == "off1")
    {
      digitalWrite(salida1, LOW);
      estado_salida1=0;
      Serial.println("Salida 1 Off");
    }

    if(pub.payload_string() == "on2")
    {
      digitalWrite(salida2, HIGH); 
      estado_salida2=1;
      Serial.println("Salida 2 On");        
    }
    if(pub.payload_string() == "off2")
    {
      digitalWrite(salida2, LOW);
      estado_salida2=0;
      Serial.println("Salida 2 Off");
    }

    if(pub.payload_string() == "on3")
    {
      digitalWrite(salida3, HIGH); 
      estado_salida3=1;
      Serial.println("Salida 3 On");        
    }
    if(pub.payload_string() == "off3")
    {
      digitalWrite(salida3, LOW);
      estado_salida3=0;
      Serial.println("Salida 3 Off");
    }

    if(pub.payload_string() == "on4")
    {
      digitalWrite(salida4, HIGH); 
      estado_salida4=1;
      Serial.println("Salida 4 On");        
    }
    if(pub.payload_string() == "off4")
    {
      digitalWrite(salida4, LOW);
      estado_salida4=0;
      Serial.println("Salida 4 Off");
    }

    if(pub.payload_string() == "on5")
    {
      digitalWrite(salida5, HIGH); 
      estado_salida5=1;
      Serial.println("Salida 5 On");        
    }
    if(pub.payload_string() == "off5")
    {
      digitalWrite(salida5, LOW);
      estado_salida5=0;
      Serial.println("Salida 5 Off");
    }

    if(pub.payload_string() == "on6")
    {
      digitalWrite(salida6, HIGH); 
      estado_salida6=1;
      Serial.println("Salida 6 On");        
    }
    if(pub.payload_string() == "off6")
    {
      digitalWrite(salida6, LOW);
      estado_salida6=0;
      Serial.println("Salida 6 Off");
    }    
    
    if (estado_salida1 != EEPROM.read(0)) EEPROM.write(0,estado_salida1);
    if (estado_salida2 != EEPROM.read(1)) EEPROM.write(1,estado_salida2);
    if (estado_salida3 != EEPROM.read(2)) EEPROM.write(2,estado_salida3);
    if (estado_salida4 != EEPROM.read(3)) EEPROM.write(3,estado_salida4);
    if (estado_salida5 != EEPROM.read(4)) EEPROM.write(4,estado_salida5);
    if (estado_salida6 != EEPROM.read(5)) EEPROM.write(5,estado_salida6);                        
                  
    EEPROM.commit();
}


void setup() 
{
  pinMode(salida1,OUTPUT);
  pinMode(salida2,OUTPUT);
  pinMode(salida3,OUTPUT);
  pinMode(salida4,OUTPUT);
  pinMode(salida5,OUTPUT);
  pinMode(salida6,OUTPUT);
  
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  Serial.println();
  Serial.println();
  client.set_callback(callback);
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
    Serial.println("WiFi not connected");
    }
    else
    {
    Serial.println("WiFi connected");                         
    }
  }

  digitalWrite(salida1, EEPROM.read(0));
  estado_salida1=EEPROM.read(0);
  Serial.print("Estado_salida1 = ");
  Serial.println(EEPROM.read(0));
  digitalWrite(salida2, EEPROM.read(1));
  estado_salida2=EEPROM.read(1);
  Serial.print("Estado_salida2 = ");
  Serial.println(EEPROM.read(1));
  digitalWrite(salida3, EEPROM.read(2));
  estado_salida3=EEPROM.read(2);
  Serial.print("Estado_salida3 = ");
  Serial.println(EEPROM.read(2));
  digitalWrite(salida4, EEPROM.read(3));
  estado_salida4=EEPROM.read(3);
  Serial.print("Estado_salida4 = ");
  Serial.println(EEPROM.read(3));
  digitalWrite(salida5, EEPROM.read(4));
  estado_salida5=EEPROM.read(4);
  Serial.print("Estado_salida5 = ");
  Serial.println(EEPROM.read(4));
  digitalWrite(salida6, EEPROM.read(5));
  estado_salida6=EEPROM.read(5);
  Serial.print("Estado_salida6 = ");
  Serial.println(EEPROM.read(5));
   
  delay(200);
}

void loop() {



    if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("ESP8266: esp6en1")) {
        client.publish("outTopic",(String)"hello world, I'm "+host);
        client.subscribe(host+(String)"/#");
      }
    }
    if (client.connected())

      client.loop();
  }

 
}



