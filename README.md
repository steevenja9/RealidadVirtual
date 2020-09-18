# RealidadVirtual

**Grupo 3 personas:** Jesús Delgado Jiménez, Jaime Steeven , Tomás

**Proyecto:**           **_L-System_**
        Consiste en un fork del siguiente proyecto: [Proyecto Erik Paluka.](https://github.com/paluka/L-Systems-OpenGL)
        
 *Requisitos:* freeglut.lib y glew32.lib
 
 *Salida:*     
 
  <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/1.Erik.JPG" />




**Estudio del proyecto**

Una vez cogido el proyector como base, hemos estudiado su código para entender su funcionamiento, el cuál consiste en utilizar un string, e ir sustituyendo o añadiendo caracteres para darle forma a un árbol, en el que cada carácter llamada a una función determinada:
1. X: Inicio 
2. D: Tronco o rama
3. V: Hoja
4. R: Rotación hacia la derecha
5. L: Rotación hacia la izquierda
6. [: push() --> Modificamos el grosor de las ramas/tronco y glPushMatrix()
7. ]: pop()  --> Modificamos el grosor de las ramas/tronco y glPopMatrix()

Para dibujar, los elementos, hemos hecho uso de _GL_LINES_ y _GL_TRIANGLES_, para el tronco y ramas, y para el suelo y hojas, respectivamente, Para asi manejar ambos modos, algo que obviamente afecta al resultado final pues _GL_LINES_, no permite bien usar texturas, y que el grosor, es el grosor de una línea, por lo que no queda muy realista. Pero hemos creído que era mejor trabajar con ambos métodos, también pensamos en utilizar _GL_POLYGON_ para el suelo, pero era muy poca cosa.



**CAMBIOS**

+ Lo primero que hicimos fué intentar crear un arbol más realista, y que encuadrase bien con la pantalla. Si mira la siguiente imagen ve como realmente finaliza la ejecución: [Imagen final Erik-Paluka.](https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/2.Erik.JPG)
Por lo que modificamos la intensidad de los colores **(ambient, difusse, specular)**, el tamaño de la ventana, y los carácteres que se añadirían en cada iteración.

        1. Al inicio: "D[LXV]D[RXV]LX".
        2. Ahora: "DD[RVXVRV]DD[RVXVLV]LVX". 
        También hemos añadido más posibles formas, para que no siempre queden iguales.




+ Luego le introducimos las texturas, una para la hoja, otra para el suelo y otra para el tronco y ramas, y esta ultima como ya he explicado no queda muy realista.
Dichas texturas las podrá encontrar en la carpeta de imagenes de este repositorio.

        1. [Tronco/Rama.]()
        2. [Hoja.]()
        3. [Suelo.]()
        
        
    
    
+ Añadimos más funcionalidades a la cámara, más opciones en el keyboard ya creado, y un nuevo keyboard especial dedicado a las teclas de las flechas.

        1. Ahora                                                                 2. Antes
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Modificacion_Keyboard.JPG" width="450"/> <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Keyboard_Erik.JPG" width="450"/><img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Keyboard_Flechas.JPG"/>

También, modificamos la función **animate()**, encargada de darle movimiento al arbol para simular el viento, pero eran movimientos muy bruscos y muy lentos cuando crecía más nuestro árbol, por lo que modificamos el rango de movimiento, y también limitamos el número de niveles de crecimiento del árbol, pues empieza a renlentizarse el proyecto.


+ Una vez terminado todo el árbol, nos pusimos a hacer el menú de inicio.

En el Menu esta compuesto por 4 opciones que son:

<img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/menu.png" />

        1. Ver controles.
        Donde estan todos las teclas que se utilzan para el movimiento de las camaras en los eje x, y ,z y moverse.
        <p align="center" >
<img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Vcontroles.PNG" width="600"/>
</p>

        2. Modificación de variables
        En este parte del menu podemos modificar las variables:
        tamaño de arbol con un maximo de 8 
        ancho del arbol


+ Para puntos extras decidimos hacer el mismo proyecto en processing

 AQUI VA UNA EXPLICACIÓN MEDIANAMENTE LARGA DE LA TRADUCCIÓN DE OPENGL A PROCESSING
 Y UNA IMAGEN DE LA SALIDA




**SALIDA**

<p align="center" title="Profundidad 6">
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Salida1.JPG"  />
</p>


