
#include "unity.h"
#include <stdbool.h>
#include "entradas_salidas.h"
#include "mock_stdlib.h"

#define ANTIREBOTE 20U
maqEstados_entrada_t maquina_pruebas;
puertoIO_t * puerto_pruebas;
debounceState_t estado_pruebas;
uint8_t numero_de_gpio;

uint auxiliar_gpio_init(uint gpio) {
    return 1;
}

uint32_t auxiliar_time_us_32() {
    return 2;
}
// Probar que inicializan bien las gpio
// Probar que se inicializa en estado down la maquina de estado
// Probar si se manda un valor ramdom a inicio de gpio y maquina de estado
// test_maquina_de_estado_inicializa_en_estado_DOWN
// Se consulta la máquina de estado para conocer en qué estado se encuentra
// Se consultan las RPM del sensado
void test_inicio_adecuado_de_gpio(void) {
    numero_de_gpio = 5;
    TEST_ASSERT_EQUAL_UINT16(1, iniciacion_gpio(&puerto_pruebas, numero_de_gpio));
}
