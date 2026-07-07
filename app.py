from flask import Flask, render_template
import socket
import subprocess

app = Flask(__name__)

# =========================
# CONFIGURACIÓN ESP32 SENSOR
# =========================
HOST = "192.168.4.2"
PORT = 12345


def guardar_temperatura_mariadb(temperatura):
    try:
        print("Intentando guardar en MariaDB...")

        temperatura = float(temperatura)

        sql = f"""
        INSERT INTO temperaturas (temperatura)
        VALUES ({temperatura:.2f});
        """

        resultado = subprocess.run(
            ["mariadb", "-e", sql],
            capture_output=True,
            text=True,
            timeout=5
        )

        if resultado.returncode == 0:
            print("OK MARIADB: Temperatura guardada:", temperatura)
            return True
        else:
            print("ERROR MARIADB:", resultado.stderr)
            return False

    except Exception as e:
        print("ERROR MARIADB:", e)
        return False


def leer_sensor():
    try:
        print("Conectando con ESP32...")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.settimeout(3)
            s.connect((HOST, PORT))

            data = s.recv(1024).decode().strip()
            print("RECIBIDO ESP32:", data)

            if data == "ERROR:DHT11":
                return 0, "Error sensor DHT11"

            clave, valor = data.split(":")
            temperatura = float(valor)

            if temperatura < 25:
                estado = "Temperatura Normal"
            elif temperatura >= 25 and temperatura < 30:
                estado = "Temperatura Media"
            else:
                estado = "Temperatura Alta"

            guardado = guardar_temperatura_mariadb(temperatura)

            if guardado:
                print("Registro completado correctamente")
            else:
                print("No se pudo guardar en MariaDB")

            return temperatura, estado

    except Exception as e:
        print("ERROR ESP32:", e)
        return 0, "Sin conexión"


@app.route("/")
def index():
    temperatura, estado = leer_sensor()

    return render_template(
        "index.html",
        temperatura=temperatura,
        estado=estado
    )


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
