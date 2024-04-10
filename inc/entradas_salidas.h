/*
 * Copyright (c) 2024 Jesus Gonzales jesus.e.1997.eg@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : entradas_salidas.h
 * @date   : 22/03/2024
 * @author : Jesus Gonzales
 * @version	v1.0.0
 */

#ifndef ENTRADAS_SALIDAS_ENTRADAS_SALIDAS_H
#define ENTRADAS_SALIDAS_ENTRADAS_SALIDAS_H

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include "stdlib.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/
typedef uint8_t uint;
/**
 * @brief   Puerto del microcontrolador
 */
typedef struct {
    uint gpio;
    bool type;
} puertoIO_t;
/**
 * @brief   Estados del pulsador
 */
typedef enum { INPUT_UP, INPUT_FALLING, INPUT_DOWN, INPUT_RAISING } debounceState_t;
/**
 * @brief   Maquina de estados
 */
typedef struct {
    debounceState_t estado;       // Estado en el que se encuentra la señal de entrada
    puertoIO_t * puertoEntrada;   // Puerto de entrada enlazado a la maquina de estados
    uint32_t ultimoTiempoLectura; // Almacena el tiempo de lectura extraido del systick
    uint32_t tiempoAntirebote;    // Almacena el tiempo de espera del antirebote para considerar la
                                  // señal como válida
    uint32_t contador;            // Contador de positivos
    uint32_t ultimoTiempoConsultaRPM; // Almacena el tiempo de consulta de las RPM
} maqEstados_entrada_t;
/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/
/**
 * @brief   Inicializalización de las GPIO
 *
 * @param pines_a_iniciar Dirección a los pines a inicializar
 * @param numGPIO Numero de pines a inicializar
 */
bool iniciacion_gpio(const puertoIO_t * pines_a_iniciar, uint8_t numGPIO);
/**
 * @brief   Inicializalización de maquina de estados de entrada
 *
 * @param maquina_a_iniciar Maquina de estados asociada
 * @param puerto_de_lectura Puerto de lectura de la maquina
 * @param tiempoAntirebote Tiempo de antirebote de la maquina en ms
 * @return Valor de la maquina de estados luego de inicializarse
 */
debounceState_t initMaqPulsador(maqEstados_entrada_t * maquina_a_iniciar,
                                puertoIO_t * puerto_de_lectura, uint32_t tiempoAntirebote);
/**
 * @brief   Consulta el estado actual de la maquina de estados
 *
 * @param maquina_a_iniciar Maquina de estados asociada
 * @return valor de maquina de estados
 */
debounceState_t consultaMaq(maqEstados_entrada_t * maquina_a_consultar);
/**
 * @brief   Consulta las RPM cada 1 seg
 *
 * @param maquina_a_iniciar Maquina de estados asociada
 * @return numero de RPM
 */
uint32_t consulta_RPM(maqEstados_entrada_t * maquina_a_consultar);
/********************** function declaration ***********************/
/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /*ENTRADAS_SALIDAS_ENTRADAS_SALIDAS_H*/
/********************** end of file ******************************************/
