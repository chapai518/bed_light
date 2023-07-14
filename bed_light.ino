#define LIGHT1 3   //мосфет на подсветку
#define PIR1 2     //датчик движения
//#define LS1 6      //датчик освещенности
#define POTEN1 A7  //потенциометр уровня подсветки
bool full_light = 0;  //флаг активности полной подсветки
int wait = 30000;    //задержка угасания если нет активности в ms
void setup() {
    pinMode(LIGHT1,OUTPUT);
    pinMode(13,OUTPUT);
}

void loop() {
  int poten = analogRead(POTEN1);  //читаем потенциометр
  bool pir = digitalRead(PIR1);   //читаем датчик движния
//  bool ls = digitalRead(LS1);    //читаем датчик освещенности
  poten = map(poten,0,1023,0,255);    //преобразуем аналог в цифру
//  if (ls == 1) {
//    poten = poten * 0.5;        //убавляем подсветку на 50% в темноте
//  }
  if (pir == 0) {           //если датчик движения не активен
    digitalWrite(13,0);
    if (full_light == 1) {      //и свет горит на полную
     for (int i = 255; i > poten; i-=5) {       //плавно гасим до номинала
      analogWrite(LIGHT1, i);
      delay(50);
    }
    full_light = 0;   //убираем флаг полной активности подсветки
    }
    else {
      analogWrite(LIGHT1, poten);  //включаем фоновою подсветку
    }
  }
  if (pir == 1) {       //если датчик движения активен
  digitalWrite(13,1);
   if (full_light == 0) {     //и свет не горит на полную
    for (int i = poten; i < 255; i+=5) {       //плавно зажигаем на 100%
      analogWrite(LIGHT1, i);
      delay(50);
    }
      analogWrite(LIGHT1, 255);       //и вклчаем его на некоторое время
      full_light = 1;   //вешаем флаг полной активности подсветки
      delay(wait);
    }
   else {
      analogWrite(LIGHT1, 255);    //если датчик движения активен и свет не горит на полную оставляем его рабоать
      full_light = 1;    //оставляем флаг полной активности подсветки
      delay(wait);
   }
  }
}

