
// FUNCIONES:  que cierran y abren el mecanismo de la puerta configurado para la maqueta
void Cerrar() {
  Serial.println("CERRANDO");
  delay(2000);
  int i = 15;
  for(i =  15; i <= 90; i++)
  {
  servo.write(i);
  }
  estado = "cerrado";
}

void Abrir() {
    Serial.println("ABRIENDO");
    delay(1000);
    int c =90; 
    for(c = 90; c >= 15; c--)
    {
      servo.write(c);
    }
    estado = "abierto";
}
