/* 
  Tipo: Libreria
  Descripcion: Conexion WiFi
  Autor: Ing. Lucas Omar Moreno
  Año: 2021
*/

// Inicializacion de wifi
void init_wifi(String& ssid, String& password, bool& wifi_activado){
  
  // Se obtienen los datos desde la EEPROM
  ssid = leer_eeprom(0);
  password = leer_eeprom(50);
  
  if(ssid == "" || password == ""){
    wifi_activado = false;
  }else{
    wifi_activado = true;
  }

}

// Conexion a Red WiFi
// Parametro -> constantes punteros -> Credenciales WiFi -> const char* ssid | const char* password
void connect_wifi(const char* ssid, const char* password, bool& wifi_activado){
  Serial.println("Conexion WiFi");
  Serial.print("Conectando a -> ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED && wifi_activado){
    // Desactivar intento de conexion  
    if(SerialBT.available()){
      String mensaje = SerialBT.readStringUntil('\n');
      int posicionGuion = mensaje.indexOf('-');
      int posicionSaltoLinea = mensaje.length();
      String comando = mensaje.substring(0,posicionGuion);
      String valor = mensaje.substring(posicionGuion + 1, posicionSaltoLinea);
      if(comando == "wifi" && valor == "desactivar"){
        wifi_activado = false;
      }
    };
    Serial.print(".");
    delay(250);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("");
    Serial.println("No se pudo establecer conexion WiFi");
  }else{
    Serial.println("");
    Serial.println("Conexion exitosa!");
    Serial.print("Mi IP es -> ");
    Serial.print(WiFi.localIP());
  }

}
