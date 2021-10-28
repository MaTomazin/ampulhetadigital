/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels(12, 5, NEO_GRB + NEO_KHZ800);
int  EmJogo;
int  EmConfiguracao;
int  ModoJogo;
int  TempDeJogo;
int  BotaoMudaJogo;
int  TempoApertado;
int  BotaoSelecinonaComecaPara;
int  Sim;
int  Nao;
int  EstouContando;
int  Intervalo;
int  AUXTempoJogo;
int  ContarTempo;
void VerificaModoJogo() {
  if (TempoApertado + 3000 < (millis())) {
    if (ModoJogo == EmJogo) {
      ModoJogo = EmConfiguracao;

    } else {
      ModoJogo = EmJogo;

    }
    TempoApertado = (millis());
    delay(1000);

  }
}

void StartStop() {
  BotaoSelecinonaComecaPara = digitalRead(0);
  if (BotaoSelecinonaComecaPara == LOW) {
    if (EstouContando == Nao) {
      EstouContando = Sim;
      Serial.println("Contar");

    } else {
      EstouContando = Nao;
      Serial.println("Parar");

    }
    ContarTempo = TempDeJogo;
    delay(1000);

  }
}

void DefineTempodeJogo() {
  BotaoSelecinonaComecaPara = digitalRead(0);
  if (BotaoSelecinonaComecaPara == LOW) {
    AUXTempoJogo = AUXTempoJogo + 1;
    if (AUXTempoJogo > 4) {
      AUXTempoJogo = 1;

    }
    TempDeJogo = AUXTempoJogo * Intervalo;
    Serial.print("Tempo de Jogo ");
    Serial.println(TempDeJogo);
    delay(1000);

  }
}

void MarcandoOTempo() {
  if (ContarTempo == 0) {
    Serial.print("PERDEU!");
    EstouContando = Nao;

  }
  ContarTempo = ContarTempo - 1;
  Serial.print(ContarTempo);
}

void setup()
{
  pixels.begin();
EmJogo = 1;
EmConfiguracao = 2;
ModoJogo = EmJogo;
TempDeJogo = 30;
BotaoMudaJogo = HIGH;
TempoApertado = 0;
BotaoSelecinonaComecaPara = HIGH;
Sim = 0;
Nao = 1;
EstouContando = Nao;
Intervalo = 30;
AUXTempoJogo = 0;
ContarTempo = 1;
pinMode(4, INPUT_PULLUP);
Serial.begin(9600);

pinMode(0, INPUT_PULLUP);
}


void loop()
{

    pixels.fill(pixels.Color(51,102,255),0,7);
    pixels.show();
    BotaoMudaJogo = digitalRead(4);
    if (BotaoMudaJogo == LOW) {
      Serial.println("pressionado");
      VerificaModoJogo();

    } else {
      TempoApertado = 0;

    }
    if (ModoJogo == EmJogo) {
      Serial.println("Modo: Em Jogo");
      StartStop();

    } else {
      Serial.println("Modo: Em Configuração");
      DefineTempodeJogo();

    }
    if (ModoJogo == EmJogo && EstouContando == Sim) {
      MarcandoOTempo();

    }
    delay(1000);

}