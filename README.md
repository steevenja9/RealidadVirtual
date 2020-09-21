# RealidadVirtual

**Grupo 3 personas:** Jesús Delgado Jiménez, Jaime Steeven Puerta Martinez , Tomás Iglesias Sáez.

**Proyecto:**           **_L-System_**
        Consiste en un fork del siguiente proyecto: [Proyecto Erik Paluka.](https://github.com/paluka/L-Systems-OpenGL)
        
 *Requisitos:* freeglut.lib, glew32.lib y FreeImage.lib.
 
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

Para dibujar, los elementos, hemos hecho uso de _GL_LINES_ y _GL_TRIANGLES_, para el tronco y ramas, y para el suelo y hojas, respectivamente, para asi manejar ambos modos, algo que obviamente afecta al resultado final pues _GL_LINES_, no permite bien usar texturas, y que el grosor, es el grosor de una línea, por lo que no queda muy realista. Pero hemos creído que era mejor trabajar con ambos métodos, también pensamos en utilizar _GL_POLYGON_ para el suelo, pero era muy poca cosa.



**CAMBIOS**

+ Lo primero que hicimos fué intentar crear un arbol más realista, y que encuadrase bien con la pantalla. Si mira la siguiente imagen ve como realmente finaliza la ejecución: [Imagen final Erik-Paluka.](https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/2.Erik.JPG)
Por lo que modificamos la intensidad de los colores **(ambient, difusse, specular)**, el tamaño de la ventana, y los carácteres que se añadirían en cada iteración.

        1. Al inicio: "D[LXV]D[RXV]LX".
        2. Ahora: "DD[RVXVRV]DD[RVXVLV]LVX". 
        También hemos añadido más posibles formas, para que no siempre queden iguales.




+ Luego le introducimos las texturas, una para la hoja, otra para el suelo y otra para el tronco y ramas, esta última como ya hemos explicado no queda muy realista.
Dichas texturas las podrá encontrar en la carpeta de imagenes de este repositorio.

        1. [Tronco/Rama.]()
        2. [Hoja.]()
        3. [Suelo.]()
        
        
    
    
+ Añadimos más funcionalidades a la cámara, más opciones en el keyboard ya creado, y un nuevo keyboard especial dedicado a las teclas de las flechas.

        1. Ahora                                                                 2. Antes
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Modificacion_Keyboard.JPG" width="400"/> <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Keyboard_Erik.JPG" width="400"/><img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Keyboard_Flechas.JPG"/>

También, modificamos la función **animate()**, encargada de darle movimiento al arbol para simular el viento, pero eran movimientos muy bruscos y muy lentos cuando crecía más nuestro árbol, por lo que modificamos el rango de movimiento, y también limitamos el número de niveles de crecimiento del árbol, pues empieza a relentizarse el proyecto.

La función drawLine() es la que nos permite crear toda la estructura del tronco del árbol. Al principio declaramos los valores para obtener los distintos colores entre 
los que podemos elegir, después configuramos la iluminación que tendrá en la escena y la textura y por último la forma en la que se dibujará.

<img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/codigoTronco.JPG" />

La otra función que hemos añadido para tratar nuestro árbol es leaf(), con la que configuramos todo lo relacionado con las hojas. Al principio, igual que en el método
anterior, tenemos las distintas configuraciones para colorear las hojas, después tratamos la iluminación y las texturas, todo esto podemos verlo en la primera captura, 
mientras que, en la segunda podemos ver como le damos la forma a las hojas que aparecerán en nuestro dibujo.

<img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/codigoHojas1.JPG" width="400"/> <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/codigoHojas2.JPG" width="400"/>


+ Una vez terminado todo el árbol, nos pusimos a hacer el menú de inicio.

El Menú esta compuesto por 4 opciones que son:
<p align="center">
<img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/MenuInicio.JPG" />
</p>

        1. Ver controles.
        Donde están todas las teclas que se utilizan para el movimiento de las cámaras 
        en los ejes x, y ,z y para moverse por la escena.
<p align="center">
<img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Vcontroles.PNG" >
</p>

        2. Modificación de variables
        En este apartado del menú podemos modificar las siguientes variables:
        
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/MVariables.JPG" />
 
 Tanto el color del tronco, como el de las hojas tienen 3 opciones para elegir, siendo la primera de estas la opción por defecto. Las otras opciones por defecto
 son un tamaño de árbol de 8, una anchura de 5.7 y árbol CON hojas. 
 
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/ColorTronco.JPG" />
 
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/ColorHojas.JPG" />

 
 Vamos a ver las variables que usamos y como trabaja cada opción de este submenú con la siguiente imagen (siguen el mismo orden que la imagen anterior donde 
 mostramos el menú).
 
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Funcion%20mvariables.JPG" />

        3. Salir
        Esta opción hará que termine la ejecución del programa y este se cierre.
        
        4. Ejecutar
        Al seleccionar esta opción se nos abrirá una nueva ventana que será donde se pintará la escena con los datos que 
        hemos introducido o bien con los que vienen por defecto. Una vez en esta pantalla saldremos de ella y volveremos
        al menú principal pulsando la tecla 'm' como hemos visto anteriormente en los controles de la aplicación. 
        
        A continuación mostramos unos ejemplos de la ejecución del programa:

<br>
<br>
<br>
<br>
<br>
<br>

**SALIDA**

<p align="center" title="Profundidad 6">
 <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/Salida1.JPG"  />
</p>


