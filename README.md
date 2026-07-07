# DSHFinal
### Evaluación 3 Asignatura desarrollo de software para hardware

## Objetivos:
  Como principal objetivo de este proyecto se realizo un sistema IoT mediante Esp-32 utilizado como Hotspot, el cual pueda conectarse con multiples Esp-32, estos realizan sus tareas correspondientes, las cuales son:

      1. Medir o Sensar temperatura ambiente y enviarla a una base de datos
      2. Indicador de luces led temperatura actual usando una base de datos
      
  Como Segundo objetivo se busca tener una interfaz Web utilizando Flask python, la cual nos permitira ver de forma grafica la temperatura actual del sistema.

## Diagrama de flujo
<img width="453" height="275" alt="Diagrama de flujo" src="https://github.com/user-attachments/assets/2cb8ac9f-a211-41b9-b6ac-236df35123dd" />

## Instrucciones
### instalaciones necesarias
- MariaDB
- Python
- Arduino IDE

### Proceso
- Se debe crear la base de datos con tabla llamada "temperaturas", que guarde ID, temperatura y fecha.
- Se deben iniciar los script de python app.py y enviar_temperatura_leds.py
- Se deben iniciar los 3 esp con los codigos, ESP_HOTSPOT.ino, Leds_db_python.ino y Sensor_Temperatura.ino
Luego de seguir estas indicaciones el sistema se encuentra operando, ya es posible conectarce a la interfaz web mediante la ip del equipo en el que esta andando el script app.py con puerto 5000
