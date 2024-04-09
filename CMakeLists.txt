cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(entradas_salidas)
pico_sdk_init()
add_executable(${PROJECT_NAME} src/main.c)
pico_enable_stdio_usb(${PROJECT_NAME} 1)   #Necesario para que se habilite la entrada UART del micro
pico_enable_stdio_uart(${PROJECT_NAME} 0)  #Necesario para que se habilite la entrada UART del micro
pico_add_extra_outputs(entradas_salidas)
target_link_libraries(${PROJECT_NAME} pico_stdlib )
