#include <Arduino.h>

const int escPin = 3;

void sendPrecisionPulse(int us) {
  noInterrupts();
  digitalWrite(escPin, HIGH);
  delayMicroseconds(us);
  digitalWrite(escPin, LOW);
  interrupts();
  delayMicroseconds(20000 - us);
}

void setup() {
  pinMode(escPin, OUTPUT);

  // 【最重要】電源ONと同時に「最高速(2000us)」を3秒間送り、ESCを学習モードにする
  // ※この3秒の間に安定化電源をONにしてください
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    sendPrecisionPulse(2000); 
  }

  // 【最重要】次に「ニュートラル(1500us)」を4秒間送り、上限と下限を記憶させる
  // ここで確定音が鳴り、1Aのリミッターが外れます
  startTime = millis();
  while (millis() - startTime < 4000) {
    sendPrecisionPulse(1500); 
  }
}

void loop() {
  // リミッター解除後のフルパワーテスト（2000us固定）
  sendPrecisionPulse(1350);
  // int kick_request = 1;
  // if(kick_request == 1){
  //   kick_request = kick.shoot(); 
  // }
}