import serial
import time

import sys
from PyQt5 import uic, QtWidgets


arduino=serial.Serial('/dev/ttyUSB0',baudrate=9600, timeout = 3.0)

while True:
    qtCreatorFile = "Apk-sensores-dos.ui" # Nombre del archivo aquí.
    Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

    class MyApp(QtWidgets.QMainWindow, Ui_MainWindow):
        def __init__(self):
            QtWidgets.QMainWindow.__init__(self)
            Ui_MainWindow.__init__(self)
            self.setupUi(self)
        # Aqui va el boton

            
            self.movimiento.clicked.connect(self.leermovimiento)
            self.gaveta.clicked.connect(self.leergaveta)
            self.corriente.clicked.connect(self.leercorriente)
            self.flujoagua.clicked.connect(self.leerflujoagua)
            self.borrar.clicked.connect(self.leerborrar)
            self.contadorhuevos.clicked.connect(self.leercontadorhuevos)
            
            
        def leermovimiento(self): 
            comando='M'
            arduino.write(comando.encode())
            time.sleep(0.2)         
            while  arduino.inWaiting() > 0:    
                    txt= arduino.readline()
                    texto_st= "ESTADO : "+str(txt) 
                    self.resmov.setText(texto_st)
              
        def leergaveta(self): 
            comando='G'
            arduino.write(comando.encode())
            time.sleep(0.2)         
            while  arduino.inWaiting() > 0:    
                    txt= arduino.readline()
                    texto_st= "ESTADO: "+str(txt) 
                    self.resgaveta.setText(texto_st)
        
        def leercorriente(self): 
            comando='C'
            arduino.write(comando.encode())
            time.sleep(0.2)         
            while  arduino.inWaiting() > 0:    
                    txt= arduino.readline()
                    texto_st= "ESTADO: "+str(txt) 
                    self.rescorriente.setText(texto_st)
                    
                    
        def leerflujoagua(self): 
            comando='F'
            arduino.write(comando.encode())
            time.sleep(0.2)         
            while  arduino.inWaiting() > 0:    
                    txt= arduino.readline()
                    texto_st= "ESTADO: "+str(txt) 
                    self.resflujoagua.setText(texto_st)

           
        def leerborrar(self):
            self.resgaveta.clear()
            self.resmov.clear()
            self.rescorriente.clear()
            self.resflujoagua.clear()
            self.rescontadorhuevos.clear()
            
        def leercontadorhuevos(self):
            comando='H'
            arduino.write(comando.encode())
            time.sleep(0.2)         
            while  arduino.inWaiting() > 0:    
                   txt= arduino.readline()
                   texto_st= "ESTADO: "+str(txt) 
                   self.rescontadorhuevos.setText(texto_st) 
            
            
            
                  
            
                      
       
        

    if __name__ == "__main__":
        app =  QtWidgets.QApplication(sys.argv)
        window = MyApp()
        window.show()
        sys.exit(app.exec_())