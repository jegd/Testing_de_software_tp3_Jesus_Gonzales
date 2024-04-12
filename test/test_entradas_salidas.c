
#include "unity.h"
#include <stdbool.h>
#include "entradas_salidas.h"
#include "Mockstdlib.h"
#include <assert.h>
#define ANTIREBOTE    20U // Tiempo de antirebote en us
#define PIN_LECTURA   5U  // Pin de lectura
#define PIN_LECTURA_2 6U  // Pin de lectura
#define PIN_LECTURA_3 2U  // Pin de lectura
#define INPUT         0U  // Pin de lectura
#define OUTPUT        1U  // Pin de lectura

maqEstados_entrada_t maquina_pruebas_1;
maqEstados_entrada_t maquina_pruebas_2;
puertoIO_t puerto_pruebas[] = {{.gpio = PIN_LECTURA, .type = INPUT},
                               {.gpio = PIN_LECTURA_2, .type = INPUT},
                               {.gpio = PIN_LECTURA_3, .type = INPUT}};
debounceState_t estado_pruebas;
uint8_t numero_de_gpio;
bool valor_de_lectura_de_pin = 0;
uint32_t valor_tiempo_para_prueba = 0;

// Se consulta la máquina de estado para conocer en qué estado se encuentra
// Se consultan las RPM del sensado
uint auxiliar_gpio_init(uint8_t numGPIO, int call_count) {
    assert(&numGPIO != NULL);
    return 1;
}

uint auxiliar_gpio_set_dir(uint gpio, bool type, int call_count) {
    return 1;
}

bool auxiliar_gpio_get(uint gpio) {

    return valor_de_lectura_de_pin;
}
uint32_t auxiliar_time_us_32() {
    return valor_tiempo_para_prueba;
}
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
// Probar que inicializan adecuada de las gpio
void test_inicio_adecuado_de_gpio(void) {
    gpio_init_StubWithCallback((CMOCK_gpio_init_CALLBACK)auxiliar_gpio_init);
    gpio_set_dir_StubWithCallback((CMOCK_gpio_set_dir_CALLBACK)auxiliar_gpio_set_dir);
    TEST_ASSERT_EQUAL_UINT16(
        1, iniciacion_gpio(puerto_pruebas, sizeof(puerto_pruebas) / sizeof(puertoIO_t)));
}

// Probar que se inicializa en estado down la maquina de estado
void test_inicio_en_estado_down_de_maquina_de_estados(void) {
    TEST_ASSERT_EQUAL(INPUT_DOWN,
                      initMaqPulsador(&maquina_pruebas_1, &(puerto_pruebas[0]), ANTIREBOTE));
}
// No hay error al asignar otra máquina de estado al mismo puerto
void test_asignando_otra_maquina_de_estados_al_mismo_puerto(void) {
    TEST_ASSERT_EQUAL(INPUT_DOWN,
                      initMaqPulsador(&maquina_pruebas_1, &(puerto_pruebas[0]), ANTIREBOTE));
    TEST_ASSERT_EQUAL(INPUT_DOWN,
                      initMaqPulsador(&maquina_pruebas_2, &(puerto_pruebas[0]), ANTIREBOTE));
}

// Probar repiendo inicialización de máquina de estados
void test_enviando_valor_null_como_maquina_de_estado(void) {
    TEST_ASSERT_EQUAL(INPUT_DOWN,
                      initMaqPulsador(&maquina_pruebas_1, &(puerto_pruebas[0]), ANTIREBOTE));
    TEST_ASSERT_EQUAL(INPUT_DOWN,
                      initMaqPulsador(&maquina_pruebas_1, &(puerto_pruebas[0]), ANTIREBOTE));
}
// Se consulta de manera correcta el estado de la maquina de estados
void test_consulta_correcta_de_maquina_de_estados(void) {
    gpio_get_StubWithCallback((CMOCK_gpio_get_CALLBACK)auxiliar_gpio_get);
    time_us_32_StubWithCallback((CMOCK_time_us_32_CALLBACK)auxiliar_time_us_32);
    maquina_pruebas_1.ultimoTiempoLectura = 0;
    valor_tiempo_para_prueba = 10;
    maquina_pruebas_1.estado = INPUT_DOWN;
    valor_de_lectura_de_pin = 0;
    TEST_ASSERT_EQUAL(INPUT_DOWN, consultaMaq(&maquina_pruebas_1));
}