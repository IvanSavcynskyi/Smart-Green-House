#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h> 

#define moisture_sensor A0 
#define moisture_sensor_power 16


#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

int very_moist_value = 0;

const char* ssid = "TP-Link_82DC";  // SSID
const char* password = "20829803"; // пароль

ESP8266WebServer server(80);

void setup() 
{
  Serial.begin(115200);
  delay(100);
  pinMode (moisture_sensor_power, OUTPUT);
  dht.setup(D4, DHTesp::DHT11);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  // Підключаємся до wifi 
  WiFi.begin(ssid, password);

  // Перевірка підключення
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/api", handle_OnApi);

  server.onNotFound(handle_NotFound);

  server.on("/", handle_On);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() 
{
  server.handleClient();
}

void handle_OnApi() 
{
  digitalWrite (moisture_sensor_power, HIGH);
  delay(10);
  int moisture_value = analogRead (moisture_sensor);
  digitalWrite(moisture_sensor_power, LOW);
  int moisture_value_percent= map (moisture_value, very_moist_value, 1023, 100, 0);
  String humidity = String (moisture_value_percent) + "%";

  delay(dht.getMinimumSamplingPeriod());

  float air_humidity = dht.getHumidity();
  float air_temperature = dht.getTemperature();
  
  server.send(200, "text/html", SendHTML(humidity=humidity, air_humidity=air_humidity, air_temperature=air_temperature)); 
  
}
void handle_On() 
{
  digitalWrite (moisture_sensor_power, HIGH);
  delay(10);
  int moisture_value = analogRead (moisture_sensor);
  digitalWrite(moisture_sensor_power, LOW);
  int moisture_value_percent= map (moisture_value, very_moist_value, 1023, 100, 0);
  String humidity = String (moisture_value_percent) + "%";

  delay(dht.getMinimumSamplingPeriod());

  float air_humidity = dht.getHumidity();
  float air_temperature = dht.getTemperature();
  
  server.send(200, "text/html", SendHTML1(humidity=humidity, air_humidity=air_humidity, air_temperature=air_temperature)); 
  
}
void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(String humidity, float air_humidity, float air_temperature)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Hallo</title>\n";
  ptr +="<h1>humidity</h1>\n";
  ptr +="<p class=humidity>";
  ptr +=humidity;
  ptr +="</p>\n";
  ptr +="<h1>air_humidity</h1>\n";
  ptr +="<p class=air_humidity>";
  ptr +=air_humidity;
  ptr +="</p>\n";
  ptr +="<h1>air_temperature</h1>\n";
  ptr +="<p class=air_temperature>";
  ptr +=air_temperature;
  ptr +="</p>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

String SendHTML1(String humidity, float air_humidity, float air_temperature)
{
String prt = "<!DOCTYPE html>";
               prt+=  "<html lang=ua>"; 
      prt+="                                              <head>";
                        prt+="                                <meta charset=UTF-8>";
                                  prt+="                      <title>SmartGreenHause</title>";
       prt+="                                             </head>";
      prt+="                                              <body>";
                        prt+="                                <div class=data_now>";
                                     prt+="                       <div class=header_data_now>  ";
                                                    prt+="        <h1>Показники датчиків на даний момент:</h1>";
              prt+="                                              </div>";
                            prt+="                                <div class=humidity>";
               prt+="                                                 <p>";
                                   prt +=humidity;
            prt+="                               </p>";
              prt+="                                              </div>";
                                prt+="                            <div class=air_humidity>";
                prt+="                                                <p>";
           prt +=air_humidity;
           prt+="                           </p>";
              prt+="                                              </div>";
                                   prt+="                         <div class=air_temperature>";
                prt+="                                                <p>";
                 prt +=air_temperature; 
           prt+="                                       </p>";
              prt+="                                              </div>";
          prt+="                                              </div>";

                         prt+="                               <div class=good_data>";
                                      prt+="                      <div class=header_good_data>  ";
                                                  prt+="              <h1>Хороші показники для рослини:</h1>";
              prt+="                                              </div>";
                            prt+="                                <div class=humidity>";
                                                   prt+="             <p>Вологість грунту: від 60% до 70%</p>";
              prt+="                                              </div>";
                                prt+="                            <div class=air_humidity>";
                                                    prt+="            <p>Вологість повітря: від 55% до 65%</p>";
              prt+="                                              </div>";
                                   prt+="                         <div class=air_temperature>";
                                                      prt+="          <p>Температура повітря: від 19* до 22*</p>";
              prt+="                                              </div>";
          prt+="                                            </div>";

                           prt+="                             <div class=normal_data>";
                                          prt+="                  <div class=header_normal_data>  ";
                                                     prt+="           <h1>Нормальні показники для рослини:</h1>";
              prt+="                                              </div>";
                            prt+="                                <div class=humidity>";
                                                   prt+="             <p>Вологість грунту: від 50% до 80%</p>";
              prt+="                                              </div>";
                                prt+="                            <div class=air_humidity>";
                                                    prt+="            <p>Вологість повітря: від 45% до 70%</p>";
              prt+="                                              </div>";
                                   prt+="                         <div class=air_temperature>";
                                                        prt+="        <p>Температура повітря: від 17.5* до 25*</p>";
              prt+="                                              </div>";
          prt+="                                              </div>";
prt+="                                                    ";
                        prt+="                                <div class=bad_data>";
                                     prt+="                       <div class=header_bad_data>  ";
                                prt+="          <h1> Погані  показники  для  рослини:</h1>";
              prt+="                                              </div>";
                            prt+="                                <div class=humidity>";
                                       prt+="   <p>Вологість грунту: менше 60% або більше 70%</p>";
              prt+="                                              </div>";
                                prt+="                            <div class=air_humidity>";                                      
                                prt+="  <p>Вологість повітря: менше 55% або більше 65%</p>";
              prt+="                                              </div>";
                                   prt+="                         <div class=air_temperature>";
                                             prt+="<p>Температура повітря: менше 19* або більше 22*</p>";
              prt+="                                              </div>";
          prt+="                                              </div>";
           prt+="                                             <style>";
         prt+="                                               html{";
                                   prt+="                background-image: url(./plants.jpg);";
                                prt+="                       background-repeat: no-repeat;";
                                           prt+="                 background-position: center center;";
                                     prt+="                       background-attachment: fixed;";
                             prt+="                     -webkit-background-size: cover;";
                                    prt+="                        -moz-background-size: cover;";
                                  prt+="                          -o-background-size: cover;";
                               prt+="                             background-size: cover;";
                      prt+="                                      opacity: 0.75;";
                       prt+="                                     background-color: rgb(109, 234, 188)";
     prt+="                                                   }";
              prt+="                                          .data_now{";
                                 prt+="               background-color: rgb(105, 216, 224);";
                      prt+="                                      padding: 10px;";
                            prt+="                                border-radius: 20px;";
                           prt+="                                 text-align: center;";
     prt+="                                                   }";
               prt+="                                         .good_data{";
                              prt+="               background-color: rgb(105, 224, 123);";
                     prt+="                                       padding: 7px;";
                            prt+="                                border-radius: 20px;";
                           prt+="                                 text-align: center;";
                         prt+="                                   max-width: 490px;";
                          prt+="                                  max-height: 500px;";
                    prt+="                                        margin: 5px;";
                    prt+="                                        float: left;";
     prt+="                                                   }";
                 prt+="                                       .normal_data{";
             prt+="               background-color: rgb(224, 192, 105);";
                            prt+="                                border-radius: 20px;";
                            prt+="                                text-align: center; ";
                     prt+="                                       width: 510px;";
                      prt+="                                      height: 197px;";
                    prt+="                                        margin: 5px;";
                    prt+="                                        float: left;";
                          prt+="                                  margin-left: 20px;";
prt+="                                 margin-right: 20px;";
prt+="                                                   }";
                        prt+="                                .header_normal_data{";
                         prt+="                                   font-size: 0.9em;";
     prt+="                                                   }";
              prt+="                                          .bad_data{";
    prt+="               background-color: rgb(224, 105, 105);";
                     prt+="                                       padding: 1px;";
                            prt+="                                border-radius: 20px;";
                           prt+="                                 text-align: center;";
                         prt+="                                   max-width: 500px;";
                      prt+="                                     height: 197px;";
                    prt+="                                       margin: 5px;";
                     prt+="                                      float: right;";
     prt+="                                                  }";
            prt+="                                           </style>";
       prt+="                                            </body>";
        prt+="                                           </html>"; 
return prt;
}
