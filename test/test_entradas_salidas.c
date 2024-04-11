
#include "unity.h"
#include <stdbool.h>
#include "entradas_salidas.h"
#include "Mockstdlib.h"
#define ANTIREBOTE 20U
maqEstados_entrada_t maquina_pruebas;
puertoIO_t * puerto_pruebas;
debounceState_t estado_pruebas;
uint8_t numero_de_gpio;

// Probar que inicializan bien las gpio
// Probar que se inicializa en estado down la maquina de estado
// Probar si se manda un valor ramdom a inicio de gpio y maquina de estado
// test_maquina_de_estado_inicializa_en_estado_DOWN
// Se consulta la máquina de estado para conocer en qué estado se encuentra
// Se consultan las RPM del sensado

void test_inicio_adecuado_de_gpio(void) {
    numero_de_gpio = 5;
    time_us_32_CMockExpectAndReturn(-1, 1);
    numero_de_gpio = time_us_32();
    TEST_ASSERT_EQUAL_UINT16(1, numero_de_gpio);
}
