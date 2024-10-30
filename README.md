#### **[[ENGLISH]](#spanish)**

# simpleMenu
simpleMenu es una biblioteca para Arduino diseñada para crear y gestionar menús de manera sencilla en proyectos que utilizan pantallas OLED y requieren navegación por múltiples opciones de configuración y control.
Ideal para proyectos como instrumentos musicales electrónicos, robots y dispositivos DIY.

## Video demo
[![Video](https://i9.ytimg.com/vi_webp/CZT4Cc9K-DI/mq2.webp?sqp=CMD0h7kG-oaymwEmCMACELQB8quKqQMa8AEB-AG-AoAC4AOKAgwIABABGGUgXihaMA8=&rs=AOn4CLAyH8MoagsQNR8sYxJ0jhskvQ-MVQ)](https://www.youtube.com/watch?v=CZT4Cc9K-DI)

## Características

- **Fácil Integración:** Diseñada para ser ligera y fácil de incorporar en cualquier proyecto.
- **Navegación Intuitiva:** Proporciona funciones para navegar hacia arriba, abajo y seleccionar opciones en el menú.
- **Personalización:** Permite cambiar alineación y temporización de apagado automático.
- **Soporte para Submenús:** Incluye funcionalidades para gestionar submenús y organizar configuraciones avanzadas.

## Requisitos

## Hardware:

Probado en tarjetas basadas en Esp32.
Pantalla OLED compatible con U8g2lib o Adafruit_GFX.
Controladores de entrada (por ejemplo, botones o sensores capacitivos).

## Software:

- **Arduino IDE** : Recommended 1.8.10 o superior

## Instalacion

1. Descargue el archivo ZIP de la biblioteca desde GitHub.
2. En el IDE de Arduino, vaya a Sketch > Incluir biblioteca > Agregar biblioteca .ZIP...
3. Seleccione el archivo ZIP descargado para instalar la biblioteca.

O puedes extraer el archivo ZIP del paso 1 en el directorio de bibliotecas de Arduino.

## Ejemplo de Uso
Aquí tienes un ejemplo básico de cómo usar simpleMenu:

```
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
```

## Metodos

**Assign(T (&opt), tipo id,  bool title=true):** asigna las opciones al menu opt:opciones , id: un identificador para el menu puede ser numerico o texto, title=true si la primera opcion es titulo
**Root(T (&opt), tipo id,  bool title=true):** se puede establecer un menu raiz, el cual solo se define una vez
**Show():** Muestra el menú actual en la pantalla.
**SetAutoOff(uint8_t timeout):** metodo que establece un tiempo de apagado para la pantalla en segundos
**Pause(bool opt):** pausa la actualizacion del menu en pantalla, util para imprimir en pantalla estando en un submenu
**Up():** desplaza una opcion arriba en el menu
**Down():** desplaza una opcion abajo en el menu
**fullUp():** desplaza al primer item en el menu
**fullDown():** desplaza al ultimo item en el menu
**Select(uint8_t sel, tipo id):** retorna verdadero si se esta seleccionando la opcion actual del menu actual
**Message(String _text,uint8_t align=LEFT,int wait=2000):** despliega un mensaje en pantalla, recibe una cadena de caracteres, una lineacion por defecto a la izquierda y un tiempo de espera en pantalla
**GetInterline():** metodo que devuelve el valor de interlinea establecido

## Contribuciones
Las contribuciones son bienvenidas. Si deseas mejorar simpleMenu, por favor envía un pull request o crea una issue para sugerir cambios.
