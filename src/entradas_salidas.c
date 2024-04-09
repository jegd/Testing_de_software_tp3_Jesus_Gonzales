/*
 * @file: entradas_salidas.c
 *
 *@brief Modulo de control de salidas y entradas
 *@Created on: 22 mar. 2024
 *@ Author: Jesus Gonzales
 *@ Mail: jesus.e.1997.eg@gmail.com || jesus.e_97@hotmail.com
 */
/************************INCLUDES************************/
#include "entradas_salidas.h"
/************************MACROS************************/
#define TIEMPO_REFRESCO_RPM  1000000 // Tiempo de refresco en us de la encuesta de RPM
#define CONVERSION_SEG_A_MIN 60      // Factor para convertir de rev/s a rev/min
#define NUMERO_DE_ALETAS_VENTILADOR                                                                \
    8 // Numero de aletas sensadas por el inductivo equivalente a 1 vuelta completa
/************************PROTOTIPOS FUNCIONES GLOBALES************************/
static uint32_t RPM;
/************************PROTOTIPOS FUNCIONES PRIVADAS************************/
/************************VARIABLES PUBLICAS************************/
/************************VARIABLES PRIVADAS************************/
uint32_t consulta_RPM(maqEstados_entrada_t * maquina_a_consultar) {
    if (time_us_32() - maquina_a_consultar->ultimoTiempoConsultaRPM > TIEMPO_REFRESCO_RPM) {
        maquina_a_consultar->ultimoTiempoConsultaRPM = time_us_32();
        RPM =
            ((maquina_a_consultar->contador) * CONVERSION_SEG_A_MIN) / NUMERO_DE_ALETAS_VENTILADOR;
        maquina_a_consultar->contador = 0;
        printf("Las RPM son: %d \n\r", RPM);
        lectura_ADC(27);
    }
    return RPM;
}
void iniciacion_gpio(const puertoIO_t * pines_a_iniciar, uint8_t numGPIO) {
    puertoIO_t * direcc_vector = (puertoIO_t *)pines_a_iniciar;
    for (int i = 0; i < numGPIO; i++) {
        gpio_init(direcc_vector->gpio);
        gpio_set_dir(direcc_vector->gpio, direcc_vector->type);
        direcc_vector++;
    }
}
debounceState_t initMaqPulsador(maqEstados_entrada_t * maquina_a_iniciar,
                                puertoIO_t * puerto_de_lectura, uint32_t tiempoAntirebote) {
    maquina_a_iniciar->puertoEntrada = puerto_de_lectura;
    maquina_a_iniciar->estado = INPUT_DOWN;
    maquina_a_iniciar->tiempoAntirebote = tiempoAntirebote;
    maquina_a_iniciar->ultimoTiempoLectura = 0;
    maquina_a_iniciar->contador = 0;
    maquina_a_iniciar->ultimoTiempoConsultaRPM = 0;
    printf("La maquina de estados se inicializo: %d \n\r", maquina_a_iniciar->estado);
}
debounceState_t consultaMaq(maqEstados_entrada_t * maquina_a_consultar) {
    assert(&maquina_a_consultar != NULL);
    switch (maquina_a_consultar->estado) {
    case INPUT_UP:
        if (!(gpio_get(maquina_a_consultar->puertoEntrada->gpio))) {
            maquina_a_consultar->estado = INPUT_FALLING;
            maquina_a_consultar->ultimoTiempoLectura = time_us_32();
        }
        break;
    case INPUT_FALLING:
        if (!(gpio_get(maquina_a_consultar->puertoEntrada->gpio)) &&
            (time_us_32() - maquina_a_consultar->ultimoTiempoLectura) >
                maquina_a_consultar->tiempoAntirebote)
            maquina_a_consultar->estado = INPUT_DOWN;
        else
            maquina_a_consultar->estado = INPUT_UP;
        break;
    case INPUT_DOWN:
        if (gpio_get(maquina_a_consultar->puertoEntrada->gpio)) {
            maquina_a_consultar->estado = INPUT_RAISING;
            maquina_a_consultar->ultimoTiempoLectura = time_us_32();
        }
        break;
    case INPUT_RAISING:
        if ((gpio_get(maquina_a_consultar->puertoEntrada->gpio)) &&
            (time_us_32() - maquina_a_consultar->ultimoTiempoLectura) >
                maquina_a_consultar->tiempoAntirebote) {
            maquina_a_consultar->estado = INPUT_UP;
            maquina_a_consultar->contador++;
        } else
            maquina_a_consultar->estado = INPUT_DOWN;
        break;

    default:
        maquina_a_consultar->estado = INPUT_DOWN;
        break;
    }
}
/************************FUNCIONES PUBLICAS************************/

/************************FUNCIONES PRIVADAS************************/
