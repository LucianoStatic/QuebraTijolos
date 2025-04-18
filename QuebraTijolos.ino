#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGURA_TELA 128
#define ALTURA_TELA 64
#define RESET_OLED -1
Adafruit_SSD1306 tela(LARGURA_TELA, ALTURA_TELA, &Wire, RESET_OLED);

// Joystick e Buzzer
#define EIXO_X A0
#define BUZZER 3

// Raquete
int posicaoRaqueteX = 64;
const int larguraRaquete = 20;
const int alturaRaquete = 3;
const int posicaoRaqueteY = ALTURA_TELA - 5;

// Bola
float posicaoBolaX = 64;
float posicaoBolaY = 32;
float velocidadeBolaX = 3.5;
float velocidadeBolaY = -3.5;
const int tamanhoBola = 2;

// Tijolos
const int colunas = 8;
const int linhas = 2;
const int larguraTijolo = 14;
const int alturaTijolo = 5;
bool tijolos[linhas][colunas];

// Pontuação
int pontuacao = 0;

void setup() {
  tela.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(BUZZER, OUTPUT);

  // Inicializa os tijolos
  for (int l = 0; l < linhas; l++) {
    for (int c = 0; c < colunas; c++) {
      tijolos[l][c] = true;
    }
  }

  tela.clearDisplay();
  Serial.begin(9600);
}

void loop() {
  // === MOVIMENTO DA RAQUETE COM SUAVIDADE ===
  int leituraX = analogRead(EIXO_X);
  int centro = 512;
  int zonaMorta = 100;
  int sensibilidade = 6;

  if (leituraX < centro - zonaMorta) {
    posicaoRaqueteX -= sensibilidade;
  }
  if (leituraX > centro + zonaMorta) {
    posicaoRaqueteX += sensibilidade;
  }

  if (posicaoRaqueteX < 0) posicaoRaqueteX = 0;
  if (posicaoRaqueteX > LARGURA_TELA - larguraRaquete) posicaoRaqueteX = LARGURA_TELA - larguraRaquete;

  // === MOVIMENTO DA BOLA ===
  float incremento = pontuacao * 0.05;

  posicaoBolaX += (velocidadeBolaX > 0 ? velocidadeBolaX + incremento : velocidadeBolaX - incremento);
  posicaoBolaY += (velocidadeBolaY > 0 ? velocidadeBolaY + incremento : velocidadeBolaY - incremento);

  // === COLISÃO COM PAREDES ===
  if (posicaoBolaX <= 0 || posicaoBolaX >= LARGURA_TELA - tamanhoBola) {
    velocidadeBolaX = -velocidadeBolaX;
    tone(BUZZER, 400, 40);
  }
  if (posicaoBolaY <= 0) {
    velocidadeBolaY = -velocidadeBolaY;
    tone(BUZZER, 500, 40);
  }

  // === COLISÃO COM A RAQUETE ===
  if (posicaoBolaY + tamanhoBola >= posicaoRaqueteY &&
      posicaoBolaX + tamanhoBola >= posicaoRaqueteX &&
      posicaoBolaX <= posicaoRaqueteX + larguraRaquete) {
    velocidadeBolaY = -velocidadeBolaY;
    tone(BUZZER, 800, 50);
  }

  // === COLISÃO COM TIJOLOS ===
  for (int l = 0; l < linhas; l++) {
    for (int c = 0; c < colunas; c++) {
      if (tijolos[l][c]) {
        int tijoloX = c * larguraTijolo;
        int tijoloY = l * alturaTijolo + 10;
        if (posicaoBolaX + tamanhoBola >= tijoloX && posicaoBolaX <= tijoloX + larguraTijolo &&
            posicaoBolaY + tamanhoBola >= tijoloY && posicaoBolaY <= tijoloY + alturaTijolo) {
          tijolos[l][c] = false;
          velocidadeBolaY = -velocidadeBolaY;
          pontuacao++;
          tone(BUZZER, 1000, 60);
        }
      }
    }
  }

  // === GAME OVER ===
  if (posicaoBolaY > ALTURA_TELA) {
    tela.clearDisplay();
    tela.setCursor(30, 30);
    tela.setTextSize(1);
    tela.setTextColor(SSD1306_WHITE);
    tela.print("PERDEU!");
    tela.display();
    tone(BUZZER, 200, 500);
    delay(2000);

    // Reset
    posicaoBolaX = 64;
    posicaoBolaY = 32;
    velocidadeBolaX = 3.5;
    velocidadeBolaY = -3.5;
    pontuacao = 0;
    for (int l = 0; l < linhas; l++) {
      for (int c = 0; c < colunas; c++) {
        tijolos[l][c] = true;
      }
    }
  }

  // === DESENHO NA TELA ===
  tela.clearDisplay();

  // Raquete
  tela.fillRect(posicaoRaqueteX, posicaoRaqueteY, larguraRaquete, alturaRaquete, SSD1306_WHITE);

  // Bola
  tela.fillCircle(posicaoBolaX, posicaoBolaY, tamanhoBola, SSD1306_WHITE);

  // Tijolos
  for (int l = 0; l < linhas; l++) {
    for (int c = 0; c < colunas; c++) {
      if (tijolos[l][c]) {
        tela.fillRect(c * larguraTijolo, l * alturaTijolo + 10, larguraTijolo - 1, alturaTijolo - 1, SSD1306_WHITE);
      }
    }
  }

  // Pontuação
  tela.setCursor(0, 0);
  tela.setTextSize(1);
  tela.setTextColor(SSD1306_WHITE);
  tela.print("Pontos: ");
  tela.print(pontuacao);

  tela.display();
  delay(20); // mantém fluidez
}
