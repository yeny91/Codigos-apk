import serial
import time

import sys
from PyQt5 import uic, QtWidgets


arduino=serial.Serial('/dev/ttyUSB0',baudrate=9600, timeout = 3.0)

while True:
    qtCreatorFile = "holamundoapk.ui" # Nombre del archivo aquí.
    Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

    class MyApp(QtWidgets.QMainWindow, Ui_MainWindow):
        def __init__(self):
            QtWidgets.QMainWindow.__init__(self)
            Ui_MainWindow.__init__(self)
            self.setupUi(self)
        # Aqui va el boton
            self.iniciar.clicked.connect(self.calculos)
        # Aqui van las nuevas funciones
        def calculos(self):
            comando='H'
            arduino.write(comando.encode())
            time.sleep(0.1)         
            while  arduino.inWaiting() > 0:    
                    txt= arduino.readline()         
                    texto_st= "MENSAJE: "+str(txt)
                    self.resultado.setText(texto_st)
                    
               
      
        

    if __name__ == "__main__":
        app =  QtWidgets.QApplication(sys.argv)
        window = MyApp()
        window.show()
        sys.exit(app.exec_())