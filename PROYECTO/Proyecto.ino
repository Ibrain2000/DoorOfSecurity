////////////// DoorOfSecurity \\\\\\\\\\\\\\

/*

AUTOR : IBRAIN ENCINAS 
COLABORADORA : MELISA FLORES TORTOLAY 
ESTADO: TERMINADO
FECHA : 1/02/2019

*/

#include <LiquidCrystal_I2C.h>//CONFIGURACION DE PANTALLA
LiquidCrystal_I2C lcd(0x3F, 16 , 2); // CONFIGURAMOS NUESTRA DIRECCION I2C Y TAMANO DEL LCD
#include <Keypad.h> //LIBRERIA DEL TECLADO 
//INICIALIZACION Y CONFIGURACION
#include <Servo.h> // LIBRERIA SERVOMOTOR
Servo servo;
const byte filas = 4;
const byte col = 4;
char teclas[filas][col] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte pinCol[col] = {6, 5, 4, 3};
byte pinFila[filas] = {10, 9, 8, 7};
Keypad teclado = Keypad(makeKeymap(teclas), pinFila, pinCol, filas, col);

//Mis Variables

char tecla;
String estado;
char palabra[9];
char clave[9] = "22222222";
int i = 0;

// variables de boton
int boton ;
int fdc;

// PINES UTILIZADOS
#define botonPin 2
#define fdcPin 12
#define servoPin 11

void setup() {
  Serial.begin(9600);
  lcd.begin();

  pinMode(botonPin, INPUT);
  servo.attach(servoPin);
  pinMode(fdcPin, INPUT);

  Cerrar();
}



void loop() {

  Serial.println(estado);
  Serial.println(digitalRead(fdcPin));
  if (estado == "cerrado" && digitalRead(fdcPin) == 1) {
    while (i < 8 ) {
      if (digitalRead(botonPin) == 1) {
        Abrir();
        delay(2000);
        break;
      }
      char car = teclado.getKey();
      if (car)
      {
        palabra[i] = car;
        lcd.setCursor(i, 0);
        lcd.print('*');
        i++;
      }
      
    }
    delay(20);
    
    while (i == 8) {
      if (teclado.getKey() == 'C') {
        {
          if (!strcmp(palabra, clave))
          {
            lcd.setCursor(0, 1);
            lcd.print(" CORRECTO ");
            Serial.println(" Correcto");
            i = 0;
            memset(palabra, 0, sizeof(palabra));
            Abrir();
            Serial.println(estado);
            Serial.println(digitalRead(fdcPin));
            delay(2000);
          }
          else
          {
            lcd.setCursor(0, 1);
            lcd.print(" INCORRECTO ");
            Serial.println(" incorrecto");
            i = 0;
            memset(palabra, 0, sizeof(palabra));
          }
        }
        delay(1000);
        lcd.clear();

      }
    }
  }
  
  else if (estado == "abierto" && digitalRead(fdcPin) == 1) {
    Cerrar();
    Serial.println(estado);
    Serial.println(digitalRead(fdcPin));
  }
}
