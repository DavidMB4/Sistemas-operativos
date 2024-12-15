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

![Diagrama jerarquico]()