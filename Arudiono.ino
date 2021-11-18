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
int  TempoDeJogo;
int  BotaoMudaJogo;
int  TempoApertado;
int  BotaoSelecinonaComecaPara;
int  Sim;
int  Nao;
int  EstouContando;
int  Intervalo;
int  AUXTempoJogo;
int  ContarTempo;
int  MostrarNLed;
int  Futuro;
int  TempoAgora;
void VerificaModoJogo() {
  if (TempoApertado + 3000 < (millis())) {
    if (ModoJogo == EmJogo) {
      ModoJogo = EmConfiguracao;

    } else {
      ModoJogo = EmJogo;

    }
    TempoApertado = (millis());

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
    ContarTempo = TempoDeJogo;

  }
}

void DefineTempodeJogo() {
  BotaoSelecinonaComecaPara = digitalRead(0);
  if (BotaoSelecinonaComecaPara == LOW) {
    AUXTempoJogo = AUXTempoJogo + 1;
    if (AUXTempoJogo > 4) {
      AUXTempoJogo = 1;

    }
    TempoDeJogo = AUXTempoJogo * Intervalo;
    Serial.print("Tempo de Jogo ");
    Serial.println(TempoDeJogo);

  }
}

void MarcandoOTempo() {
  if (ContarTempo == 0) {
    Serial.print("PERDEU!");
    EstouContando = Nao;
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
       for(int i=0; i<pixels.numPixels(); i++) {
       int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
       pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();
    delay(10);
    }

  }
  Serial.println("------");
  Serial.print(ContarTempo);
  Serial.print(" - Mapeia ");
  MostrarNLed = map(ContarTempo, 0, TempoDeJogo-1, 0, 8);
  Serial.println(MostrarNLed);
  Serial.println("");
  pixels.clear();
  if (MostrarNLed != 0) {
    pixels.fill(pixels.Color(51,102,255),0,MostrarNLed);
    pixels.show();

  } else {
    pixels.fill(pixels.Color(0,0,0),0,7);
    pixels.show();

  }
}

void setup()
{
  pixels.begin();
EmJogo = 1;
EmConfiguracao = 2;
ModoJogo = EmJogo;
TempoDeJogo = 30;
BotaoMudaJogo = HIGH;
TempoApertado = 0;
BotaoSelecinonaComecaPara = HIGH;
Sim = 0;
Nao = 1;
EstouContando = Nao;
Intervalo = 30;
AUXTempoJogo = 0;
ContarTempo = 1;
MostrarNLed = 0;
Futuro = 0;
TempoAgora = (millis());
pinMode(4, INPUT);
Serial.begin(9600);
  pixels.setBrightness(25);

pinMode(0, INPUT);
}


void loop()
{

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
    TempoAgora = (millis());
    if (TempoAgora > Futuro) {
      Serial.print("Passou 1 segundo");
      Futuro = TempoAgora + 1000;
      if (EstouContando == Sim) {
        ContarTempo = ContarTempo - 1;

      }

    }

}
