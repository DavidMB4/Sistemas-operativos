# Actividad final

# Sistemas de archivos
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

![Diagrama jerarquico](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Listar_disp_conectados/diagrama%20directorios.jpeg?raw=true)

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
![Modelo jerarquico de sistema de archivos](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Listar_disp_conectados/jerarquia%20directorios.jpeg?raw=true)
Representa la forma en que estan distribuidos la jerarquia en los archivos de unix/linux. Tiene __/bin__ que es donde estan los ejecutables esenciales que el usuario o el sistema necesita para funcionar de forma correcta.
__/home__ que es donde se guardan las carpetas personales del usuario.
__/lib__ que contiene bibliotecas esenciales compartidas por los programas en /bin y /sbin.

Ejemplo de simulacion:
Si un directorio en un sistema Linux sufrió una falla debido a corrupción de datos. Los archivos en este directorio ya no son accesibles.
Se vereficia el directorio con 
````Bash
ls /proyectos
````
Si devuelve un error como "Input/output error", indica que hay un problema en el sistema de archivos. Para evitar más daños, montar el sistema de archivos en modo de solo lectura.
````Bash
mount -o remount,ro /dev/sdX
````
Donde /dev/sdX es el disco donde se encuentra el directorio /proyectos.

Se puede usar herramientas como fsck para analizar y reparar el sistema de archivos:
````Bash
fsck /dev/sdX
````
Si fsck no soluciona el problema, usar herramientas de recuperación de datos como testdisk o photorec para recuperar los archivos.
````Bash
testdisk /dev/sdX
````
Si se tenía configurada una copia de seguridad automatizada, restaurar el directorio desde ella con:
````Bash
rsync -av /backup/proyectos /proyectos
````

Si no hay respaldo, usar herramientas como grep o strings en el disco afectado para intentar recuperar fragmentos de texto o archivos importantes. Esto es útil para rescatar datos parciales.
````Bash
grep -a "contenido" /dev/sdX
````


Existen diferentes formas y herramientas para respaldar información.
* Se puedes utilizar el uso de discos duros (HDD) o discos de estado solido (SSD) como una unidad externa para almacenar informacion importante, pero necesitan ser actualziadas constantemente.
* Tambien es utilizar el servidores en la nube como Drive para almacenar los datos a traves de la conexion a internet. Este tipos de guardado puede programarse para hacer resplados cada cierto tiempo de forma frecuente.
* Se puede usar un __Backup completo__ crea una copia completa de todos los datos de un sistema, aunque un respaldo complelto no requiere tanto esfuerzo, puede haber mas adelante problemas de redundancia, y para el medio de respaldo requiere una gran cantidad de espacio.
* Un __Backup diferencial__ contiene todos los datos que han cambiado desde la última copia de seguridad completa. La cantidad de datos que se deben guardar depende del tiempo transcurrido desde el ultimo backup.  una copia de seguridad diferencial es mucho más pequeña y, por tanto, más rápida de crear que otra copia de seguridad completa. 
Para restaurar los datos, se necesita el backup diferencial y el último backup completo. 
* En un __Backup incremental__ se hace una copia de seguridad de los cambios realizados desde el último backup completo o incremental. Estos backups no son independientes unos de otros. Para ser restaurados se necesitan todas las copias de seguridad incrementales desde la última copia de seguridad completa. 
Si un backup incremental de la cadena se daña, todos los backups incrementales posteriores carecen de valor.


# Protección y Seguridad
## Ejercicio 1: Concepto y objetivos de protección y seguridad
La protección es un método que limita el acceso de programas, procesos o usuarios a los recursos definidos por un sistema informático. La protección se puede utilizar para permitir que varios usuarios compartan de forma segura un espacio de nombres lógico común, como un directorio o archivos, en sistemas operativos de programación múltiple.

La seguridad en sistemas operativos se refiere a la capacidad de un sistema para proteger sus recursos, datos y funcionalidades contra amenazas internas y externas, y garantizar la integridad, disponibilidad y confidencialidad de la información

Los mecanismos de protección en un sistema operativo sirven para varios objetivos:
* __Confidencialidad:__ Asegurar que la información confidencial sea accesible solo para usuarios o procesos autorizados.
* __Integridad:__ Garantizar que los datos permanezcan inalterados y confiables a lo largo de su ciclo de vida.
* __Disponibilidad:__ Asegurar que los recursos y servicios estén disponibles y accesibles para los usuarios autorizados cuando sea necesario.
* __Aislamiento:__ Prevención de interferencias y acceso no autorizado entre diferentes procesos, usuarios o componentes.
* __Auditabilidad:__ Proporcionar mecanismos para rastrear y monitorear las actividades del sistema para detectar e investigar incidentes o violaciones de seguridad.

La seguridad y protección en los sistemas operativos son aspectos fundamentales para garantizar la integridad, confidencialidad y disponibilidad de la información.

Ejemplo de uso de objetivos en sistemas operativos:
En una empresa tiene un archivo que contiene informacion confidencial sobre las nominas de los empleados, este archivo debe de poder ser accedido solo por Recursos humanos.
En windows se peude configurar el permiso para el archivo usando el sistema de permisos NTFS, estos son permisos que deciden y definen qué acciones pueden realizar los usuarios en carpetas y archivos, tanto localmente como también a través de la red, esto le puede dar permisos de lectura y escritura a Recursos humanos sin contar a los demas empleados que usan el sistema.
Tambien se puede garantizar que el archivo no se modifique de manera no autorizada o accidental, al activar registros de auditoría (event logs) para monitorear cambios en el archivo. Si alguien intenta modificar "nominas.xlsx" sin permisos, el sistema genera un evento en el registro de seguridad.
Tambien podria necesitarse configurar el historial de archivos para crear copias automáticas del archivo. Esto Asegura que el archivo esté accesible cuando los usuarios autorizados lo necesiten.

## Ejercicio 2: Clasificación aplicada a la seguridad
La seguridad del sistema operativo se puede clasificar como:
* __Seguridad de software(logica):__ Los sistemas operativos son los más vulnerables a los diferentes tipos de ataques que existen, que pueden llegar a causar daños desde el funcionamiento del dispositivo hasta el robo de información. La seguridad del software es la que se encarga de proteger estos sistemas y los programas de aplicación. Además, también se encarga de proteger al software de amenazas exteriores como virus o ataques maliciosos.

    El mecanismo estrella de este tipo de seguridad son los programas antivirus, que disponen de un archivo de virus que se actualiza regularmente y es capaz de encontrar nuevos virus.

    Por medio del cifrado de datos puede protege la información almacenada en el sistema operativo para evitar robo o manipulación.

    Ejemplos:
    * En Windows Se pueden aplicar permisos a archivos y carpetas, cifrar discos con BitLocker y usar un antivirus.
    * En Linux Se utilizan mecanismos como permisos con chmod, listas de control de acceso (ACL) y herramientas como SELinux para reforzar la seguridad.

* __Seguridad de Hardware(fisica):__ Los sistemas de seguridad de hardware son los que aportan el mayor nivel de protección frente a los ciberataques. Se centran en la protección de los ordenadores o dispositivos frente a amenazas o intromisiones. 

    Los mecanismos más comunes de protección de hardware son los cortafuegos de hardware o firewalls y servidores proxy, que se utilizan para controlar el tráfico de red. También existe otra herramienta denominada módulos de seguridad de hardware (HSM) que se encargan del suministro de claves encriptadas para diferentes sistemas.

    La seguridad física incluye medidas como respaldos en sitios seguros, protección contra incendios, inundaciones, y otros desastres naturales.

    Ejemplos:
    En un centro de datos, los servidores que ejecutan sistemas operativos como Linux o Windows Server están protegidos con:
    * Cámaras de vigilancia.
    * Tarjetas de acceso personal (Tarjetas RFID, Identificación Biométrica).
    * Sistemas de refrigeración y control de incendios.

* __Seguridad de red:__ La seguridad de red informática es la que se encarga de la protección de los datos y la información de una red de ordenadores contra accesos no autorizados. Es decir, toda la información que está accesible a través de Internet (datos bancarios, datos personales, documentos, etc.).

    También se refiere a la protección de la red contra ataques externos e internos que puedan comprometer la seguridad de la información. En este sentido, este sistema se encarga de prohibir a usuarios ajenos acceder a nuestra información privada.

    Previene ataques como el acceso remoto no autorizado, denegación de servicio (DoS), y ataques de intermediario (MITM).

    Puedes usar protocolos como SSL/TLS que garantizan que los datos enviados y recibidos por el sistema operativo no puedan ser interceptados.

    Ejemplos:
    * En un servidor con Windows o Linux, se configura un firewall (por ejemplo, iptables en Linux o Windows Firewall) para bloquear tráfico no autorizado.
    * Se utiliza VPN para proteger conexiones remotas y protocolos seguros como SSH en lugar de Telnet para administración remota.
    * Uso de un IDS/IPS en un firewall o como una solución integrada en el sistema operativo

## Ejercicio 3: Funciones del sistema de protección
Un sistema de proteccion puede controlar el acceso a los recursos por medio de estas funciones:
__1. Identificacion de personas o usados:__ Es identificar quién está intentando acceder a un recurso. Esta identificación se realiza mediante credenciales (como nombres de usuario y contraseñas)
__2. Autenticacion:__ Una vez que un usuario o proceso se ha identificado, se necesita verificar su identidad para asegurarse de que es quien dice ser.
__3. Autorización:__ Aquí, el sistema decide si el usuario o proceso tiene permiso para realizar la acción solicitada sobre el recurso.
__4. Control de Acceso a la Memoria:__ El sistema operativo también puede controlar el acceso a la memoria de la máquina. Por ejemplo, puede prevenir que un proceso acceda a la memoria de otro proceso sin autorización, protegiendo así la integridad y privacidad de los procesos.
__5. Auditoría y Monitoreo:__ El objetivo es registrar y analizar todas las acciones realizadas sobre los recursos.
__6. Prevención de Accesos No Autorizados:__ Para evitar accesos no autorizados, los sistemas operativos emplean varias técnicas como Firewalls, cifrado o Control de acceso basado en atributos (ABAC).

Las funciones principales son la autenticacion, la autorizacion y la auditoria.
La __autenticación__ es el proceso de verificación de la identidad de un usuario, dispositivo o proceso que intenta acceder a un sistema. Su objetivo es asegurar que la entidad es quien dice ser. Generalmente se realiza mediante credenciales, como contraseñas, tarjetas inteligentes o biometría. La autenticación establece la confianza inicial entre el usuario y el sistema, y es fundamental para evitar accesos no autorizados. 
Ejemplo: Un usuario ingresa su contraseña para iniciar sesión en un sistema operativo.

La __autorizacin__ ocurre después de la autenticación y tiene como propósito controlar el acceso a los recursos del sistema según los permisos y privilegios del usuario. Una vez autenticado, el sistema determina qué acciones puede realizar el usuario, como leer, escribir o ejecutar archivos, según las políticas de acceso previamente definidas. Este proceso asegura que los usuarios solo tengan acceso a los recursos que les han sido específicamente asignados.
Ejemplo: Después de autenticarse, un usuario puede tener acceso solo a ciertos archivos y no a todos los del sistema.

La __auditoria__ es el proceso de registro y monitoreo de las actividades realizadas en un sistema. Esto incluye identificar quién accede a qué recursos, qué operaciones realiza (como lectura, escritura, eliminación), y cuándo ocurre el acceso. Los registros de auditoría son esenciales para detectar comportamientos sospechosos, violaciones de seguridad y para realizar un seguimiento en caso de incidentes. Además, permiten a los administradores del sistema revisar y analizar el uso del sistema para garantizar el cumplimiento de políticas de seguridad.
Ejemplo: Los logs del sistema registran el intento de acceso de un usuario no autorizado a un archivo restringido.

Ejemplo de uso de las funciones:
Una empresa implementa un sistema de protección para garantizar que solo los usuarios autorizados puedan acceder a esta información y para mantener un registro de todas las actividades.
El primer paso por el que pasa es la autenticación, aqui el sistema verifica las credenciales del empleado que intenta acceder con la base de datos interna. Si las credenciales son correctas, el sistema permite que el empleado acceda al sistema, si la contraseña es incorrecta, el sistema rechaza el acceso y registra un intento fallido. Esto asegura que solo las personas con credenciales válidas puedan acceder al sistema.

La siguiente parte seria la autorización, el sistema verifica los permisos del empleado y le presenta solo los recursos y herramientas a los que tiene acceso, por ejemplo podrian ser los estados financieros de los clientes y los balances. Si el empleado intenta acceder a una sección restringida, como la configuración de usuarios, el sistema le muestra un mensaje de "Acceso denegado". Esto garantiza que el empleado solo pueda acceder y modificar la información para la cual tiene permisos, protegiendo otros datos sensibles del sistema.

En la auditoria cada acción realizada por el empleado es registrada en los logs del sistema.
Si se detecta un intento de acceso no autorizado, el sistema genera una alerta en el panel de administración. El administrador del sistema revisa los registros de auditoría para identificar qué ocurrió, cuándo y quién intentó acceder sin autorización. Esto permite la determinar la responsabilidad de las acciones en el sistema, detectar actividades sospechosas o violaciones de seguridad, y tener un historial completo de las operaciones para análisis futuros.

## Ejercicio 4: Implantación de matrices de acceso
Una matriz de acceso es una forma de representar qué operaciones pueden realizar diferentes usuarios sobre ciertos recursos en un sistema. Esto, con el objetivo de proteger la información crítica y confidencial que puede verse en riesgo si no se limita, documenta, comunica ni controla formalmente.

Ejemplo de matriz de acceso:
| **Usuario**        | **Recurso 1** | **Recurso 2** | **Recurso 3** | **Recurso 4**|
|:------------------:|--------------:|--------------:|--------------:|-------------:|
|  Usuario 1         |Leer y escribir|  No permitido |Leer           |Escribir      |
|  Usuario 2         |Leer           |Leer y escribir|No Permitido   |Leer          |
|  Usuario 3         |No permitido   |  Permitido    |Leer y escribir|Leer          |

Aqui muestra que existen 3 usuarios cada uno tiene acceso a los diferentes recursos que hay, pero hay recursos a los que no tienen acceso, asi como hay algunos en los que pueden hacer las 2 operaciones y otros en donde solo pueden hacer uno. Esto es util ya que por ejemplo en un sistem operativo es importante determinar que elementos puedesn manejar los archivos criticos de este sistema, asi evitar errores en el futuro. 

Ejemplo de simulacion:
En este codigo se define la matriz que ya se habia hecho.
~~~
matriz_acceso = [
    #Filas son usuarios, columnas son recursos
    [3, 0, 1, 2],  # Usuario 1
    [1, 3, 0, 1],  # Usuario 2
    [0, 3, 3, 1],  # Usuario 3
]
~~~
Filas siendo usarios del 1 al 3, y columanas siendo los recursos del 1 al 4.

Se definen despues los recursos que hay en la matriz, siendo un numero diferente a 0 alguna operacion.
~~~
# Valores de la matriz
permisos = {
    3: "Lectura y escritura",
    2: "Escritura",
    1: "Lectura",
    0: "No permitido"
}
~~~

Se muestra el menu para seleccionar el usuario que va a entrar y el recurso al que se desea acceder.
~~~
print("Sistema de control de acceso")
usuario = int(input("Introduce el id del usuario (1-3): ")) - 1
recurso = int(input("Introduce el id del recurso (1-4): ")) - 1
~~~

Se valida los datos que entraron, si hay un 0 en la posicion donde se seleccione al usuario y el recurso significa que no tiene acceso, sino, se mostrara la operacion que puede hacer con el recurso.
~~~
if 0 <= usuario < 3 and 0 <= recurso < 4:
    permiso = matriz_acceso[usuario][recurso]
    
    if permiso == 0:
        print(f"Acceso denegado: Usuario {usuario + 1} no tiene permisos para el Recurso {recurso + 1}.")
    else:
        print(f"Acceso permitido: Usuario {usuario + 1} puede realizar la operación '{permisos[permiso]}' en el Recurso {recurso + 1}.")
else:
    print("Entrada inválida. Por favor, introduce los id válidos para usuario y recurso.")
~~~

Ahora una prueba con el usuario 1 y el recurso 2.
````Bash
Sistema de control de acceso
Introduce el id del usuario (1-3): 1
Introduce el id del recurso (1-4): 2
Acceso denegado: Usuario 1 no tiene permisos para el Recurso 2.
````
Como el usuario 1 no puede hacer nada con el recurso 2, aparece este mensaje.
Ahora probando con el usuario 2 y el recurso 1.
````Bash
Sistema de control de acceso
Introduce el id del usuario (1-3): 2
Introduce el id del recurso (1-4): 1
Acceso permitido: Usuario 2 puede realizar la operación 'Lectura' en el Recurso 1.
````
Como si peude acceder aparece las operaciones que peude realizar, en este caso Lectura.

## Ejercicio 5: Protección basada en el lenguaje
La protección basada en el lenguaje refiere a técnicas que utilizan constructos de programación para prevenir ataques. Esto incluye enfoques como la verificación de tipos y el manejo seguro de memoria, que limitan las vulnerabilidades en las aplicaciones. ayuda a prevenir la ejecución de código malicioso. Al imponer restricciones en la manipulación de datos, protege la memoria y evita exploitaciones de vulnerabilidades.

 Un ejemplo de esto puede ser Java, Java garantiza la seguridad de la memoria y evita accesos no autorizados. A diferencia de C o C++, Java no permite a los desarrolladores manipular directamente punteros de memoria, esto evita problemas como desbordamiento de búfer o accesos a áreas no autorizadas de la memoria.
 En una maquina virtual Java tambien puede manejar la asignación y liberación de memoria automáticamente, evita problemas como fugas de memoria o el uso de memoria ya liberada (errores de dangling pointers).
 Antes de ejecutar el código, la JVM verifica el bytecode para asegurar que cumple con las reglas de acceso a memoria y tipos.

 | **Basada en lenguaje**                | **Protección en sistemas operativos**          
|:--------------------------------:|----------------------:|
|  Lenguajes de programación (software)        | Kernel del sistema operativo (hardware y software)  |
|  Evita errores como desbordamientos y punteros          | Utiliza la MMU y protección de memoria virtual   | 
|  Controla el acceso con encapsulamiento, restricciones de variables          |Controla el acceso por medio de permisos de archivos, privilegios de procesos   | 
| No aplica auditoria y monitoreo directamente            | Implementa monitoreo con logs y sistemas de auditoría   | 
| La vereficacion se hace en el tiempo de compilacion como RUST o de ejecución como en Java     | Generalmente se hace la verificacion en el tiempo de ejecución   | 

## Ejercicio 6: Validación y amenazas al sistema
El sistema operativo tiene diferentes tipos de amenazas, las mas comunes son:
* __Fuerza bruta:__ Es una ataque en el que se prueben todas las claves posibles en una búsqueda exhaustiva, Por ejemplo, en sistemas de cifrado de 56 bits, un atacante intentará descifrar un texto cifrado probando cada clave posible hasta que el resultado sea inteligible. Este ataque es costoso en tiempo y recursos, pero es efectivo si no existen medidas de protección, como límites en intentos de autenticación o uso de algoritmos robustos.
* __Malware:__ Es una categoría de códigos maliciosos que incluyen virus,  troyanos, o spyware, usan medios y herramientas de comunicación populares para extenderse, incluyendo gusanos enviados a través de e-mails, troyanos que entran a través de páginas Web y archivos infectados por virus descargados en conexiones directas entre usuarios. Tienen la capacidad de corromper los archivos que haya guardado en el disco duro o incluso destruir determinados archivos.
* __Inyección de codigo:__ En este tipo de ataque, un hacker aprovecha las debilidades de la aplicación para insertar código malicioso en el servidor y así poder robar información confidencial, tomar el control del sistema o realizar otras acciones dañinas

Algunos tipos de mecanismos que se usan contra estas amenazas pueden ser:
* __Autenticación multifactor:__ La autenticación multifactor (MFA) agrega una capa de protección al proceso de inicio de sesión. Cuando se accede a una cuenta o aplicación, los usuarios deben pasar por una verificación de identidad adicional; por ejemplo, tienen que escanear su huella digital o especificar un código que reciben en su teléfono.
* __Control de integridad:__ Es un mecanismo que asegura que los datos y archivos no hayan sido alterados de manera no autorizada durante su almacenamiento, transmisión o procesamiento. Su objetivo principal es garantizar que la información sea consistente, precisa y confiable
* __Tokens:__ Son dispositivos fisicos o digitales que generan códigos únicos (tokens) para validar la identidad del usuario. Pueden ser llaves USB que deben conectarse al sistema, o tambien aplicaciones como Google Authenticator.

Esquema de validacion para un sistema con multiples usuarios:
![Validacion de sistema operativo con multiples usuarios](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Listar_disp_conectados/Validacion%20de%20usuario.jpeg?raw=true)

## Ejercicio 7: Cifrado
Cifrado es el proceso de transformar texto sin formato legible en texto cifrado ilegible para enmascarar información confidencial de usuarios no autorizados.
El __cifrado asimétrico__, también conocido como criptografía de clave pública o criptografía asimétrica, es uno de los dos métodos principales de cifrado junto con el cifrado simétrico. El cifrado asimétrico funciona creando un par de claves, una pública y otra privada. Cualquiera puede usar una clave pública para cifrar datos. Sin embargo, solo los titulares de la clave privada correspondiente pueden descifrar esos datos.
El __cifrado simétrico__ funciona mediante la creación de una única clave compartida para cifrar y descifrar datos confidenciales. El principal beneficio del cifrado simétrico es que generalmente es simple y eficiente para proteger los datos. 

Ejemplos:
Un sistema operativo utiliza cifrado simétrico para proteger un archivo sensible, como un archivo de configuración con credenciales o claves de API. El sistema operativo genera una clave secreta única para el usuario o proceso, Esta clave se almacena en un área segura del sistema, como un módulo de seguridad (TPM o HSM).
Cuando el archivo necesita ser protegido, se cifra con AES usando esta clave secreta, para acceder al archivo, el sistema lo descifra con la misma clave secreta. 

Un sistema operativo implementa cifrado asimétrico para asegurar la transferencia de datos en red, como en una conexión SSH (Secure Shell). Cuando un usuario se conecta al servidor a través de SSH, el servidor envía su clave pública al cliente, el cliente cifra los datos con esta clave publica. 
Solo el servidor, que posee la clave privada correspondiente, puede descifrar estos datos. Una vez establecida la conexión, un cifrado simétrico se utiliza para el resto de la sesión. Herramientas como OpenSSH  utilizan este enfoque para proteger las conexiones remotas.

Este codigo simula el cifrado y descifrado de un arhivo. Para el codigo se uso la dependencia cryptography, para installarlo se usó
````Bash
pip install cryptography
````
~~~
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
~~~
__cryptography.hazmat.primitives.ciphers__ contiene herramientas para trabajar con cifrados como AES. __Cipher__ es la clase principal que permite configurar un cifrado. __algorithms.AES__ especifica el algoritmo AES (Advanced Encryption Standard). __modes.CBC__ se refiere al modo de operación CBC (Cipher Block Chaining). __default_backend__ es el Backend predeterminado que configura las operaciones criptograficas.

Se usan estos datos de entrada
~~~
mensaje = b"Hola, mundo!"  
clave = b"1234567890123456"  
iv = b"abcdefghijklmnop" 
~~~
El __mensaje__ es el texto que se va a cifrar. La __clave__ es la clave que se va a usar para descifrar el texto. El __iv__ es el vector de inicializacion, se usa en modos como CBC para garantizar que el cifrado sea único incluso si el mismo texto y clave se reutilizan, también debe ser de 16 bytes.

~~~
cipher = Cipher(algorithms.AES(clave), modes.CBC(iv), backend=default_backend())
~~~
Aqui se configura un cifrado.
Se usa __algorithms.AES(clave)__ con AES como algoritmo de cifrado con la clave dada. El __modes.CBC(iv)__ Especifica el modo CBC, que usa bloques y requiere un vector de inicialización. Se usa __default_backend()__ que realiza las operaciones criptográficas con Backend.

~~~
cifrador = cipher.encryptor()
mensaje_cifrado = cifrador.update(mensaje.ljust(16)) + cifrador.finalize() 
~~~
Aqui __cipher.encryptor()__ devuelve un objeto para cifrar datos.
En __mensaje_cifrado__ se usa mensaje.ljust(16) que ajusta manualmente el tamaño del mensaje a 16 bytes rellenando con espacios. __cifrador.update(mensaje.ljust(16))__ va cifrar el mensaje ajustado. __cifrador.finalize()__ finaliza el proceso de cifrado y devuelve un bloque restante. Todo esto hace que se devuelva el mensaje cifrado como una secuencia de bytes.

Que despues se puede imprimir el mensaje con un print
~~~
print("Mensaje cifrado:", mensaje_cifrado)
~~~

Ahora se necesita descifrar el mensaje
~~~
descifrador = cipher.decryptor()
mensaje_descifrado = descifrador.update(mensaje_cifrado) + descifrador.finalize()
~~~
Aqui __cipher.decryptor()__ devuelve un objeto para descifrar datos.
Para __mensaje_descifrado__ se usa __descifrador.update(mensaje_cifrado)__ que descifra el mensaje. __descifrador.finalize()__ hace que finalice el proceso de descifrado y devuelve cualquier bloque restante. Esto consigue el mensaje cifrado, incluyendo el relleno.

Por ultimo se imprime el mensaje
~~~
print("Mensaje descifrado:", mensaje_descifrado.strip())
~~~

Resultado:
Cifra primero el mensaje
````Bash
Mensaje cifrado: b'\xc0\x1f\x8c-\x1eV\xd9\\c\xa5\r\xbd.\xa7-\xdf'
````
Despues descifra el mensaje y lo muestra
````Bash
Mensaje descifrado: b'Hola, mundo!'
````