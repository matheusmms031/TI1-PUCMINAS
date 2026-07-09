#include <Wire.h>

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

  randomSeed(analogRead(0));

  mostrarMenu();
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "1") {
      jogar1();
      mostrarMenu();
    }
    else if (comando == "2") {
      jogar2();
      mostrarMenu();
    }
    else if (comando == "3") {
      jogar3();
      mostrarMenu();
    }
    else {
      Serial.println("Opção inválida! Digite apenas o número: 1, 2 ou 3.");
    }
  }
}

void mostrarMenu() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);

  Serial.println();
  Serial.println("======= MENU DE JOGOS =======");
  Serial.println("Escolha um jogo:");
  Serial.println("Precisao (1), Reflexo (2) e Potenciometro (3).");
  Serial.println("-----------------------------");
  Serial.println("Digite apenas o numero correspondente e aperte Enter.");
}

void jogar1() {
  // Sorteia um tempo alvo entre 5 e 15 segundos
  long tempoAlvo = random(5, 16); 

  Serial.println("\n[Jogo 1: Precisão Iniciado!]");
  Serial.print("Seu alvo: ");
  Serial.print(tempoAlvo);
  Serial.println(" segundos.");
  Serial.println("PREPARE-SE... O LED vai acender e sua contagem mental começa!");
  delay(2000); // Pequena pausa para o jogador se preparar antes do LED acender

  // O LED acende e o seu tempo começa a contar AGORA
  digitalWrite(ledVermelho, HIGH);
  unsigned long tempoInicio = millis(); 

  Serial.println("\n>>> VALENDO! Conte mentalmente e aperte o botão! <<<");

  // Espera o jogador apertar o botão (enquanto isso a tela fica limpa para não dar spoiler)
  while (digitalRead(botao) == HIGH) {
  }

  unsigned long tempoFinal = millis();
  digitalWrite(ledVermelho, LOW); // Apaga o LED assim que aperta

  // Calcula exatamente quanto tempo você demorou na contagem mental
  float seuTempoMental = (tempoFinal - tempoInicio) / 1000.0;

  Serial.print("\nVocê apertou o botão em: ");
  Serial.print(seuTempoMental);
  Serial.println(" segundos.");

  // Calcula a diferença entre o seu tempo e o alvo sorteado
  float diferenca = abs(seuTempoMental - tempoAlvo);

  // Se a diferença for menor ou igual a 0.5 segundos, você ganha!
  if (diferenca <= 0.5) {
    Serial.println("===============================");
    Serial.println("  PARABÉNS! VOCÊ ACERTOU!!! :D ");
    Serial.println("===============================");
    // Pisca o LED azul para comemorar
    for(int i=0; i<5; i++){
      digitalWrite(ledAzul, HIGH); delay(100);
      digitalWrite(ledAzul, LOW);  delay(100);
    }
  } else {
    Serial.println("===============================");
    Serial.println("  VOCÊ ERROU! Tente de novo.   ");
    Serial.println("===============================");
    // Pisca o LED vermelho indicando erro
    for(int i=0; i<5; i++){
      digitalWrite(ledVermelho, HIGH); delay(100);
      digitalWrite(ledVermelho, LOW);  delay(100);
    }
  }

  delay(4000);
}

void jogar2() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);

  Serial.println("\n[Jogo 2: Reflexo - Aperte o botão!]");
  delay(2000);

  Serial.println("Prepare-se...");
  delay(random(1000, 3000));

  Serial.println("Prestando atenção...");

  digitalWrite(leds2[0], HIGH);
  delay(random(1000, 3000));

  digitalWrite(leds2[1], HIGH);
  delay(random(1000, 3000));

  digitalWrite(leds2[2], HIGH);
  unsigned long tempoInicial = millis();

  Serial.println("JÁ!!! GO!!!");

  while (digitalRead(botao) == HIGH) {
  }

  unsigned long tempoFinal = millis();
  unsigned long tempoReacao = tempoFinal - tempoInicial;

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);

  Serial.print("Tempo de Reação: ");
  Serial.print(tempoReacao);
  Serial.println(" ms");

  Serial.print("Jogo 2 finalizado. Tempo: ");
  Serial.print(tempoReacao);
  Serial.println(" ms");

  delay(4000);
}

void jogar3() {
  int alvo = random(0, 1024);
  int margem = 50;

  Serial.println("\n[Jogo 3: Potenciômetro Iniciado!]");
  Serial.print("Alvo: ");
  Serial.print(alvo);
  Serial.println(" - Gire o potenc.");

  unsigned long tempoInicio = millis();

  while (abs(analogRead(potenciometro) - alvo) > margem) {
  }

  unsigned long tempoFinal = millis();
  float tempoReacao = (tempoFinal - tempoInicio) / 1000.0;

  Serial.print("Acertou! Tempo: ");
  Serial.print(tempoReacao);
  Serial.println(" seg");

  Serial.print("Jogo 3 finalizado. Tempo: ");
  Serial.print(tempoReacao);
  Serial.println(" seg");

  delay(4000);
}
