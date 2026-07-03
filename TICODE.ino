#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define col 16
#define lin 2
#define ende 0x20
LiquidCrystal_I2C lcd(ende, col, lin);

const int ledVermelho = 2;
const int ledAmarelo  = 3;
const int ledAzul     = 4;
const int botao       = 5;
const int potenciometro = A1;

int leds2[3] = {ledVermelho, ledAmarelo, ledAzul};

void setup() {
  Serial.begin(9600);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(botao, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(0));

  mostrarMenu();
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toLowerCase();

    if (comando == "jogo 1") {
      jogar1();
      mostrarMenu();
    }
    else if (comando == "jogo 2") {
      jogar2();
      mostrarMenu();
    }
    else if (comando == "jogo 3") {
      jogar3();
      mostrarMenu();
    }
    else {
      Serial.println("Comando invalido. Digite: jogo 1, jogo 2 ou jogo 3");
    }
  }
}

void mostrarMenu() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Escolha um jogo");
  lcd.setCursor(0, 1);
  lcd.print("no Serial");

  Serial.println();
  Serial.println("=== MENU ===");
  Serial.println("Digite 'jogo 1', 'jogo 2' ou 'jogo 3' e aperte Enter");
}

void jogar1() {
  long tempoEspera = random(3, 20);
  int segundos = 0;

  Serial.println("Jogo 1 iniciado!");

  while (segundos < tempoEspera) {
    segundos++;
    lcd.setCursor(0, 0);
    lcd.print("Tempo:          ");
    lcd.setCursor(0, 1);
    lcd.print(segundos);
    lcd.print(" seg    ");
    delay(1000);
  }

  digitalWrite(ledVermelho, HIGH);
  unsigned long tempoInicio = millis();

  while (digitalRead(botao) == HIGH) {
  }

  unsigned long tempoFinal = millis();
  digitalWrite(ledVermelho, LOW);

  float tempoReacao = (tempoFinal - tempoInicio) / 1000.0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tempo Final:");
  lcd.setCursor(0, 1);
  lcd.print(tempoReacao);
  lcd.print(" seg");

  Serial.print("Jogo 1 finalizado. Tempo: ");
  Serial.print(tempoReacao);
  Serial.println(" seg");

  delay(4000);
}

void jogar2() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jogo de Reacao");
  lcd.setCursor(0, 1);
  lcd.print("Aperte o botao!");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Prepare-se...");
  delay(random(1000, 3000));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Prestando atencao");

  digitalWrite(leds2[0], HIGH);
  delay(random(1000, 3000));

  digitalWrite(leds2[1], HIGH);
  delay(random(1000, 3000));

  digitalWrite(leds2[2], HIGH);
  unsigned long tempoInicial = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JA!!! GO!!!");

  while (digitalRead(botao) == HIGH) {
  }

  unsigned long tempoFinal = millis();
  unsigned long tempoReacao = tempoFinal - tempoInicial;

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tempo de Reacao:");
  lcd.setCursor(0, 1);
  lcd.print(tempoReacao);
  lcd.print(" ms");

  Serial.print("Jogo 2 finalizado. Tempo: ");
  Serial.print(tempoReacao);
  Serial.println(" ms");

  delay(4000);
}

void jogar3() {
  int alvo = random(0, 1024);
  int margem = 50;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alvo:");
  lcd.print(alvo);
  lcd.setCursor(0, 1);
  lcd.print("Gire o potenc.");

  Serial.println("Jogo 3 iniciado!");

  unsigned long tempoInicio = millis();

  while (abs(analogRead(potenciometro) - alvo) > margem) {
  }

  unsigned long tempoFinal = millis();
  float tempoReacao = (tempoFinal - tempoInicio) / 1000.0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acertou!");
  lcd.setCursor(0, 1);
  lcd.print(tempoReacao);
  lcd.print(" seg");

  Serial.print("Jogo 3 finalizado. Tempo: ");
  Serial.print(tempoReacao);
  Serial.println(" seg");

  delay(4000);
}