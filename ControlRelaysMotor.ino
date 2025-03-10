#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Configuración del teclado matricial 4x4
const byte ROWS = 4;
const byte COLS = 4;

const byte relay = 11, pwm = 10;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// Inicializar la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Configuración de pines de salida
  pinMode(relay,OUTPUT);
  pinMode(pwm,OUTPUT);

  lcd.init();  // Inicializar la pantalla LCD
  lcd.backlight();  // Encender la luz de fondo
  lcd.print("Iniciando sistema...");
  Serial.begin(9600);
  delay(1500);
}



char seleccionarSentido() {
  char seleccion_sentido = '0';
  bool input_valido = false;
  
  
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seleccione sentido:");
  lcd.setCursor(0, 1);
  lcd.print("1. Horario");
  lcd.setCursor(0, 2);
  lcd.print("2. Antihorario");
  
  delay(300);

  while(seleccion_sentido != '1' && seleccion_sentido != '2'){
    seleccion_sentido = keypad.getKey();
  }
    
  return seleccion_sentido;
}


byte seleccionarVelocidad() {
  char input = '0';
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seleccione potencia:");
  lcd.setCursor(0, 1);
  lcd.print("1. 0%    2. 25%");
  lcd.setCursor(0, 2);
  lcd.print("3. 50%   4.100%");
  

  while(input != '1' && input != '2' && input != '3' && input != '4'){
    input = keypad.getKey();
    delay(300);
  }

  switch(input){
    case '1':return 0;
    case '2':return 25;
    case '3':return 50;
    case '4':return 100;
    default:return 0;
  }
    

}



void loop() {
  char sentido = '0';
  byte velocidad = 0;
  sentido = seleccionarSentido();
  lcd.clear();
  lcd.setCursor(0, 0);
  velocidad = seleccionarVelocidad();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Girando");
  
  if(sentido == '1'){
    digitalWrite(relay,HIGH);
  }
  else if( sentido == '2'){
    digitalWrite(relay,LOW);
  }
  analogWrite(pwm,velocidad);
  
  delay(3000);

  digitalWrite(relay,LOW);
  analogWrite(pwm,0);
  
}
