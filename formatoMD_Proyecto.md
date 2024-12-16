# Actividad final

## Ejercicio 1: Concepto y noción de archivo real y virtual

Un __archivo real__ se refiere a una entidad de datos concreta que existe físicamente en un medio de almacenamiento (como un discoduro, SSD o unidad USB). Mientras que un __arhicvo virtual__ es la idea de un archivo que no existe físicamente en el disco duro, pero que el sistema operativo muestra como si fuera un archivo real. Estos archivos se crean y manejan en tiempo real, y sirven para proporcionar información del sistema, facilitar tareas especiales o simular dispositivos, sin ocupar espacio en el almacenamiento. Un archivo virtual es como un "archivo falso" que el sistema operativo te muestra, pero que no existe realmente en el disco duro.

Ejemplo de __NUL__ en windows:
NUL es un archivo virtual en Windows que actúa como un "basurero" de datos. Tiene diferentes funciones como:
* Silenciar la salida: Si un comando o programa genera mucha información que no quieres ver, puedes redirigir esa información a NUL.
* Evitar creación de archivos temporales: En lugar de crear un archivo temporal para descartar datos no deseados, puedes usar NUL.
* Pruebas: Es útil en scripts cuando necesitas una "salida vacía".

Tambien se utiliza para manejar estos tipos de archivos los sitemas de archivos. Son sistemas diseñados para organizar y gestionar los datos almacenados en dispositivos de almacenamiento. Permite a los usuarios acceder, manipular, almacenar los datos de manera segura. Sus componentes son:

* Indices de nodo: Es una herramienta que permite acceder directamente a los registros de un archivo en el disco.
* Superbloque: Almacena información sobre el estado y funcionamiento del sistema de archivos.
* Registro de eventos: Es una funcion que lleva un registro de las operaciones pendientes.

En sistemas operarivos basados en Linux el directorio /proc contiene archivos virtuales que representan información del sistema en tiempo real, mientras que un arhivo fisico tendrias que monitorear y guardar la informacion manual y constantemente. Por ejemplo, __/proc/cpuinfo__ proporciona detalles sobre el procesador, como su modelo, velocidad, número de núcleos, etc.

En windows esta __Named Pipes__ que ayuda a la comunicacion entre programas.

## Ejercicio 2: Componentes de un sistema de archivos

Ademas de los componentes que se habian mencionado anteriormente, los sistemas de archivos tambien cuentan con:
* Tabla de asginaciones: Es una estructura de datos para realizar un seguimiento de como se asignan los bloques de almacenamiento en el disco.
* Metadatos: Se refiere a informacion adicional que describe las caracteristicas de los archivos y directorios almacenados en el sistema de archivo. Contienen informacion de los archivos, pero no los datos reales del archivo.

| **NTFS**                         | **EXT4**          |
|:---------------------------------------:|----------------------:|
|  Usa una tabla maestra (MFT) para almacenar información de archivos y reducir la fragmentación.                  | Utiliza mapas de bits para rastrear qué bloques están libres o ocupado      |
|  Es posible definir multiples flujos de datos para un unico fichero      | Soporte de metadatos para sistemas grandes |
|  Soporte avanzado para seguridad y permisos (ACL)                     | Mecanismos para prevenir corrupción (journaling)        |
| B+ Trees para búsquedas rápidas                          | En los inodos (permiso Unix, extendidos)                            |

__Sistema NTFS__
Ventajas:
* Los metadatos muestran claramente con qué programa puede abrirse un archivo
* No es necesario indicar la extensión del archivo
* Con la información de todos los metadatos se registra un diario o journal, con las que se pueden evitar incoherencias
* También es compatible con cifrado de archivos mediante EFS (Encrypting File System).
* Incluye características de tolerancia a fallos, como el registro de transacciones y la restauración automática

Desventajas:
* Aunque Linux y macOS pueden leer NTFS y, en algunos casos, escribir en él, la compatibilidad no es tan nativa ni eficiente como en Windows.
* Las funcionalidades avanzadas de NTFS pueden consumir más recursos del sistema
* Los sistemas de archivos NTFS pueden fragmentarse, especialmente a medida que se crean, modifican y eliminan archivos. 

Sistema ext4
Ventajas:
* Ext4 admite tamaños de archivos y particiones significativamente más grandes en comparación con sus predecesores
* Gracias al diario reduce el riesgo de corrupción de datos y garantiza que el sistema de archivos permanezca constante.
* Maneja volúmenes y archivos de hasta 1 exabyte y 16 terabytes, respectivamente
* Permite opciones avanzadas como archivos dispersos (sparse files) y timestamps de alta resolución

Desventajas:
* Con el tiempo, a medida que se crean, modifican y eliminan archivos, puede producirse su fragmentación, lo que disminuye el rendimiento
* Sistemas operativos como Windows no soportan ext4 de forma nativa, requiriendo herramientas o controladores externos
* Aunque es más resistente a fallos, la recuperación de datos en caso de corrupción de bloques o metadatos puede ser difícil 

## Ejercicio 3: Organización lógica y física de archivos
Un ejemplo de organizacion logica de directorios y subdirectorios puede ser:

![Diagrama jerarquico](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Listar_disp_conectados/diagrama%20directorios.jpg?raw=true)

Para la traducción de direcciones hay que dar los siguientes pasos: 
* Obtener el número de página de los n bits más significativos de la dirección lógica. 
* Emplear el número de página como índice en la tabla de páginas del proceso para encontrar 
el número de marco k. 
* El comienzo de la dirección física del marco es k x 2m y la dirección física del byte referenciado es este número más el desplazamiento. No hace falta calcular esta dirección física, sino que se construye fácilmente concatenando el número de marco con el desplazamiento.

Un ejemplo practico podria ser:
__Creación del archivo:__ Cuando creamos el archivo documento.txt, el sistema operativo asigna un nombre a este archivo en el sistema de archivos.
__Asignación de bloques:__ Dado que el archivo documento.txt tiene un tamaño de 100 KB y el sistema de archivos utiliza bloques de 4 KB, el archivo se divide en varias partes
__Almacenamiento:__ El contenido del archivo documento.txt se divide en fragmentos y se escribe en los bloques físicos. Los primeros 4 KB del archivo se escriben en el bloque físico 101, los siguientes 4 KB se escriben en el bloque físico 102, y así sucesivamente hasta que todos los bloques del archivo se han escrito en los bloques físicos.
__Actualización del inodo:__ El inodo del archivo documento.txt se actualiza para reflejar el número total de bloques utilizados, los punteros a cada uno de los bloques físicos asignados
__Acceso al archivo:__ El sistema usa los punteros en el inodo para localizar y leer los datos del archivo en los bloques físicos.

Estructura en disco:
| **Bloque Lógico**                         | **Bloque Físico**          | **Contenido**|
|:---------------------------------------:|----------------------:|----------------------:|
|  1            | 101   | Datos del archivo|
|  2            | 102   | Datos del archivo|
|  ...          | ...   | ...|
| 25            | 125   | Datos del archivo|

Inodo:
| **Bloque Lógico**                | **BloqueFísico**          
|:--------------------------------:|----------------------:|
|  Tamaño del archivo            | 100 kb   |
|  Numero de bloques            | 25   | 
|  Puntero a bloque 1          | Bloque fisico 101   | 
| Puntero a bloque 2            | Bloque fisico 102   | 
| ...            | ...   | 
|  Puntero a bloque 25          | Bloque fisico 125   |

## Ejercicio 4: Mecanismos de acceso a los archivos
Existen diferentes mecanismos de acceso a los archivos, como lo son los accesos secuencial, directo e indexado.
__Acceso secuencial:__ Es la capacidad de introducir datos en un dispositivo de almacenamiento o un soporte de datos en la misma secunecia en la que estaban ordenados los datos, o de obtenerlos en el mismo orden en el que se introdujeron.

Abrimos el archivo en un punto, y las lecturas/escrituras sucesivas se van realizando a partir del último punto en el que nos quedamos. Abrimos el archivo en un punto, y las lecturas/escrituras sucesivas se van realizando a partir del último punto en el que nos quedamos. Es el modelo básico de Unix y Windows (open --> read --> read --> …)

__Acceso directo:__ Es la capacidad de obtener datos o introducir datos en un dispositivo de almacenamiento en una secuencia independiente de su posición relativa, a través de direcciones que indican la ubicacioni física de los datos.

Cada operación de lectura/escritura indica la posición dentro del archivo sobre la que se quiere trabajar. En Unix, se implementa con lseek().

__Acceso indexado:__ Es perteneciente a la organizacion y acceso de los registros de una estructura de almacenmiento, a través de un índice de las claves que se almacenan en ficheros secuenciales arbitrariamente patrocinados.

El fichero consiste en una tabla con registros, ordenados según una clave (ej. fichas de personas ordenadas por apellidos o DNI).

Cada operación de lectura se puede hacer buscando por clave, o por número de orden. Cada operación de escritura mantiene el fichero bien ordenado.

El SO asocia a cada fichero una o varios ficheros índices para mantener la ordenación de forma eficiente. Estos índices están ocultos al usuario.

Pseudocodigo de acceso secuencial:
~~~
Inicio
Abrir (archivo)
Mientras haya datos en archivo:
    Leer (archivo)
Cerrar (Archivo)
Fin
~~~

Pseudocodigo de acceso directo:
~~~
Inicio 
Abrir (archivo.doc)
Escribe la pagina del archivo a la que quieres ir
>> 10
Ir a la Posicion de la pagina "10" del archivo
Leer datos del archivo
Cerrar (Archivo.doc)
Fin
~~~

Pseudocodigo de acceso indexado:
~~~
Abrir (Archivo.doc)
Abrir indice del archivo 
Indice = {"Capitulo 1", "Capitulo 2", "Capitulo 3"}
Selecciona un capitulo
Posicion =  "Capitulo 1"
Leer desde Posicion
Cerrar (Archivo.doc)
Fin
~~~

| **Secuencial**                         | **Directo**          | **Indexado**|
|:---------------------------------------:|----------------------:|----------------------:|
|  Eficiente para archivos pequeños            | Util para archivos mas grandes   |Ideal para archivos grandes o complejos |
|  Util para registro continuo            | Acceso a posiciones especificas   | Acceso rapido sin recorrer todo el archivo|
|  Sencillo de usar| Flexibilidad en el orden de escritura/lectura   | Util en archivos jerarquicos|


## Ejercicio 5: Modelo jerárquico y mecanismos de recuperación en caso de falla

Modelo jerarquico ejemplo
![Modelo jerarquico de sistema de archivos]()