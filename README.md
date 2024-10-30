# simpleMenu
simpleMenu es una biblioteca para Arduino diseñada para crear y gestionar menús de manera sencilla en proyectos que utilizan pantallas OLED y requieren navegación por múltiples opciones de configuración y control.
Ideal para proyectos como instrumentos musicales electrónicos, robots y dispositivos DIY.

# Características

Fácil Integración: Diseñada para ser ligera y fácil de incorporar en cualquier proyecto.
Navegación Intuitiva: Proporciona funciones para navegar hacia arriba, abajo y seleccionar opciones en el menú.
Personalización: Permite cambiar alineación y temporización de apagado automático.
Soporte para Submenús: Incluye funcionalidades para gestionar submenús y organizar configuraciones avanzadas.


# Requisitos

## Hardware:

Pantalla OLED compatible con U8g2lib o Adafruit_GFX.
Controladores de entrada (por ejemplo, botones o sensores capacitivos).

## Software:

Arduino IDE

## Instalación
Clona este repositorio e instala la biblioteca en tu Arduino IDE.

bash
Copiar código
git clone https://github.com/habuenav/simpleMenu
Incluir la Biblioteca en tu código:



## Ejemplo de Uso
Aquí tienes un ejemplo básico de cómo usar simpleMenu:


#include <simpleMenu.h>


// Configuración de pantalla OLED y menú
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);
simpleMenu menu(display);

void setup() {
    display.begin(); // Inicializa la pantalla
    menu.SetAutoOff(30); // Apagado automático del menú en 30 segundos
    menu.Root(Main, "Main"); // Define el menú principal
}

void loop() {
    menu.Show(); // Muestra el menú
    menu.Up();   // Navega hacia arriba
    menu.Down(); // Navega hacia abajo
    menu.Select(); // Selecciona la opción
}


## Funciones
SetAutoOff(uint16_t time): Configura el tiempo en segundos para que el menú se apague automáticamente.

alignTitle y alignItem: Configura la alineación de títulos y elementos (CENTRO, IZQUIERDA).

Root(txtMenu *menu, const char* title): Establece el menú principal y el título.

Show(): Muestra el menú actual en la pantalla.

Up() y Down(): Navega hacia arriba y abajo en el menú.

Select(): Selecciona la opción actual.

Assign(txtMenu *menu, const char* title): Asigna un submenú a una opción seleccionada.

## Contribuciones
Las contribuciones son bienvenidas. Si deseas mejorar simpleMenu, por favor envía un pull request o crea una issue para sugerir cambios.
