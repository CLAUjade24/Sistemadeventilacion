# Sistema de ventilacion

El sistema de ventilacion consiste en darle un hambiente calido para el hogar dandole  cierta prioridades que son importantes 
desde el uso de sus sensores para darle una alta tecnologia, esto es una buena practica para darse una idea para el hogar 
nosostros ocupamos en especial un Lm35 para la temperatura de su hogar.

* Se controla desde una pagina de web para saber de alguna forma como se encuentra la temperatura del hogar.

* Al momento de recibir una temperatura alta, el usuario ingresa a la pagina y checa si no le parece la temperatura adecuada puede         activar el ventilaor

 * En caso contrario el mismo sensor transistor 2N2222 se le connfigura al ventilador para al momento de que sienta una cierta    temperatura inadecuada el ventilador se encedera automaticamente asi le dara un hambiente calido al hogar, sin necesidad de checar la temperatura del hogar
 
 * El segundo sensor que ocupamos fue el de luminicidad, este sensor nos brindara luz al momento de que en el hogar o lugar se encuentre con muy poca luz esto con el fin de que los amantes de lo ajeno no sospechen que la casa se encuentra sola o solo para darle luz a un espacio del lugar
 
 * Para el tercer sensor sera el de humedad, lo utilizamos para saber cuanta humedad transmite el lugar en donde se encuetra   ubicado. 
 Cabe destacar que para los sensores de humedad se utilizo de DHT11, esto mas adelante se mostraran la imagenes del material que se ocupo 
 
# Material 
* Arduino Uno 
* Un servomotor sg90
* sensor de humedad DHT11
* Sensor de tempreatura DHT11
* Arduino Ethernet Shield W5100
* Sensor de luz (fotoresistencia)
* Un ventilador de 5V o un motor de corriente continua.
* cables hembra-macho y macho-macho
* protoboard
* Un modem para poder usar con exito Shield W5100
* Un transistor 2N2222. Comprobad que lleva rotulada esta referencia, porque el sensor de temperatura es similar

# Caracteristicas del material
  El Arduino ethernet shield nos da la capacidad de conectar un Arduino a una red ethernet. Es la parte física que implementa la  pila de protocolos TCP/IP.     
     
  Está basada en el chip ethernet Wiznet W5100. El Wiznet W5100 provee de una pila de red IP capaz de soportar TCP y UDP. Soporta  hasta cuatro conexiones de sockets simultáneas. Usa la librería Ethernet para leer y escribir los flujos de datos que pasan por  el puerto ethernet. Me permitirá escribir sketches que se conecten a internet usando la shield.
  El shield provee un conector ethernet estándar RJ45. La ethernet shield dispone de unos conectores que permiten conectar a su vez otras placas encima y apilarlas sobre la placa Arduino.

Arduino usa los pines digitales 10, 11, 12, y 13 (SPI) para comunicarse con el W5100 en la ethernet shield. Estos pines no pueden ser usados para e/s genéricas.

 ![imagen de Arduino Ethernet Shield W5100](https://github.com/CLAUjade24/Sistemadeventilacion/blob/master/imagSistemaventilador/ArduinoEthernetShield%20w5100.jpg)

El botón de reset en la shield resetea ambos, el W5100 y la placa Arduino.

La shield contiene varios LEDs para información:

    * ON: indica que la placa y la shield están alimentadas
    * LINK: indica la presencia de un enlace de red y parpadea cuando la shield envía o recibe datos
    * 100M: indica la presencia de una conexión de red de 100 Mb/s (de forma opuesta a una de 10Mb/s)
    * RX: parpadea cuando el shield recibe datos
    * TX: parpadea cuando el shield envía datos

El jumper soldado marcado como “INT” puede ser conectado para permitir a la placa Arduino recibir notificaciones de eventos por interrupción desde el W5100, pero esto no está soportado por la librería Ethernet. El jumper conecta el pin INT del W5100 al pin digital 2 de Arduino.

El slot SD en la shield usa la l


  * Humedad y temperatura
  
 ![imagen de sensore dht11](https://github.com/CLAUjade24/Sistemadeventilacion/blob/master/imagSistemaventilador/sensor-de-humedad-y-temperatura-dht11.jpg)


 
 
 
