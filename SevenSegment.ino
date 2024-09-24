
int segmento[8] = {PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7};

// funcion para asignar HIGH o LOW a cada segmento (HIGH = 1 Y LOW = 0  y como es catodo comun el HIGH apaga el segmento y el LOW lo enciende)


void SEGMENTO(int A, int B, int C, int D, int E, int F, int G, int H) {
  int valores[] = {A, B, C, D, E, F, G, H};


  for (int i = 0; i < 8; i++) {
    digitalWrite(segmento[i], valores[i]);
  }
}


void setup() {

// configurar los pines como OUTPUT, como son muchos se pueden configurar en bucle para no repetir codigo.

  for (int i = 0; i < 8; i++) {
    pinMode(segmento[i], OUTPUT);
  }

  Serial.begin(9600);
}


const int segmentos[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Ajusta los números según tus pines
const int configuraciones[10][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0, 1}, // 2
  {0, 0, 0, 0, 1, 1, 0, 1}, // 3
  {1, 0, 0, 1, 1, 0, 0, 1}, // 4
  {0, 1, 0, 0, 1, 0, 0, 1}, // 5
  {0, 1, 0, 0, 0, 0, 0, 1}, // 6
  {0, 0, 0, 1, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0, 1}, // 8
  {0, 0, 0, 0, 1, 0, 0, 1}  // 9
};



void mostrarNumero(int numero) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentos[i], configuraciones[numero][i]);
  }
}

void loop() {

      //descomentar para mostrar todos los numeros uno por uno

 // for (int i = 0; i < 10; i++) {
  //  mostrarNumero(i);
 // }




mostrarNumero(7);

    delay(500);

}




//+Ter




//+Ter


