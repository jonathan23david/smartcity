

const int pinTrigger = 2;
const int pinEcho = 3;

int d1, d2;
double v;
int activo;

int t = 500;
int anteriorDistancia;
int anteriorVelocidad;


LedControl lc = LedControl(11, 13, 10, 1);  // LedControl (DIN, CLK, CS, NDispositivos (1 a 8) )

byte numeros[10][5][3] = {
  { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 } },
  { { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } },
  { { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 } },
  { { 1, 1, 1 }, { 0, 0, 1 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 } },
  { { 1, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 0, 1 }, { 0, 0, 1 } },
  { { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 } },
  { { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } },
  { { 1, 1, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } },
  { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } },
  { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 0, 1 }, { 0, 0, 1 } }
};

void setup() {
  // inicializar el led:
  lc.shutdown(0, false);  //apaga todos los leds del dispositivo 0
  lc.setIntensity(0, 2);  //intensidad de la luz de 0 a 15
  lc.clearDisplay(0);     //
  Serial.begin(9600);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(pinTrigger, LOW);

  for (int nn = 3; nn >= 0; nn--) {
    mostrarNumero(nn);
    delay(1000);
  }
}

void loop() {

  d1 = Sonar();
  Serial.print("Distancia 1:");
  Serial.println(d1);
  if (d1 < 100) {
    
    delay(t);
    d2 = Sonar();
    Serial.print("Distancia 2:");
    Serial.println(d2);

    v = 1000 * (d1 - d2) / t;
    Serial.print("Velocidad:");
    Serial.println(v);

    mostrarNumero(v);
    if (v > 0) {
      delay(1000);
    }
  } else {
    lc.clearDisplay(0);
    lc.setLed(0,3,3,!activo);
    lc.setLed(0,4,4,!activo);
    delay(200);  
  }
}

int Sonar() {
  int time;
  int dist;

  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  time = pulseIn(pinEcho, HIGH);
  dist = time / 59;
  return dist;
}

void mostrarNumero(int n) {
  int d1, d2;
  d1 = n / 10;
  d2 = n % 10;
  lc.clearDisplay(0);
  for (int fila = 2; fila < 7; fila++) {
    for (int columna = 1; columna < 8; columna++) {
      //Evalua primer Digito

      if ((columna > 0) && (columna < 4)) {
        lc.setLed(0, fila, columna, numeros[d1][fila - 2][columna - 1]);
      } else if ((columna > 4) && (columna <= 7)) {
        lc.setLed(0, fila, columna, numeros[d2][fila - 2][columna - 5]);
      }
    }
  }
}