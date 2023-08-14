# Control-de-distancia-delantera-carrito-ARDUINO


> Este proyecto fue realizado para la materia **Controladores Hibridos** de la carrera **Ingeniería en AUtomatización y Autotrónica** para **8vo semestre**


# Introducción 

El presente repositorio indica cómo se puede realizar un controlador basado en lógica difusa. El proyecto consiste en controlar la distancia delantera de un carrito, la sensor que usaremos es un **HC-SR04** para hacer la retroalimentación y todo estará programado en un **ARDUINO UNO** _(importante mensionar que es igual de posible en una Raspberry)_. Los actuadores que usaremos son motorreductores _(de los amarillos)_, para controlar el movimiento de los actuadores usaremos un **Puente H, L298N** y dos fuentes de energía, una será para alimentar el Arduino (5V a 1A) y otra fuente para alimentar el puente H (5V a 2.5A)

# Contextualización del problema

### Justificación 

Al finalizar este proyecto se entregará un carrito con control de distancia delantero. Se plantea una solución propuesta para el nuevo hito automotriz enfocado a la **Protección a peatones**, en donde cada que sea detectado un obstaculo cerca del auto exista un actuador que indique alguna recomendación o acción de reacción. 

En cuanto al ámbito escolar, se busca una asimilación de la importancia de os procesos de simulación _(DIGITALIZACIÓN)_ desde un punto de vista matemático _(CAE)_. Esto con la finalidad de facilitar la toma de decisiones basado en datos estadísticos y en función de un controlador no discreto. 

### Objetivos
**Generales**
+ Diseñar un controlador basado el lógica difusa para controlar un carrito en función de una distacia delantera de 20 centímetros (+,- 2 cm) con ayuda de un sensor ultrasonico.

**Particulares**
+ Realizar una investigacion sobre las funciones de membresia, grado de pertenencia

+ Realizar una práctica que permita realizar el posicionamiento de un servomotor utilizando un potenciometro en lazo cerrado

+ Hacer pruebas. 

## Carrito Final

El carrito que se entrega al final del curso se realiza con MDF _(Medium Density Fiberboard)_. El diseño del carrito se realiza en **SolidWorks 2020**, la programación se realiza en **Arduino**.


![Diseño y simulación de aspecto del carrito en SolidWorks.](Images/14.png)

Dentro del diagrama podemos observar los siguientes elementos:

+ Arduino UNO (cuadro azul)

+ Puente H (cuadro rojo)

+ Llantas con Motorreductores

+ Estructura de MDF

### Programación 

La programación es relaativamente sencilla. Podemos ver el diagrama de flujo del programa que se realizó en ARDUINO en la soguiente imagen. 

![Diagrama de flujo](Images/Diagrama1.png)

### Final

Por último podemos ver el resultado en físico del proyecto terminado y armado. 

![Carrito terminado](Images/im3.jpeg)

Igualmente, en e siguiente link podemos ver el funcionamiento deseado del controlador. 

[Video del carrito](https://www.youtube.com/watch?v=6mszPVwZKWs)


# Conclusión del proyecto

Podemos concluir que la lógica difusa se puede utilizar cuando la complejidad del proceso requiere de modelos matemáticos bastante tardados de describir. cuando existen definiciones y conceptos que estrictamente nose pueden definir con facilidad. pero que igualmente es necesario controlar de alguna forma. 

Los objetivos se cumplieron con éxito. El desarrollo del controlador difuso _(Una entrada, Una salida)_, una vez entendido, fue fécil de implementar. Gracias al apoyo y mentoría del docente Angel Ortega, el proyecto tuvo la evolución y desarrollo esperado. 




