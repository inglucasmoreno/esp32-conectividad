/* 
  Tipo: Libreria
  Descripcion: Manejo de memoria EEPROM
  Autor: Ing. Lucas Omar Moreno
  Año: 2021
*/

// Inicializacion de EEPROM
void init_eeprom(){
  EEPROM.begin(512);
}

// Leer EEPROM
String leer_eeprom(int addr){
  byte lectura;
  String strLectura;
  for(int i = addr; i < addr+50; i++){
    lectura = EEPROM.read(i);
    if(lectura != 255){ strLectura += (char)lectura; }
  }
  return strLectura;
}

// Escribir EEPROM
void escribir_eeprom(int addr, String text){
  int tamano = text.length();
  char inChar[50];
  text.toCharArray(inChar, tamano+1);
  for(int i = 0; i < tamano; i++){
    EEPROM.write(addr+i, inChar[i]);
  }
  for(int i = tamano; i < 50; i++){
    EEPROM.write(addr+i, 255);    
  }
  EEPROM.commit();
}