
int segmento[8] = {PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7};

// funcion para asignar HIGH o LOW a cada segmento (HIGH = 1 Y LOW = 0  y como es anodo comun el HIGH apaga el segmento y el LOW lo enciende)


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


const int configuraciones[38][8] = {
   
  {0, 0, 0, 0, 0, 0, 1, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0, 1}, // 2
  {0, 0, 0, 0, 1, 1, 0, 1}, // 3
  {1, 0, 0, 1, 1, 0, 0, 1}, // 4
  {0, 1, 0, 0, 1, 0, 0, 1}, // 5
  {0, 1, 0, 0, 0, 0, 0, 1}, // 6
  {0, 0, 0, 1, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0, 1}, // 8
  {0, 0, 0, 0, 1, 0, 0, 1}, // 9
  {1, 1, 1, 1, 1, 1, 1, 0}, //10 .
  {0, 0, 0, 1, 0, 0, 0, 1}, //11 A
  {1, 1, 0, 0, 0, 0, 0, 1}, //12 b
  {1, 1, 1, 0, 0, 1, 0, 1}, //13 c
  {1, 0, 0, 0, 0, 1, 0, 1}, //14 d
  {0, 1, 1, 0, 0, 0, 0, 1}, //15 E
  {0, 1, 1, 1, 0, 0, 0, 1}, //16 F
  {0, 1, 0, 0, 0, 0, 0, 1}, //17 G
  {1, 0, 0, 1, 0, 0, 0, 1}, //18 H
  {1, 1, 1, 1, 0, 0, 1, 1}, //19 I
  {1, 0, 0, 0, 1, 1, 1, 1}, //20 J
  {1, 0, 1, 1, 0, 0, 0, 1}, //21 k
  {1, 1, 1, 0, 0, 0, 1, 1}, //22 L
  {0, 0, 0, 1, 0, 0, 1, 1}, //23 M
  {1, 1, 0, 1, 0, 1, 0, 1}, //24 n
  {0, 1, 0, 1, 0, 1, 0, 1}, //25 ñ
  {1, 1, 0, 0, 0, 1, 0, 1}, //26 o
  {0, 0, 1, 1, 0, 0, 0, 1}, //27 P
  {0, 0, 0, 1, 1, 0, 0, 1}, //28 q
  {1, 1, 1, 1, 0, 1, 0, 1}, //29 r
  {0, 1, 0, 0, 1, 0, 0, 1}, //30 s
  {0, 1, 1, 1, 0, 0, 1, 1}, //31 t
  {1, 1, 0, 0, 0, 1, 1, 1}, //32 u
  {1, 0, 0, 0, 0, 0, 1, 1}, //33 V
  {1, 0, 0, 0, 0, 0, 1, 1}, //34 W
  {1, 0, 0, 1, 0, 0, 0, 1}, //35 X
  {1, 0, 0, 0, 1, 0, 0, 1}, //36 Y
  {0, 0, 1, 0, 0, 1, 0, 1} //37 Z
};



void mostrarNumero(int numero) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmento[i], configuraciones[numero][i]);
  }
}

void loop() {



//descomentar el for para mostrar todos los numeros de a uno
 for (int i = 0; i < 38; i++) {
    mostrarNumero(i);
    delay(500);
  }


//mostrarNumero(5);
//delay(500);

}

