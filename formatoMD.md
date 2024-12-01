# Repositorio Sistemas Operativos
### 3.1 Política y filosofia
###### 1. ¿Cuál es la diferencia entre fragmentación interna y externa?
La __fragmentación interna__ ocurre cuando un bloque de memoria es más grande que el tamaño solicitado y se desperdicia el exceso de espacio.
Por ejemplo: digamos que un asignador solo puede proporcionar memoria en fragmentos de 4 bytes. Si un programa solicita 29 bytes de memoria, en realidad recibirá una porción de 32 bytes. Dado que el programa utiliza sólo 29 de los 32 bytes disponibles, los 3 bytes sobrantes de memoria se desperdician.

Esta memoria que no se usa, queda inservible para otros procesos y limita la cantidad que se pueden ejecutar al mismo tiempo. Ya que reduce la memoria funcional óptima. Esto puede aumentar el tiempo de procesamiento ya que debe buscar un bloque adecuado para reducir la fragmentación.

La __fragmentación externa__ ocurre cuando hay espacios entre los bloques asignados y la memoria no se puede usar para solicitudes más grandes. 
Por ejemplo: digamos que el asignador asigna varios bloques de memoria en una línea continua. Si uno de los bloques intermedios se libera porque el proceso que lo estaba usando dejó de ejecutarse, el bloque libre se fragmenta.

Esto hace que solo se pueda usar ese bloque aislado solo si hay una solicitud que quepa dentro, pero no puede usarse para solicitudes de memoria mayores. Y no puede unirse como los bloques libres.

Entonces la __fragmentación interna__ ocurre dentro del espacio del bloque que se solicita, mientras que la __fragmentación externa__ ocurre en los bloques contiguos o espacios entre los bloques.


######  2. Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?
Las __políticas de reemplazo de páginas__ son algoritmos utilizados en sistemas operativos para decidir qué página en la memoria debe ser reemplazada cuando se necesita liberar espacio para cargar una nueva página.

Una página es una unidad de memoria fija en la que se divide el espacio de direcciones de un proceso. Cada página puede tener un tamaño de 4 KB, 8 KB o más, dependiendo de la arquitectura del sistema.

La memoria física (RAM) se divide en bloques de tamaño fijo llamados marcos de página, que son del mismo tamaño que las páginas.

Hay varios algoritmos de reemplazo de páginas, cada uno con sus propias características y estrategias:

1. __FIFO (First-In, First-Out)__: Este algoritmo reemplaza la página más antigua en la memoria. Se usa una cola, al cargar una página nueva se ingresa en el último lugar. Aunque las colas FIFO son simples e intuitivas, no se comportan de manera aceptable en la aplicación práctica, por lo que es raro su uso en su forma simple. 

Una desventaja es la anomalía Belady, consiste en que podemos quitar de memoria una página de memoria muy usada, solo porque es la más antigua.

2. __LRU (Least Recently Used)__: Reemplaza la página que no ha sido utilizada durante el periodo más largo de tiempo. Este algoritmo utiliza la idea de que las páginas que han sido accedidas recientemente tienen más probabilidad de ser accedidas nuevamente en el futuro.

La desventaja es que gasta recursos para rastrear el orden de uso de las páginas.

3. __Optimal__: Este es un algoritmo teórico que reemplaza la página que no será utilizada por el mayor periodo de tiempo en el futuro.  Para esto el sistema operativo debería ver en cuánto tiempo será usada cada página en memoria y elegir la que está más distante.

El problema de este método es que necesita conocimiento del futuro, por lo que es difícil de implementar.

4. __Algoritmo de reloj__: Es una variación de FIFO que utiliza un "bit de referencia" para decidir qué páginas reemplazar. En caso de estar fijado (en 1) se cambia el bit a 0 y se lo coloca al final de la obstrucción, actualizando su tiempo de carga como si recién hubiera llegado al procesador. De esta forma, se le da una segunda oportunidad. Si el bit se encuentra sin fijar(en 0), la página se saca de memoria.

La desventaja es que en algunos casos suele ser menos precisa que LRU.

5. __NRU (Not Recently Used)__: Cuándo una página es referenciada, fija el bit de referencia para esa página. Similarmente, cuando una página es modificada, fija su bit de modificación.
Cuando una página debe ser reemplazada, el sistema operativo divide las páginas en cuatro categorías:
    * Categoría 0: No referenciada, No modificada
    * Categoría 1: No referenciada, modificada
    * Categoría 2: referenciada, No modificada
    * Categoría 3: referenciada, modificada

Las mejores páginas para cambiar son las que se encuentran en la categoría 0, mientras que las peores son las de la categoría 3.
En algunos casos es más óptimo LRU o reloj.

El más eficiente podría ser el optimal, pero solo de forma teórica ya que es el más difícil de llevarlo a la practica, asi que yo elegiría LRU como el más eficiente, ya que aunque puede gastar más recursos que otros algoritmos, es el que mejor referencia el estado de las páginas en los sistemas para ser reemplazados.

### 3.2 Memoria real 
###### 1.Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas.
###### 2. Diseña un algoritmo para calcular qué procesos pueden ser asignados  a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida".

Para el programa se uso como base el codigo compartido por el profesor en la seccion de Administraciono de memoria en las respuestas del ejercicio. El codigo simula la administracion de memoria con particiones fijas al preguntarle al usuario el tamaño de la memoria y el numero de particiones que quieres.
~~~
int main(){
    int memoria_total, particiones, opcion, tamano_particion = 0;
    Particion particion[max_particiones];

    printf("Ingresa el tamaño de la memoria: \n");
    scanf("%d", &memoria_total);

    printf("Ingresa el numero de particiones: \n");
    scanf("%d", &particiones);
~~~

El usuario le asigna el tamaño a cada particion, luego puede asignar un proceso a cada particion mientras cumpla con los requisitos de tamaño, el codigo tambien utiliza la primera cabida ya que recorre el arreglo de particion para ver cual cumple con el tamaño indicado en la asignacion del proceso, la primera particion que encuentre que cumpla los requisitos le asigna el proceso.

~~~
int asignado = 0;
for (int i = 0; i < particiones; i++) {
    if (particion[i].id_de_proceso == -1 && particion[i].tamano >= tam_proceso) {
        particion[i].id_de_proceso = id_de_proceso;
        asignado = 1;
        printf("Proceso %d asignado a la partición %d.\n", id_de_proceso, i + 1);
        break;
        }
}
if (!asignado) {
    printf("No se encontró una partición disponible para el proceso %d.\n", id_de_proceso);
}
break;
~~~

### Organizacion de memoria virtual
###### 1. Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?

La __paginación__ es una estrategia de organización de la memoria física que consiste en dividir la memoria en porciones de igual tamaño. A dichas porciones se las conoce como páginas físicas o marcos. La división de la memoria en páginas facilita la gestión de la memoria física. Los marcos se identifican con un número que se denomina «número de página física. A su vez, cada página física se asigna a un proceso de forma exclusiva.

Tanto el tamaño de las páginas como de los marcos de páginas es definido por el hardware y suele ser una potencia de 2. Permite que las páginas de un proceso puedan cargarse en cualquier marco de página disponible, sin necesidad de que estén contiguos en la memoria.

El sistema operativo mantiene una tabla de páginas para cada proceso, que mapea cada página lógica a su marco físico correspondiente. Esta tabla se utiliza para traducir las direcciones lógicas (del proceso) a direcciones físicas (de la memoria). Cuando el proceso necesita acceder a una dirección lógica, el traductor de memoria paginada toma la dirección lógica y, por medio de la tabla de página, obtiene la dirección física real.

Ejemplo:
Supongamos un tamaño de página de 4 KB. Un proceso tiene 16 KB de memoria lógica, dividido en 4 páginas. La memoria física tiene 8 marcos disponibles.
Las páginas del proceso se asignan a marcos libres como sigue:
![Tabla de paginacion](https://github.com/DavidMB4/Graficacion/blob/master/Actividad1Transformaciones/pokeball.png?raw=true)

La tabla de páginas almacenará esta información. Cuando el proceso necesita acceder a una dirección lógica, se consulta esta tabla para determinar su ubicación física.

__Ventajas:__
* Fácil de usar gestión de la memoria algoritmo
* No hay necesidad de fragmentación externa
* El intercambio es fácil entre páginas y marcos de página del mismo tamaño.

__Desventajas:__
* Puede causar fragmentación interna.
* Las tablas de páginas consumen memoria adicional.
* La paginación multinivel puede generar una sobrecarga de referencia de memoria.


__La segmentación__ es una técnica que asigna segmentos contiguos de memoria para las áreas de memoria de un proceso. De esta forma, logra acomodarse más a la visión de la memoria por parte del usuario. Un segmento de programa representa su parte lógica e incluye la función principal del programa, las estructuras de datos, las funciones de utilidad, etc. Cada segmento tiene un nombre y una longitud.

El sistema operativo mantiene una tabla de mapas de segmentos para todos los procesos. También incluye una lista de bloques de memoria libres junto con su tamaño, números de segmento y ubicaciones de memoria en la memoria principal o memoria virtual.

Las direcciones virtuales se componen de un número de segmento y el desplazamiento dentro del segmento. El desplazamiento debe ser menor que el largo asociado al segmento.

Cada segmento puede asignarse en cualquier parte de la memoria física.
La segmentación no requiere que los segmentos sean contiguos en memoria física.

Ejemplo:
Supongamos que un programa tiene las siguientes secciones:
![Tabla de segmentacion](https://github.com/DavidMB4/Graficacion/blob/master/Actividad1Transformaciones/pokeball.png?raw=true)

Si se usa segmentación, cada sección se asigna a un segmento diferente. Una dirección lógica en el segmento 1 (código) con un desplazamiento de 500 se traduce a una dirección física en la memoria donde ese segmento está cargado.


__Ventajas:__
* Ofrecer protección dentro de los segmentos.
* Puede lograr compartir segmentando y haciendo referencia a múltiples procesos.
* No ofrece fragmentación interna.
* Las tablas de segmentos usan menos memoria que la paginación

__Desventajas:__
* En el método de segmentación, los procesos se cargan o eliminan de la memoria principal. Por tanto, el espacio libre de memoria se separa en pequeños trozos, lo que puede crear un problema de fragmentación externa.
* Algoritmo costoso de gestión de memoria
