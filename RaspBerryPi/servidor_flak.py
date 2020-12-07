from flask import Flask
import serial
serialPort = serial.Serial('/dev/ttyAMA0', 9600)
app = Flask(_name_)

@app.route("/")
def hello():
    return "Servidor Enbotelladora Raspberry Pi 4"

    @app.route("/crear_pedido/<int:botellas>", methods=['POST'])
    def pedido(botellas=1):
        print("llegan "+str(botellas))
        serialPort.write(str(botellas)+'\r\n')
        return "ok"

if _name_ == "_main_":
    app.run(host="0.0.0.0", port=80, debug=True)
