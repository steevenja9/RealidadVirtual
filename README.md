# RealidadVirtual

**Grupo 3 personas:** Jesús Delgado Jiménez, Jaime Steeven , Tomás

**Proyecto:**           **_L-System_**
        Consiste en un fork del siguiente proyecto: [Proyecto Erik Paluka.](https://github.com/paluka/L-Systems-OpenGL)
        
 *Requisitos:* freeglut.lib y glew32.lib
 
 *Salida:*     
 
  <img src= "https://github.com/steevenja9/RealidadVirtual/blob/master/Imagenes/1.Erik.JPG" />



**CAMBIOS**

Una vez cogido el proyector como base, hemos estudiado su código para entender su funcionamiento, el cuál consiste en utilizar un string, e ir sustituyendo o añadiendo caracteres para darle forma a un árbol, en el que cada carácter llamada a una función determinada:
1. X: Inicio 
2. D: Tronco o rama
3. V: Hoja
4. R: Rotación hacia la derecha
5. L: Rotación hacia la izquierda
6. [: push()
7. ]: pop()



utilizando _GL_LINES_ y _GL_TRIANGLES_
