/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/25
 * Description        : Main program body. (MODIFICADO PARA FADE EN PC4 USANDO PWM)
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "debug.h"

// Prototipos de funciones locales para organizar el código
void GPIO_Config_PWM(void);
void TIM1_PWM_Config(void);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    // Inicializaciones básicas del sistema
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    // 1. Configurar el pin PC4 para la salida PWM del Timer 1
    GPIO_Config_PWM();

    // 2. Configurar el Timer 1 para generar la señal PWM
    TIM1_PWM_Config();

    // Bucle infinito para el efecto de desvanecimiento (fade)
    while(1)
    {
        // Variable para controlar el brillo (ciclo de trabajo)
        uint16_t brightness;

        // Fade In: Aumentar el brillo gradualmente
        for (brightness = 0; brightness < 1000; brightness++)
        {
            // Actualizar el ciclo de trabajo del canal 4 del Timer 1
            TIM_SetCompare4(TIM1, brightness);
            Delay_Ms(2); // Pequeña pausa para controlar la velocidad del fade
        }

        // Fade Out: Disminuir el brillo gradualmente
        for (brightness = 1000; brightness > 0; brightness--)
        {
            // Actualizar el ciclo de trabajo del canal 4 del Timer 1
            TIM_SetCompare4(TIM1, brightness);
            Delay_Ms(2); // Pequeña pausa para controlar la velocidad del fade
        }
    }
}

/*********************************************************************
 * @fn      GPIO_Config_PWM
 *
 * @brief   Configura el pin PC4 como salida de función alternativa para PWM.
 *
 * @return  none
 */
void GPIO_Config_PWM(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Habilitar el reloj para el puerto C (GPIOC) y para las funciones alternativas (AFIO)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    // Configurar el pin PC4 como salida de función alternativa (controlado por el Timer)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     // Modo: Salida de Función Alternativa Push-Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      TIM1_PWM_Config
 *
 * @brief   Configura el Timer 1 para generar una señal PWM en el canal 4.
 *
 * @return  none
 */
void TIM1_PWM_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};

    // Habilitar el reloj para el Timer 1 (TIM1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* Configuración de la base de tiempos del Timer 1 */
    // SystemCoreClock = 48MHz
    // Frecuencia del Timer = 48,000,000 / (Prescaler + 1) = 48,000,000 / 48 = 1,000,000 Hz (1MHz)
    // Frecuencia PWM = Frecuencia del Timer / (Period + 1) = 1,000,000 / 1000 = 1000 Hz (1kHz)
    TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1;       // Prescaler para dividir el reloj
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;        // Período del contador (resolución de 1000 pasos)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // Modo de conteo ascendente
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Configuración del Canal 4 del Timer 1 en modo PWM */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // Modo PWM 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   // Habilitar la salida del canal
    TIM_OCInitStructure.TIM_Pulse = 0;                              // Ciclo de trabajo inicial (0% de brillo)
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       // Polaridad de la salida: Alta
    TIM_OC4Init(TIM1, &TIM_OCInitStructure); // Usar OC4Init para el Canal 4

    // Habilitar la precarga del registro de comparación del canal 4
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    // Habilitar la precarga del registro de auto-recarga del timer
    TIM_ARRPreloadConfig(TIM1, ENABLE);

    // Habilitar la salida principal del Timer 1 (necesario para timers avanzados como TIM1)
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    // Habilitar el contador del Timer 1 para que empiece a funcionar
    TIM_Cmd(TIM1, ENABLE);
}
