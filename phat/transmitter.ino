#include <IRremote.h>

IRsend irsend;

int analogPinTien = A0;
int analogPinLui = A1;
int analogPinTrai= A2;
int analogPinPhai = A3;
int amount = 3; // so luong tin hieu phat ra khi nhan duoc am thanh
int nguong = 650; // nguong am thanh, vuot nguong nay thi se thu tin hieu
int tien;
int lui;
int phai;
int trai;
void setup() {
  Serial.begin(9600);           //  khoi tao serial
}
int max = 0;
void readSoundSensor() { // doc cuong do am thanh cua 4 cam bien
  tien = analogRead(analogPinTien);
  lui = analogRead(analogPinLui);
  phai = analogRead(analogPinPhai);
  trai = analogRead(analogPinTrai);
}
void findSignalMax() { // Tim tim cuong do am thanh lon nhat thu duoc tu 4 cam bien trong 1 thoi diem
  max = 0;
  if (max < tien) {
    max = tien;
  }
  if (max < lui) {
    max = lui;
  }
  if (max < phai) {
    max = phai;
  }
  if (max < trai) {
    max = trai;
  }
}
void loop() {
  readSoundSensor(); // doc lai tin hieu cuong do tu cam bien am thanh trong vong lap loop
  while (tien > nguong || lui > nguong || phai > nguong || trai > nguong) { // vong lap thuc hien khi co tin hieu vuot nguong
    findSignalMax();// tim tin hieu cuong do am thanh lon nhat
    if (max == tien) {
      Serial.print("Tien : "); Serial.println(tien); // Print ma ra serial
      for (int i = 0; i < amount; i++) { // goi ma lien tuc neu nhan duoc tin hieu
        irsend.sendRC5(0xa90, 12); // Goi tin hieu dinh dang RC5 co ma HEX 0xa90, 12 bits
        delay(40);
      }
    }
    if (max == lui) {
      Serial.print("Lui : "); Serial.println(lui);
      for (int i = 0; i < amount; i++) { // goi ma lien tuc neu nhan duoc tin hieu
        irsend.sendRC5(0xa91, 12); // Goi tin hieu dinh dang RC5 co ma HEX 0xa91, 12 bits
        delay(40);
      }
    }
    if (max == phai) {
      Serial.print("Phai : "); Serial.println(phai); // Print ma ra serial
      for (int i = 0; i < amount; i++) { // goi ma lien tuc neu nhan duoc tin hieu
        irsend.sendRC5(0xa92, 12); // Goi tin hieu dinh dang RC5 co ma HEX 0xa92, 12 bits
        delay(40);
      }
    }
    if (max == trai) {
      Serial.print("Trai : "); Serial.println(trai); // Print ma ra serial
      for (int i = 0; i < amount; i++) { // goi ma lien tuc neu nhan duoc tin hieu
        irsend.sendRC5(0xa93, 12); // Goi tin hieu dinh dang RC5 co ma HEX 0xa93, 12 bits
        delay(40);
      }
    }
    readSoundSensor(); // doc lai tin hieu cuong do tu cam bien am thanh trong vong lap while() de dam bao viec doc tin hieu lien tuc
  }
  delay(10); // tri hoan vong lap
}
