/*
 * Ing. Rafael Lozano
 * Taloselectronics
 * 22-Enero-2019
 */
#include <HX711.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DOUT  A1
#define CLK  A0

HX711 balanza(DOUT, CLK);

//Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2); //

//Variables para calibracion
int Peso_conocido=493;//493 gramos

//funciones
void Calibrar(void);

void setup()
{
  Serial.begin(9600);
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();
  
  Calibrar();
  Serial.println("Listo para pesar");

}

void loop()
{
  float peso = balanza.get_units(10);
  if(peso<1) peso=peso*-1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Peso:");
  lcd.setCursor(5, 0);
  lcd.print(peso,1);
  lcd.print(" g");
  Serial.print("Peso: ");
  Serial.print(peso, 1);
  Serial.println(" g");
  delay(50);
}

void Calibrar(void)
{
  float escala;
  float medicion;
  balanza.set_scale(); //La escala por defecto es 1
  balanza.tare(20);  //20 mediciones
 
  for(int i=3;i>=0;i--)
  { 
    lcd.print("Coloque el peso");
    lcd.setCursor(0,1);
    lcd.print(i);
    medicion=balanza.get_value(20);//20 mediciones
    lcd.clear();
    
  }
  
  for(int i=3;i>=0;i--)
  {
    lcd.print("Retire el peso");
    lcd.setCursor(0,1);
    lcd.print(i);
    delay(1000);
    lcd.clear();
  }
  
  escala=medicion/Peso_conocido;
  balanza.set_scale(escala);
}
