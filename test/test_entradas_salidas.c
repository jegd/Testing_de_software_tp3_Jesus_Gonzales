
#include "unity.h"
#include <stdbool.h>
#include "entradas_salidas.h"
#include "mock_stdlib.h"

#define ANTIREBOTE 20U
maqEstados_entrada_t maquina_pruebas;
puertoIO_t * puerto_pruebas;
debounceState_t estado_pruebas;

void test_maquina_de_estado_inicializa_en_estado_DOWN(void) {

    // estado_pruebas = initMaqPulsador(&maquina_pruebas, puerto_pruebas, ANTIREBOTE);
    // TEST_ASSERT_EQUAL_UINT16(INPUT_DOWN, estado_pruebas);
}
