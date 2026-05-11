#include "HUSKYLENS.h"
#include "Wire.h"

// --- Esp32'nin Pin Tanımlamaları ---
#define MIC_PIN 34      
#define LED_PIN 25      
#define SDA_PIN 32      
#define SCL_PIN 33      
#define MOTOR_AIN1 18
#define MOTOR_AIN2 19
#define MOTOR_SLEEP 22

const int MIYAV_THRESHOLD = 2000; 
bool kapiAcik mi = false; // Kapının durumunu takip etmek için

HUSKYLENS huskylens;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    
    pinMode(MIC_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(MOTOR_AIN1, OUTPUT);
    pinMode(MOTOR_AIN2, OUTPUT);
    pinMode(MOTOR_SLEEP, OUTPUT);

    kapiyiKilitle(); // Başlangıçta motoru kapat ve uykula
    
    while (!huskylens.begin(Wire)) {
        Serial.println("HuskyLens bekleniyor...");
        delay(1000);
    }
}

// --- Motor Fonksiyonları (Kodun okunabilirliği için) ---
void kapiyiAc() {
    digitalWrite(MOTOR_SLEEP, HIGH);
    digitalWrite(MOTOR_AIN1, HIGH);
    digitalWrite(MOTOR_AIN2, LOW);
    delay(2000); // Kapının tamamen açılması için gereken süre (Ayarlanabilir)
    motoruDurdur();
}

void kapiyiKapat() {
    digitalWrite(MOTOR_SLEEP, HIGH);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH);
    delay(2000); // Kapının tamamen kapanması için gereken süre
    kapiyiKilitle();
}

void motoruDurdur() {
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, LOW);
}

void kapiyiKilitle() {
    motoruDurdur();
    digitalWrite(MOTOR_SLEEP, LOW);
}

void loop() {
    // 1. Sensör Verileri
    int sesSeviyesi = analogRead(MIC_PIN);
    bool kediEsikte = false;

    if (huskylens.request()) {
        while (huskylens.available()) {
            HUSKYLENS_Result result = huskylens.read();
            if (result.ID == 1) kediEsikte = true;
        }
    }

    // 2. Senaryo Yönetimi
    if (!kapiAcikmi) {
        // KAPI KAPALI: Miyavlama bekliyoruz
        if (sesSeviyesi > MIYAV_THRESHOLD) {
            Serial.println("Miyav algılandı! Kapı açılıyor...");
            kapiyiAc();
            kapiAcikmi = true;
        }
    } 
    else {
        // KAPI AÇIK: Kedinin geçmesini ve eşikten ayrılmasını bekliyoruz
        digitalWrite(LED_PIN, kediEsikte ? HIGH : LOW); // Kedi eşikteyse LED yansın

        if (kediEsikte) {
            Serial.println("Kedi hala eşikte, kapanma bekletiliyor...");
            // Kedi eşikteyken hiçbir şey yapma, bekle.
        } 
        else {
            // Eşik boşaldı! 3 saniye daha bekle (garanti olsun) ve kapat
            Serial.println("Eşik boş. 3 saniye sonra kapanıyor...");
            delay(3000); 
            kapiyiKapat();
            kapiAcikmi = false;
        }
    }

    delay(100);
}
