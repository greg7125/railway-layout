class Timer {
  public:
    Timer () {}
    Timer (uint32_t nprd) {
      start(nprd);
    }
    void start(uint32_t nprd) {
      prd = nprd;
      start();
    }
    void start() {
      tmr = millis();
      if (!tmr) tmr = 1;
    }
    void stop() {
      tmr = 0;
    }
    bool ready() {
      if (tmr && millis() - tmr >= prd) {
        start();
        return 1;
      }
      return 0;
    }

  private:
    uint32_t tmr = 0, prd = 0;
};

#include <iarduino_I2C_Relay.h>
#include <Wire.h>
#include <Bounce2.h>

#define PIN_RELAY 2 //реле вперед
#define PIN_2RELAY 3 // реле назад
#define PIN_LED 4 // реле освещение дома
#define PIN_LED1 6  // освещение секторов 1-4
#define PIN_LED2 5
#define PIN_LED3 8
#define PIN_LED4 7

#define magnetPin1 9
#define magnetPin2 10
#define magnetPin3 11

//Таймеры (см класс таймер (пс оформить в библиотеку ;избавиться от макарон))
Timer tmr1(1000); //интервал между включением и отключением подсветки
Timer tmr2; //отвечает за работу манипулятора
Timer tmr3; // не забыть как это все работет https://alexgyver.ru/lessons/class/)


//создадим объект геркона  [библиотека:раздел] [переменная] = [функция из библиотеки]
//Bounce2::Button magnetPin1 = Bounce2::Button();
//Bounce2::Button magnetPin2 = Bounce2::Button();
//Bounce2::Button magnetPin3 = Bounce2::Button();

Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 

//объявим герконы и переменные к которым они привязаны
//const int magnetPin1 = 9; // номер пина, к которому подключен геркон
//int magnetState1 = 0; // переменная для хранения состояния геркона

//const int magnetPin2 = 10; // номер пина, к которому подключен геркон
//int magnetState2 = 0; // переменная для хранения состояния геркона

//const int magnetPin3 = 11; // номер пина, к которому подключен геркон
//int magnetState3 = 0; // переменная для хранения состояния геркона

//вся шляпа относящаяся к состоянию пинов
int PIN_RELAY = 2; // пин, состояние которого мы хотим узнать
int PIN_RELAY_state = digitalRead(PIN_RELAY); // считываем состояние пина

int PIN_2RELAY = 3; 
int PIN_2RELAY_state = digitalRead(PIN_2RELAY); 

int PIN_LED = 4; 
int PIN_LED_state = digitalRead(PIN_LED); 

int PIN_LED1 = 5; 
int PIN_LED1_state = digitalRead(PIN_LED1); 

int PIN_LED2 = 6; 
int PIN_LED2_state = digitalRead(PIN_LED2); 

int PIN_LED3 = 8; 
int PIN_LED3_state = digitalRead(PIN_LED3); 

int PIN_LED4 = 7; 
int PIN_LED4_state = digitalRead(PIN_LED4); 

int serialBite = 1; //если не будет работать поменяй на 0.
uint32_t myTimer1;

void setup() {
  Serial.begin(9600);
    
  //задать все пины, входы и переменные
  Serial.begin(9600);
  //Serial.print ('board started for usind Automatic mode print "1" or wait 5 second ');
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_2RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);

  // SELECT ONE OF THE FOLLOWING :
  // 1) IF YOUR BUTTON HAS AN INTERNAL PULL-UP
   button.attach( BUTTON_PIN ,  INPUT_PULLUP ); // USE INTERNAL PULL-UP
  // 2) IF YOUR BUTTON USES AN EXTERNAL PULL-UP
 // button.attach( BUTTON_PIN, INPUT ); // USE EXTERNAL PULL-UP
// герконы  INPUT_PULLUP
  pinMode(magnetPin1, INPUT_PULLUP); // устанавливаем пин на вход
  debouncer1.attach(magnetPin1);
  debouncer1.interval(5); // interval in ms

  pinMode(magnetPin2, INPUT_PULLUP); // устанавливаем пин на вход
  debouncer2.attach(magnetPin2);
  debouncer2.interval(5); // interval in ms

  pinMode(magnetPin3, INPUT_PULLUP); // устанавливаем пин на вход
  debouncer3.attach(magnetPin3);
  debouncer3.interval(5); // interval in ms


}

void loop() {
if (Serial.available() > 0) {
    serialBite = Serial.read();
    Serial.print("received: ");
    Serial.println(serialBite);
  }
}


if (serialBite = 1) or (millis()  - myTimer1 >= 5000) {   // таймер на 5с
    myTimer1 = millis();              // сброс таймера
 // начало цикла

  //освещение города (10 с)

  digitalWrite(PIN_LED, HIGH); //активировать питание домов
  if (tmr1.ready ()) digitalWrite(PIN_LED1, HIGH); //активировать питание дорожного света
  tmr1.start();
  if (tmr1.ready ()) digitalWrite(PIN_LED2, HIGH);
  tmr1.start();
  if (tmr1.ready ()) digitalWrite(PIN_LED3, HIGH);
  tmr1.start();
  if (tmr1.ready ()) digitalWrite(PIN_LED4, HIGH);
  tmr1.start();



  //Движение поезда (n с)

  digitalWrite(PIN_RELAY, HIGH); //0-1 загрузка

  debouncer1.update();
  debouncer2.update();
  debouncer3.update();

  char magnetState1 = debouncer1.read();
  char magnetState2 = debouncer2.read();
  char magnetState3 = debouncer3.read();

  magnetState1 = digitalRead(magnetPin1);
  while (magnetState1 == 1)
  {
    digitalWrite(PIN_RELAY, LOW);
  }

  tmr2.start(2000);
  if (tmr2.ready()) digitalWrite(PIN_RELAY, HIGH); //1-2 выгрузка

  magnetState2 = digitalRead(magnetPin2);
  while (magnetState2 == 1)
  {
    digitalWrite(PIN_RELAY, LOW);
  }

  
  tmr2.start(2000);
  if (tmr2.ready()) digitalWrite(PIN_RELAY, HIGH); //2-2 холостой ход и загрузка

  magnetState3 = digitalRead(magnetPin3);
  while (magnetState3 == 1)
  {
    digitalWrite(PIN_RELAY, LOW);
  }


  tmr2.start(2000);
  if (tmr2.ready()) digitalWrite(PIN_RELAY, HIGH); //2-r1 выгрузка

  magnetState2 = digitalRead(magnetPin2);
  while (magnetState2 == 1)
  {
    digitalWrite(PIN_2RELAY, LOW);
  }


  tmr2.start(2000);
  if (tmr2.ready()) digitalWrite(PIN_RELAY, HIGH); //1-r0 холостой ход и базирование

  magnetState1 = digitalRead(magnetPin1);
  while (magnetState1 == 1)
  {
    digitalWrite(PIN_2RELAY, LOW);
  }
  
  
  tmr2.start(2000);
  if (tmr2.ready()) digitalWrite(PIN_RELAY, LOW) digitalWrite(PIN_2RELAY, LOW); //1-2 выгрузка




  //отключение светва
  if (tmr1.ready ()) digitalWrite(PIN_LED3, LOW);
  tmr1.start();
  if (tmr1.ready ()) digitalWrite(PIN_LED4, LOW);
  tmr1.start();

  if (tmr1.ready ()) digitalWrite(PIN_LED1, LOW);

  if (tmr1.ready ()) digitalWrite(PIN_LED2, LOW);
  tmr1.start();
  tmr3.start(3000);
  if (tmr3.ready ()) digitalWrite(PIN_LED, LOW);
  tmr1.start();


  }
  
  
  
   else if (serialBite == '2') {
     //все реле и осещение переводится а положение 0. первый блок полностью прерывается
	 digitalWrite(PIN_RELAY, LOW);
	 digitalWrite(PIN_2RELAY, LOW);
	 digitalWrite(PIN_LED, LOW);
	 digitalWrite(PIN_LED1, LOW);
	 digitalWrite(PIN_LED2, LOW);
	 digitalWrite(PIN_LED3, LOW);
	 digitalWrite(PIN_LED4, LOW);
  }
  
  else if (serialBite == '3') {
    //Moving forward
  if PIN_RELAY_state == LOW {
	  digitalWrite(PIN_RELAY, HIGH);
  }
  else {
	  digitalWrite(PIN_RELAY, LOW);
  }
  }
  
  else if (serialBite == '4'){
//Moving back
  if PIN_2RELAY_state == LOW {
	  digitalWrite(PIN_2RELAY, HIGH);
  }
  else {
	  digitalWrite(PIN_2RELAY, LOW);
  }
  }
  else if (serialBite == '5'){
//house light
  if PIN_RELAY_state == LOW {
	  digitalWrite(PIN_LED, HIGH);
  }
  else {
	  digitalWrite(PIN_LED, LOW);
  }
  }

  else if (serialBite == '6'){
//road light 1
  if PIN_RELAY_state == LOW {
	  digitalWrite(PIN_LED1, HIGH);
  }
  else {
	  digitalWrite(PIN_LED1, LOW);
  }
  }

  else if (serialBite == '7'){
//road light 2
  if PIN_RELAY_state == LOW {
	  digitalWrite(PIN_LED2, HIGH);
  }
  else {
	  digitalWrite(PIN_LED2, LOW);
  }
  }

  else if (serialBite == '8'){
//road light 3
  if PIN_RELAY_state == LOW {
	  digitalWrite(PIN_LED3, HIGH);
  }
  else {
	  digitalWrite(PIN_LED3, LOW);
  }
  }

  else if (serialBite == '9'){
//road light 4
  if PIN_RELAY_state == LOW {
	  digitalWrite(PIN_LED4, HIGH);
  }
  else {
	  digitalWrite(PIN_LED4, LOW);
  }
  }

