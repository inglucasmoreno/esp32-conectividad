#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include "BluetoothSerial.h"

#include "equi_eeprom.h"    // (1)
#include "equi_bluetooth.h" // (2)
#include "equi_wifi.h"      // (3)

// Credenciales WiFi
String ssid = "hola";
String password = "mundo";

// Comando y Valor - Bluetooth
String comando = "";
String valor = "";

// Flags
bool wifi_activado = false;

// Funcion: Acciones
void actions() {
  
  // Manejo de BUILTIN_LED
  if(comando == "led"){
    if(valor == "encender") digitalWrite(BUILTIN_LED, HIGH);
    else if(valor == "apagar") digitalWrite(BUILTIN_LED, LOW);
    else Serial.println("Valor para comando LED invalido!");
  }

  // Manejo de RED WIFI

  // Configuracion de SSID
  if(comando == "ssid"){
    if(valor != ""){
      ssid = valor;
      escribir_eeprom(0, valor);
      Serial.println("SSID configurado!");
    }
  }

  // Configuracion de password
  if(comando == "password"){
    if(valor != ""){
      password = valor;
      escribir_eeprom(50, valor);
      Serial.println("PASSWORD configurado!");
    }
  }

  // Activar/Desactivar conexion wifi
  if(comando == "wifi"){
    if(valor == "conectar"){
      wifi_activado = true;
      connect_wifi(ssid.c_str(), password.c_str(), wifi_activado);
    }
    else if(valor == "desconectar"){
      Serial.println("");
      Serial.println("Desconexion a Red WiFi Exitosa!");
      WiFi.disconnect();
      wifi_activado = false;
    }
    else Serial.println("Valor para comando WiFi invalido!");
  }

}

// Funcion: Setup
void setup() {
  Serial.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  init_eeprom();
  init_bluetooth("ESP32_ET");
  init_wifi(ssid, password, wifi_activado);
}

// Funcion: Loop
void loop() {
  
  // WiFi - Conexion/Reconexion 
  if(WiFi.status() != WL_CONNECTED && wifi_activado) {
    connect_wifi(ssid.c_str(), password.c_str(), wifi_activado);
  }   

  // Bluetooth - Puerto serie
  if(SerialBT.available()) {
    recepcion_bluetooth(comando, valor);
    actions();
  }

  delay(20);
}