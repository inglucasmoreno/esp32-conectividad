/* 
  Tipo: Libreria
  Descripcion: Conexion Bluetooth
  Autor: Ing. Lucas Omar Moreno
  Año: 2021
*/

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// Inicializacion de Bluetooth
// Parametro -> Nombre del dispositivo -> String name
void init_bluetooth(String name) {
  SerialBT.begin(name); // Nombre de dispositivo Bluetooth
  Serial.println("Dispositivo inicializado...");
  Serial.println("Ahora puedes establecer una conexion bluetooth!");  
}

// Recepcion bluetooth
// Parametros -> Posicion de memoria de variables -> String comando | String valor
void recepcion_bluetooth(String& comando, String& valor){
  
  String mensaje = SerialBT.readStringUntil('\n');
  int posicionGuion = mensaje.indexOf('-');
  int posicionSaltoLinea = mensaje.length();

  comando = mensaje.substring(0,posicionGuion);
  valor = mensaje.substring(posicionGuion + 1, posicionSaltoLinea);

}
