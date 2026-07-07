import socket
import subprocess
import time

# =========================
# CONFIGURACIÓN ESP32 #3 LEDS
# =========================
ESP_LED_HOST = "192.168.4.3"
ESP_LED_PORT = 12346

# =========================
# CONFIGURACIÓN BASE DE DATOS
# =========================
DB_NAME = "dsh_final"

# Cada cuántos segundos revisa la base de datos
INTERVALO_REVISION = 2

# Diferencia mínima para considerar que cambió la temperatura
DIFERENCIA_MINIMA = 0.01


def leer_ultima_temperatura():
    try:
        sql = """
        SELECT temperatura
        FROM temperaturas
        ORDER BY fecha_hora DESC, id DESC
        LIMIT 1;
        """

        resultado = subprocess.run(
            ["mariadb", "-N", "-B", "-D", DB_NAME, "-e", sql],
            capture_output=True,
            text=True,
            timeout=5
        )

        if resultado.returncode != 0:
            print("ERROR BD:", resultado.stderr)
            return None

        salida = resultado.stdout.strip()

        if salida == "":
            print("BD sin registros de temperatura")
            return None

        temperatura = float(salida.replace(",", "."))
        return round(temperatura, 2)

    except Exception as e:
        print("ERROR leyendo BD:", e)
        return None


def conectar_esp32():
    while True:
        try:
            print("Conectando al ESP32 #3...")

            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(5)
            s.connect((ESP_LED_HOST, ESP_LED_PORT))

            # Mantener conexión TCP activa
            s.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)

            print("Conectado al ESP32 #3")
            return s

        except Exception as e:
            print("No se pudo conectar al ESP32 #3:", e)
            print("Reintentando en 3 segundos...")
            time.sleep(3)


def enviar_temperatura(socket_esp32, temperatura):
    try:
        mensaje = f"TEMP:{temperatura:.2f}\n"

        socket_esp32.sendall(mensaje.encode())

        respuesta = socket_esp32.recv(1024).decode().strip()

        print(f"Enviado al ESP32 #3: {mensaje.strip()} | Respuesta: {respuesta}")

        return True

    except Exception as e:
        print("ERROR enviando al ESP32 #3:", e)
        return False


def main():
    print("Iniciando conexión constante con ESP32 #3...")

    socket_esp32 = conectar_esp32()

    ultima_temperatura_enviada = None

    while True:
        temperatura_actual = leer_ultima_temperatura()

        if temperatura_actual is not None:

            if ultima_temperatura_enviada is None:
                print("Primer envío de temperatura")
                enviado = enviar_temperatura(socket_esp32, temperatura_actual)

                if enviado:
                    ultima_temperatura_enviada = temperatura_actual
                else:
                    socket_esp32.close()
                    socket_esp32 = conectar_esp32()

            else:
                diferencia = abs(temperatura_actual - ultima_temperatura_enviada)

                if diferencia >= DIFERENCIA_MINIMA:
                    print(
                        f"Cambio detectado: {ultima_temperatura_enviada} → {temperatura_actual}"
                    )

                    enviado = enviar_temperatura(socket_esp32, temperatura_actual)

                    if enviado:
                        ultima_temperatura_enviada = temperatura_actual
                    else:
                        socket_esp32.close()
                        socket_esp32 = conectar_esp32()

                else:
                    print(f"Sin cambio de temperatura: {temperatura_actual} °C")

        time.sleep(INTERVALO_REVISION)


if __name__ == "__main__":
    main()
