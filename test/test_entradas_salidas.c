
#include "unity.h"
#include <stdbool.h>
#include "entradas_salidas.h"
#include "Mockstdlib.h"
#include <assert.h>
#define ANTIREBOTE    20U
#define PIN_LECTURA   5U
#define PIN_LECTURA_2 6U
#define PIN_LECTURA_3 2U
#define INPUT         0U
#define OUTPUT        1U

maqEstados_entrada_t maquina_pruebas;
puertoIO_t puerto_pruebas[] = {{.gpio = PIN_LECTURA, .type = INPUT},
                               {.gpio = PIN_LECTURA_2, .type = INPUT},
                               {.gpio = PIN_LECTURA_3, .type = INPUT}};
debounceState_t estado_pruebas;
uint8_t numero_de_gpio;

// Probar que inicializan adecuada de las gpio
// Probar que se inicializa en estado down la maquina de estado
// Probar si se manda un valor ramdom a inicio de gpio y maquina de estado
// test_maquina_de_estado_inicializa_en_estado_DOWN
// Se consulta la máquina de estado para conocer en qué estado se encuentra
// Se consultan las RPM del sensado

// Evaluando valores validos para los gpio
void test_valores_de_array_puertos_esperados(void) {
    puertoIO_t * puerto_test = (puertoIO_t *)puerto_pruebas;
    for (int i = 0; i < sizeof(puerto_pruebas) / sizeof(puertoIO_t); i++) {
        if (puerto_pruebas->gpio < 0) {
            TEST_FAIL_MESSAGE("El numero de gpio debe ser un valor entero real positivo");
        }
        TEST_ASSERT_EQUAL_UINT16(0, puerto_pruebas->type);
    }
}
