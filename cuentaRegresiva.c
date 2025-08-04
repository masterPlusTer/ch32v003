#include "debug.h"

// Definición de pines para cada segmento del display (nueva configuración)
#define SEG_A  GPIO_Pin_0  // PC0
#define SEG_B  GPIO_Pin_1  // PC1
#define SEG_C  GPIO_Pin_2  // PC2
#define SEG_D  GPIO_Pin_3  // PC3
#define SEG_E  GPIO_Pin_4  // PC4
#define SEG_F  GPIO_Pin_5  // PC5
#define SEG_G  GPIO_Pin_6  // PC6

// Configuración de los números en el display (1 = encendido, 0 = apagado)
const uint8_t digitos[10] = {
    // ABCDEFG  (nuevo orden de segmentos)
    0b0000001, // 0
    0b1001111, // 1
    0b0010010, // 2
    0b0000110, // 3
    0b1001100, // 4
    0b0100100, // 5
    0b0100000, // 6
    0b0001111, // 7
    0b0000000, // 8
    0b0001100  // 9
};

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Habilitar reloj para el puerto C
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Configurar todos los pines de segmentos como salidas push-pull
    GPIO_InitStructure.GPIO_Pin = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void mostrarDigito(uint8_t numero) {
    // Verificar que el número esté entre 0-9
    if(numero > 9) return;

    // Obtener el patrón de bits para este dígito
    uint8_t patron = digitos[numero];

    // Controlar cada segmento según el nuevo patrón
    GPIO_WriteBit(GPIOC, SEG_A, (patron & 0b1000000) ? Bit_SET : Bit_RESET); // A (MSB)
    GPIO_WriteBit(GPIOC, SEG_B, (patron & 0b0100000) ? Bit_SET : Bit_RESET); // B
    GPIO_WriteBit(GPIOC, SEG_C, (patron & 0b0010000) ? Bit_SET : Bit_RESET); // C
    GPIO_WriteBit(GPIOC, SEG_D, (patron & 0b0001000) ? Bit_SET : Bit_RESET); // D
    GPIO_WriteBit(GPIOC, SEG_E, (patron & 0b0000100) ? Bit_SET : Bit_RESET); // E
    GPIO_WriteBit(GPIOC, SEG_F, (patron & 0b0000010) ? Bit_SET : Bit_RESET); // F
    GPIO_WriteBit(GPIOC, SEG_G, (patron & 0b0000001) ? Bit_SET : Bit_RESET); // G (LSB)
}

int main(void) {
    // Inicializaciones básicas
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    // Configurar GPIOs para el display
    GPIO_Config();

    // Cuenta regresiva del 9 al 0
    while(1) {
        for(int i = 9; i >= 0; i--) {
            mostrarDigito(i);  // Mostrar el dígito actual
            Delay_Ms(1000);    // Esperar 1 segundo

            // Parpadeo al llegar a cero
            if(i == 0) {
                for(int j = 0; j < 3; j++) {
                    mostrarDigito(0);
                    Delay_Ms(200);
                    // Apagar todos los segmentos
                    GPIO_ResetBits(GPIOC, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G);
                    Delay_Ms(200);
                }
            }
        }
    }
}
