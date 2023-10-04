#include <SoftwareSerial.h>
SoftwareSerial mygsm(7, 8);

int Buz = 4;
void NetSet();
void Httpget ();
String Response;
void setup()
{
  pinMode (Buz, OUTPUT);
  mygsm.begin(9600);
  Serial.begin(9600);
  delay(20000);

NetSet();
  
 

}

void loop()
{
Httpget ();
}


void printSerialData()
{
  while (Serial.available() != 0)
    Serial.write(Serial.read());
}

void NetSet(){

mygsm.println("AT+CMEE=1");
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  mygsm.println("AT+CSQ");
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  mygsm.println("AT+CPIN?");    //To check whether Sim card is present or not in module added by Anuja
  //  delay(2000);  // Delay of 1000 milli seconds or 1 second

  Response = mygsm.readStringUntil('K');
  Serial.println(Response);
  mygsm.println("AT+CREG?\r");    //Check the registration status
  //  delay(2000);  // Delay of 1000 milli seconds or 1 second

  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  /* Serial.println("AT+CGATT=1");
    delay(200);
    printSerialData();*/

  mygsm.println("AT+CGATT=1\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  // Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR,connection type is GPRS
  // delay(1000);
  // printSerialData();

  mygsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  // Serial.println("AT+SAPBR=3,1,\"APN\",\"\"");//setting the APN,2nd parameter empty works for all networks
  // delay(5000);
  // printSerialData();

  mygsm.println("AT+SAPBR=3,1,\"APN\",\"\"\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  mygsm.println();
  // Serial.println("AT+SAPBR=1,1");
  // delay(10000);
  // printSerialData();

  mygsm.println("AT+SAPBR=1,1\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  // Serial.println("AT+HTTPINIT"); //init the HTTP request
  // delay(2000);
  // printSerialData();
}

void Httpget ()
{
  mygsm.println("AT+HTTPINIT\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  // Serial.println("AT+HTTPPARA=\"URL\",\"https://yevatekar.com/edi/get_status.php\"");// setting the httppara,
  // //the second parameter is the website from where you want to access data
  // delay(1000);
  // printSerialData();//http://localhost/shaunak/get_status.php

  mygsm.println("AT+HTTPPARA=\"URL\",\"http://yevatekar.com/edi/get_status.php\"\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  mygsm.println();
  // Serial.println("AT+HTTPACTION=0");//submit the GET request
  // delay(8000);//the delay is important if the return datas are very large, the time required longer.
  // printSerialData();

  mygsm.println("AT+HTTPACTION=0\r");
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  Response = mygsm.readStringUntil('\0');
  Serial.println(Response);

  // Serial.println("AT+HTTPREAD");// read the data from the website you access//AT+HTTPREAD=0,20
  // delay(3000);
  // printSerialData();

  mygsm.println("AT+HTTPREAD\r"); //AT+HTTPREAD=0,20
  //  delay(2000);
  Response = mygsm.readStringUntil('K');
  Serial.println(Response);

  if (Response.indexOf(":\"1") != -1){
  digitalWrite (Buz,HIGH);
  Serial.println ("Buz: ON!");
} else if (Response.indexOf(":\"0") != -1){
 digitalWrite (Buz,LOW);
  Serial.println ("Buz: OFF!");
}

mygsm.println("");
Response = mygsm.readStringUntil('\0');
           Serial.println(Response);

//           delay(1000);

           // Serial.println("AT+HTTPTERM");// terminate HTTP service
           // printSerialData();

           mygsm.println("AT+HTTPTERM\r");
           //  delay(2000);
           Response = mygsm.readStringUntil('K');
           Serial.println(Response); 
}
