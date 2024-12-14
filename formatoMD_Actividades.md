# Repositorio Sistemas Operativos

### Actividad de contar islas
Se crea la matriz para con 0 en los espacios libre y 1 para determinar las islas.
~~~
int islas[6][8] = {
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,1},
    {0,1,1,0,0,1,0,1},
    {0,1,1,0,0,1,0,1},
    {0,0,0,0,1,1,0,1},
    {0,0,0,0,0,0,0,0}
};
~~~
La funcion contarIslas recorre la matriz y cada ves que encuentre un 1 aumentara el contador de islas y llamara a la funcion eliminar islas.
~~~
int contarIslas (int islas[6][8]){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 8; j++)
        {
            if (islas[i][j] == 1){
                eliminarIsla(islas, i, j);
                contador++;
            }
        }
    }
    return contador;
}
~~~
EliminarIsla usa recursividad para encontrar los 1 de cada isla y eliminarlos colocando un 0, recorre la matriz mientras va encontrando 1, de esta forma si encuentra un 1 verifica o avanza en una direccion hasta que encuentre un 0 en cada llamado recursivo.
~~~
void eliminarIsla(int islas[6][8], int F, int C){
    if (islas[F][C] == 1 && F<6 && C<8){

        islas[F][C] = 0;
        eliminarIsla(islas, F+1, C);
        eliminarIsla(islas, F+1, C+1);
        eliminarIsla(islas, F+1, C-1);
        eliminarIsla(islas, F-1, C);
        eliminarIsla(islas, F-1, C+1);
        eliminarIsla(islas, F-1, C-1);
        eliminarIsla(islas, F, C+1);
        eliminarIsla(islas, F, C-1);
    }

    return ;
}
~~~
Finalmente termina de eliminar la isla y continua con el for hasta volver a encontrar un 1.
Codigo completo:
~~~
#include <stdio.h>
#include <stdbool.h>

int contador;

int islas[6][8] = {
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,1},
    {0,1,1,0,0,1,0,1},
    {0,1,1,0,0,1,0,1},
    {0,0,0,0,1,1,0,1},
    {0,0,0,0,0,0,0,0}
};

void eliminarIsla(int islas[6][8], int F, int C){
    if (islas[F][C] == 1 && F<6 && C<8){

        islas[F][C] = 0;
        eliminarIsla(islas, F+1, C);
        eliminarIsla(islas, F+1, C+1);
        eliminarIsla(islas, F+1, C-1);
        eliminarIsla(islas, F-1, C);
        eliminarIsla(islas, F-1, C+1);
        eliminarIsla(islas, F-1, C-1);
        eliminarIsla(islas, F, C+1);
        eliminarIsla(islas, F, C-1);
    }

    return ;
}

int contarIslas (int islas[6][8]){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 8; j++)
        {
            if (islas[i][j] == 1){
                eliminarIsla(islas, i, j);
                contador++;
            }
        }
    }
    return contador;
}


int main() {
    int total = contarIslas(islas);
    printf("El total de islas es %d\n",total);
    return 0;
}
~~~

### Pruebas de escritorio Dekker y Peterson
Ejemplo de dekker:
![Ejemplo de Dekker](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/Ejemplo%20algoritmo%20Dekker.jpg?raw=true)

Ejemplo de producto consumidor Dekker:
![Ejemplo de producto consumidor Dekker 1](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Dekker1.jpg?raw=true)
![Ejemplo de producto consumidor Dekker 2](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Dekker2.jpg?raw=true)
![Ejemplo de producto consumidor Dekker 3](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Dekker3.jpg?raw=true)
![Ejemplo de producto consumidor Dekker 4](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Dekker4.jpg?raw=true)
![Ejemplo de producto consumidor Dekker 5](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Dekker5.jpg?raw=true)

Ejemplo de Peterson:
![Ejemplo de Peterson](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/Ejemplo%20algoritmo%20Peterson.jpg?raw=true)

Ejemplo de producto consumidor Peterson:
![Ejemplo de producto consumidor Peterson 1](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Peterson1.jpg?raw=true)
![Ejemplo de producto consumidor Peterson 2](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Peterson2.jpg?raw=true)
![Ejemplo de producto consumidor Peterson 3](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Pruebas_de_escritorio/ProctoConsumido%20Peterson3.jpg?raw=true)


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

Codigo completo:
~~~
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max_particiones 100
#define max_procesos 100

typedef struct {
    int tamano;
    int id_de_proceso; 
} Particion;

void imprime_memoria(Particion particion[], int numero_de_particiones) {
    printf("\nEstado de la memoria:\n");
    for (int i = 0; i < numero_de_particiones; i++) {
        if (particion[i].id_de_proceso == -1) {
            printf("Partición %d: %d KB (Libre)\n", i + 1, particion[i].tamano);
        } else {
            printf("Partición %d: %d KB (Proceso %d)\n", i + 1, particion[i].tamano, particion[i].id_de_proceso);
        }
    }
    printf("\n");
}

void ingresar_tamano(Particion particion[],int particiones, int tamano_particion ){
        for(int i = 0; i<particiones; i++){
        printf("Ingresa el tamaño de la particion:  %d\n", i+1);
        scanf("%d", &particion[i].tamano);
        particion[i].id_de_proceso = -1;
        tamano_particion += particion[i].tamano;
    }
}

int main(){
    int memoria_total, particiones, opcion, tamano_particion = 0;
    Particion particion[max_particiones];

    printf("Ingresa el tamaño de la memoria: \n");
    scanf("%d", &memoria_total);

    printf("Ingresa el numero de particiones: \n");
    scanf("%d", &particiones);

    while (particiones>max_particiones){
        printf("El numero de particiones excedio el limite (100), ingresa otro numero  \n");
        scanf("%d", &particiones);
    }
    
    
    ingresar_tamano(particion, particiones, tamano_particion);

    while (tamano_particion > memoria_total){
        printf("El tamaño total de las particiones excede el tamaño de la memoria.\n");
        printf("Ingresa de nuevo el tamaño.\n");
        tamano_particion = 0;

        ingresar_tamano(particion, particiones, tamano_particion);
    }

    do {       
        printf("1. Asignar proceso\n");
        printf("2. Liberar proceso\n");
        printf("3. Mostrar estado de la memoria\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int id_de_proceso, tam_proceso;
                bool id_igual = false;

                do{
                    id_igual = false;
                    printf("Ingrese el ID del proceso: ");
                    scanf("%d", &id_de_proceso);

                    for (int i = 0; i < particiones; i++) {
                        if (particion[i].id_de_proceso == id_de_proceso) {
                            printf("Ese Id ya esta asignado, prueba con otro. \n ");
                            id_igual = true;
                            break;
                    }
                }
                } while (id_igual == true);

                printf("Ingrese el tamaño del proceso (KB): ");
                scanf("%d", &tam_proceso);

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
            }
            case 2: {
                int id_de_proceso;
                printf("Ingrese el ID del proceso a liberar: ");
                scanf("%d", &id_de_proceso);

                int libre = 0;
                for (int i = 0; i < particiones; i++) {
                    if (particion[i].id_de_proceso == id_de_proceso) {
                        particion[i].id_de_proceso = -1;
                        libre = 1;
                        printf("Proceso %d liberado de la partición %d.\n", id_de_proceso, i + 1);
                        break;
                    }
                }
                if (!libre) {
                    printf("No se encontró el proceso %d en ninguna partición.\n", id_de_proceso);
                }
                break;
            }
            case 3:
                imprime_memoria(particion, particiones);
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);

    return 0;
}
~~~

### 3.3 Organizacion de memoria virtual
###### 1. Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?

La __paginación__ es una estrategia de organización de la memoria física que consiste en dividir la memoria en porciones de igual tamaño. A dichas porciones se las conoce como páginas físicas o marcos. La división de la memoria en páginas facilita la gestión de la memoria física. Los marcos se identifican con un número que se denomina «número de página física. A su vez, cada página física se asigna a un proceso de forma exclusiva.

Tanto el tamaño de las páginas como de los marcos de páginas es definido por el hardware y suele ser una potencia de 2. Permite que las páginas de un proceso puedan cargarse en cualquier marco de página disponible, sin necesidad de que estén contiguos en la memoria.

El sistema operativo mantiene una tabla de páginas para cada proceso, que mapea cada página lógica a su marco físico correspondiente. Esta tabla se utiliza para traducir las direcciones lógicas (del proceso) a direcciones físicas (de la memoria). Cuando el proceso necesita acceder a una dirección lógica, el traductor de memoria paginada toma la dirección lógica y, por medio de la tabla de página, obtiene la dirección física real.

Ejemplo:
Supongamos un tamaño de página de 4 KB. Un proceso tiene 16 KB de memoria lógica, dividido en 4 páginas. La memoria física tiene 8 marcos disponibles.
Las páginas del proceso se asignan a marcos libres como sigue:
![Tabla de paginacion](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Administraci%C3%B3n_de_memoria/tabla_paginacion.jpg?raw=true)

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
![Tabla de segmentacion](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Administraci%C3%B3n_de_memoria/tabla_segmentacion.jpg?raw=true)

Si se usa segmentación, cada sección se asigna a un segmento diferente. Una dirección lógica en el segmento 1 (código) con un desplazamiento de 500 se traduce a una dirección física en la memoria donde ese segmento está cargado.


__Ventajas:__
* Ofrecer protección dentro de los segmentos.
* Puede lograr compartir segmentando y haciendo referencia a múltiples procesos.
* No ofrece fragmentación interna.
* Las tablas de segmentos usan menos memoria que la paginación

__Desventajas:__
* En el método de segmentación, los procesos se cargan o eliminan de la memoria principal. Por tanto, el espacio libre de memoria se separa en pequeños trozos, lo que puede crear un problema de fragmentación externa.
* Algoritmo costoso de gestión de memoria

###### 2. Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual.

Para el el codigo de la tabla de paginas se usa un arreglo que ocntiene todas las paginas, hay 100 y solo puede haber 10 procesos, al momento de asignar un proceso se pide el su ID y el tamaño del proceso, se simula con una formula para calcular la cantidad de paginas que se va a utilizar, como el acceso debe ser aleatorio la forma en que se asigna tambien es aleatoria asi que se usa un random que da un numero aleatorio para la acceder a la posicion del arreglo de las paginas (0-19). Esto se puede hacer por la forma en que funciona la paginacion, ya que no necesitan ser ocntinuos los espacios donde almacenan los procesos.
~~~            
    if paginas_disponibles >= num_paginas:
        while paginas_asignadas < num_paginas:
            pagina = random.randint(0, len(tabla_paginas) - 1)  
            if tabla_paginas[pagina] == -1: 
                tabla_paginas[pagina] = id_proceso 
                paginas_asignadas += 1
    else:
        print(f"No hay suficiente memoria para asignar el proceso {id_proceso}.")
~~~

Se peude ver toda la tabla en forma de arreglo con la opcion 3, pero se puede acceder de forma aleatoria a varias paginas con la opcion 2.
~~~
def acceso_aleatorio(num_acceso):
    print("\nAccesos aleatorios a la memoria:")
    for _ in range(num_acceso):
        pagina = random.randint(0, len(tabla_paginas) - 1)
        if tabla_paginas[pagina] == -1:
            print(f"Página {pagina} está libre.")
        else:
            print(f"Página {pagina} es parte del proceso {tabla_paginas[pagina]}.")
~~~

__Codigo completo:__
~~~
import random

max_paginas = 100
max_procesos = 10
tam_pagina = 4

tabla_paginas = []
for i in range (max_paginas):
    tabla_paginas.append(-1)
    
def asignar_proceso(id_proceso, tamano_proceso):    
    num_paginas = (tamano_proceso + tam_pagina - 1) // tam_pagina
    paginas_asignadas = 0
    paginas_disponibles = 0
    
    for i in range (max_paginas):
        if tabla_paginas[i] == -1:
            paginas_disponibles = paginas_disponibles + 1
            
    if paginas_disponibles >= num_paginas:
        while paginas_asignadas < num_paginas:
            pagina = random.randint(0, len(tabla_paginas) - 1)  
            if tabla_paginas[pagina] == -1: 
                tabla_paginas[pagina] = id_proceso 
                paginas_asignadas += 1
    else:
        print(f"No hay suficiente memoria para asignar el proceso {id_proceso}.")
    
def mostrar_tabla():
    print("\n Tabla de paginas")
    for i in range(max_paginas):
        if tabla_paginas[i] == -1:
            print(f"Página {i}: Libre")
        else:
            print(f"Página {i}: Proceso {tabla_paginas[i]}")
            
def liberar_proceso():
    id_proceso = int(input("\n Ingresa el id del proceso a liberar: "))     
    liberado = False
    for i in range(max_paginas):
        if tabla_paginas[i] == id_proceso:
            tabla_paginas[i] = -1 
            liberado = True
    if liberado == True:
            print(f"Proceso {id_proceso} liberado.")
    else:
            print(f"Proceso {id_proceso} no encontrado.")        
            
def acceso_aleatorio(num_acceso):
    print("\nAccesos aleatorios a la memoria:")
    for _ in range(num_acceso):
        pagina = random.randint(0, len(tabla_paginas) - 1)
        if tabla_paginas[pagina] == -1:
            print(f"Página {pagina} está libre.")
        else:
            print(f"Página {pagina} es parte del proceso {tabla_paginas[pagina]}.")
    
def main():
    while True:
        print("\n1. Asignar proceso")
        print("2. Acceso aleatorio")
        print("3. Mostrar estado de la tabla de páginas")
        print("4. Liberar proceso")
        print("5. Salir")
        opcion = int(input("Seleccione una opción: "))

        if opcion == 1:
            id_proceso = int(input("Ingrese el ID del proceso: "))
            tamano_proceso = int(input("Ingrese el tamaño del proceso (KB): "))
            asignar_proceso(id_proceso, tamano_proceso)
        elif opcion == 2:
            num_acceso = int(input("Ingrese el numero de accesos aleatorios: "))
            acceso_aleatorio(num_acceso)
        elif opcion == 3:
            mostrar_tabla()
        elif opcion == 4:
            liberar_proceso()
        elif opcion == 5:
            print("Saliendo del programa.")
            break
        else:
            print("Opción no válida.")
            
if __name__ == "__main__":
    main()
~~~

### 3.4 Administración de memoria virtual
###### 1. Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU).
En el codigo primero pide al usuario ingresar el numero de marcos, numero de paginas, y la secuencia de las paginas. Se usa la funcion remplazo y empieza a poner los marcos como libres con un -1, y con un tiempo de 0 para cada uno. Empieza a buscar cada una de las paginas en los marcos de acuerdo a la secuencia, si no encuentra una usa la funcion encontrar_menos_reciente para buscar el marco que contiene a la pagina menos reciente utilizada revisando el tiempo de cada pagina, si encuentra un marco de pagina con un tiempo menor al del anterior lo toma como referencia para el siguiente marco hasata comprobar que es el menor, y lo returna.
~~~
printf("Secuencia de reemplazo:\n");

    for (int i = 0; i < num_paginas; i++) {
        int pagina = paginas[i];
        int encontrado = false;

        for (int j = 0; j < num_marcos; j++) {
            if (marcos[j] == pagina) {
                encontrado = true;
                tiempo[j] = ++contador; 
                break;
            }
        }

        if (encontrado == false) {
            int menos_reciente = encontrar_menos_reciente(tiempo, num_marcos);

            marcos[menos_reciente] = pagina;
            tiempo[menos_reciente] = ++contador;
            fallos++;

            mostrar_marcos(marcos, num_marcos);
        }
    }
~~~
~~~
int encontrar_menos_reciente(int tiempo[], int num_marcos) {
    int min_tiempo = INT_MAX;
    int menos_reciente = 0;

    for (int i = 0; i < num_marcos; i++) {
        if (tiempo[i] < min_tiempo) {
            min_tiempo = tiempo[i];
            menos_reciente = i;
        }
    }
    return menos_reciente;
}
~~~
De volvera la primera posicion de los marcos ya que aun no se habian utilizado ninguno, agregara la pagina al marco y le sumara al contador de tiempo, ademas de que sumara a la variable fallos por no haber encontrado la pagina dentro de los marcos. Y asi ira realizando el ciclo for hasta haber acabado la secuencia de las paginas.
~~~
void remplazo(int paginas[], int num_paginas, int num_marcos) {
    int marcos[num_marcos];
    int tiempo[num_marcos];
    int contador = 0;  
    int fallos = 0;

    for (int i = 0; i < num_marcos; i++) {
        marcos[i] = -1;
        tiempo[i] = 0;
    }

    printf("Secuencia de reemplazo:\n");

    for (int i = 0; i < num_paginas; i++) {
        int pagina = paginas[i];
        int encontrado = false;

        for (int j = 0; j < num_marcos; j++) {
            if (marcos[j] == pagina) {
                encontrado = true;
                tiempo[j] = ++contador; 
                break;
            }
        }
~~~

__codigo completo:__
~~~
#include <stdio.h>
#include <limits.h>

void mostrar_marcos(int marcos[], int num_marcos) {
    for (int i = 0; i < num_marcos; i++) {
        if (marcos[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", marcos[i]);
        }
    }
    printf("\n");
}

int encontrar_menos_reciente(int tiempo[], int num_marcos) {
    int min_tiempo = INT_MAX;
    int menos_reciente = 0;

    for (int i = 0; i < num_marcos; i++) {
        if (tiempo[i] < min_tiempo) {
            min_tiempo = tiempo[i];
            menos_reciente = i;
        }
    }
    return menos_reciente;
}

void remplazo(int paginas[], int num_paginas, int num_marcos) {
    int marcos[num_marcos];
    int tiempo[num_marcos];
    int contador = 0;  
    int fallos = 0;

    for (int i = 0; i < num_marcos; i++) {
        marcos[i] = -1;
        tiempo[i] = 0;
    }

    printf("Secuencia de reemplazo:\n");

    for (int i = 0; i < num_paginas; i++) {
        int pagina = paginas[i];
        int encontrado = false;

        for (int j = 0; j < num_marcos; j++) {
            if (marcos[j] == pagina) {
                encontrado = true;
                tiempo[j] = ++contador; 
                break;
            }
        }

        if (encontrado == false) {
            int menos_reciente = encontrar_menos_reciente(tiempo, num_marcos);

            marcos[menos_reciente] = pagina;
            tiempo[menos_reciente] = ++contador;
            fallos++;

            mostrar_marcos(marcos, num_marcos);
        }
    }

    printf("\nTotal de fallos de página: %d\n", fallos);
}

int main() {
    int num_paginas, num_marcos;

    printf("Ingresa el número de marcos: ");
    scanf("%d", &num_marcos);

    printf("Ingresa el número de páginas: ");
    scanf("%d", &num_paginas);

    int paginas[num_paginas];
    printf("Ingresa la secuencia de uso de páginas:\n");
    for (int i = 0; i < num_paginas; i++) {
        scanf("%d", &paginas[i]);
    }

    remplazo(paginas, num_paginas, num_marcos);

    return 0;
}

~~~


###### 2. Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual.
El diagrama muestra que la direccion virtual está dividida en el número de página y el desplazamiento (Offset). Tiene un buffer de traducción adelantada (TLB), que muestra cómo se verifica si la dirección virtual tiene una entrada correspondiente en la TLB. Si la TLB no muestra ninguna coincidencia, se recurre a la tabla de páginas para obtener el marco físico correspondiente. Por ultimo la direccion fisica sale al combinar el marco físico con el desplazamiento.

![Diagrama de traduccion de direcciones](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Administraci%C3%B3n_de_memoria/diagrama%20de%20traduccion%20de%20direcciones.jpg?raw=true)

### 4.1 Dispositivos y manejadores de dispositivos 
###### 1. Explica la diferencia entre dispositivos de bloque y dispositivos de carácter. Da un ejemplo de cada uno. 

Todos los dispositivos instalados en una máquina pueden ser accedidos a través de un interfaz de ficheros bajo el directorio /dev/. Allí podemos encontrar los dispositivos conectados a las controladoras IDE (hda, hdb, hdc y hdd), el dsp de la tarjeta de sonido, etc.
Los ficheros asociados a un dispositivo pueden ser de dos tipos, de carácter y de bloque .

Los __dispositivos de carácter__ son accedidos secuencialmente, un carácter cada vez. Algunos ejemplos de dispositivos de carácter son el ratón, el teclado, un terminal de texto, una cinta magnética, etc.

Los __dispositivos de bloque__ se caracterizan por ser de acceso aleatorio, la unidad mínima de lectura-escritura no es un carácter, sino un bloque (1KB). Algunos ejemplos de dispositivos de carácter son los discos duros, los disquetes, los CDROMS, etc.

Dispositivos de Bloque:
* Trabajan con datos en bloques de tamaño fijo.
* La E/S se realiza en bloques de datos completos, lo que permite una transferencia eficiente de grandes cantidades de datos.
* Suelen ser más adecuados para el almacenamiento de datos a largo plazo y la transferencia de archivos grandes.

Dispositivos de Carácter:
* Trabajan con datos en forma de caracteres individuales.
* La E/S se realiza carácter por carácter, lo que los hace más adecuados para la interacción humana y la comunicación en tiempo real.
* Suelen ser más utilizados para la entrada de datos, la visualización de información y la comunicación con dispositivos externos.

En conclusión, los dispositivos de bloque manejan datos en bloques de tamaño fijo, mientras que los dispositivos de carácter manejan datos carácter por carácter y son más adecuados para la interacción humana y la comunicación en tiempo real.

###### 2. Diseña un programa que implemente un manejador de dispositivos sencillo para un dispositivo virtual de entrada.
En el codigo se maneja un dispositivo en el cual se pueden escribir mensajes, el dispositivo puede despues imprimir el mensaje que tiene dentro, se puede liberar el dispositivo o seguir escribiendo un mensaje que se imprimira junto con el mensaje que tenia anteriormente.
Esta funcion escribe en el dispositivo si ya se inicializo y si hay espacio:
~~~
void escribir_dispositivo(Dispositivo_virtual *dispositivo, const char *data) {
    if (dispositivo == NULL || dispositivo->buffer == NULL) {
        printf("Error: Dispositivo no inicializado.\n");
        return;
    }
    int data_length = strlen(data);
    if (dispositivo->posicion + data_length >= dispositivo->tamano_buffer) {
        printf("Error: No hay suficiente espacio en el búfer del dispositivo.\n");
        return;
    }
    memcpy(&dispositivo->buffer[dispositivo->posicion], data, data_length);
    dispositivo->posicion += data_length;
    printf("Datos escritos al dispositivo: %s\n", data);
}
~~~

Esta funcion muestra el mensaje que sta en el dispositivo:
~~~
void leer_dispositivo(Dispositivo_virtual *dispositivo) {
    if (dispositivo == NULL || dispositivo->buffer == NULL) {
        printf("Error: Dispositivo no inicializado.\n");
        return;
    }
    printf("Datos en el dispositivo: %s\n", dispositivo->buffer);
}
~~~

Esta funcion usa free para liberar el despositivo y hace que el codigo termine:
~~~
void liberar_dispositivo(Dispositivo_virtual *dispositivo) {
    if (dispositivo == NULL) {
        return;
    }
    free(dispositivo->buffer);
    free(dispositivo);
    printf("Dispositivo liberado correctamente.\n");
}
~~~

El dispositivo tiene esta estrucutura para poder escribir y leer los datos que hay en el:
~~~
typedef struct {
    char *buffer;       
    int tamano_buffer;  
    int posicion;       
} Dispositivo_virtual;
~~~

Codigo completo:
~~~
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *buffer;       
    int tamano_buffer;  
    int posicion;       
} Dispositivo_virtual;

Dispositivo_virtual* iniciar_dispositivo(int size) {
    Dispositivo_virtual *dispositivo = (Dispositivo_virtual *)malloc(sizeof(Dispositivo_virtual));
    if (dispositivo == NULL) {
        perror("Error al asignar memoria para el dispositivo");
        return NULL;
    }
    dispositivo->buffer = (char *)malloc(size);
    if (dispositivo->buffer == NULL) {
        perror("Error al asignar memoria para el búfer del dispositivo");
        free(dispositivo);
        return NULL;
    }
    dispositivo->tamano_buffer = size;
    dispositivo->posicion = 0;
    memset(dispositivo->buffer, 0, size); 
    printf("Dispositivo inicializado con un búfer de %d bytes.\n", size);
    return dispositivo;
}


void escribir_dispositivo(Dispositivo_virtual *dispositivo, const char *data) {
    if (dispositivo == NULL || dispositivo->buffer == NULL) {
        printf("Error: Dispositivo no inicializado.\n");
        return;
    }
    int data_length = strlen(data);
    if (dispositivo->posicion + data_length >= dispositivo->tamano_buffer) {
        printf("Error: No hay suficiente espacio en el búfer del dispositivo.\n");
        return;
    }
    memcpy(&dispositivo->buffer[dispositivo->posicion], data, data_length);
    dispositivo->posicion += data_length;
    printf("Datos escritos al dispositivo: %s\n", data);
}


void leer_dispositivo(Dispositivo_virtual *dispositivo) {
    if (dispositivo == NULL || dispositivo->buffer == NULL) {
        printf("Error: Dispositivo no inicializado.\n");
        return;
    }
    printf("Datos en el dispositivo: %s\n", dispositivo->buffer);
}

void liberar_dispositivo(Dispositivo_virtual *dispositivo) {
    if (dispositivo == NULL) {
        return;
    }
    free(dispositivo->buffer);
    free(dispositivo);
    printf("Dispositivo liberado correctamente.\n");
}


int main() {
    Dispositivo_virtual *dispositivo = iniciar_dispositivo(BUFFER_SIZE);
    if (dispositivo == NULL) {
        return 1;
    }

    int opcion;
    char mensaje[BUFFER_SIZE];

    do {
        printf("\n--- Menú ---\n");
        printf("1. Escribir un mensaje\n");
        printf("2. Leer los datos del dispositivo\n");
        printf("3. Liberar el dispositivo y salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1:
                printf("Escribe tu mensaje: ");
                fgets(mensaje, BUFFER_SIZE, stdin);
                mensaje[strcspn(mensaje, "\n")] = '\0';
                escribir_dispositivo(dispositivo, mensaje);
                break;
            case 2:
                leer_dispositivo(dispositivo);
                break;
            case 3:
                liberar_dispositivo(dispositivo);
                printf("Desconectado\n");
                break;
            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}
~~~



### 4.2 Mecanismos y funciones de los manejadores de dispositivos 
###### 1. Investiga qué es la interrupción por E/S y cómo la administra el sistema operativo. Escribe un ejemplo en pseudocódigo para simular este proceso

Una interrupción es una señal recibida por el procesador de una computadora, que indica que debe «interrumpir» el curso de ejecución actual y pasar a ejecutar código específico para tratar esta situación. Las interrupciones de hardware son aquellas interrupciones que se producen como resultado de, por lo general, una operación de E/S. En los sistemas modernos se prefiere un funcionamiento mediante interrupciones, ya que éstas permiten mejorar la productividad del procesador, de forma que este último puede ordenar una operación de E/S y, en lugar de tener que realizar una espera activa, se puede dedicar a atender a otro proceso o aplicación hasta que el dispositivo esté de nuevo disponible, siendo dicho dispositivo el encargado de notificar al procesador mediante la línea de interrupción que ya está preparado para continuar/terminar la operación de E/S.

El sistema operativo utiliza varias estrategias para manejar las interrupciones y coordinar las operaciones de E/S de manera eficiente:

* Las operaciones de E/S suelen utilizar buffers en la memoria para almacenar temporalmente los datos. Por ejemplo, los datos leídos de un disco duro se guardan en un buffer antes de ser enviados a una aplicación.

* Cada dispositivo tiene un controlador de software que traduce las operaciones de alto nivel solicitadas por el sistema operativo en comandos específicos para el hardware.

* El sistema asigna prioridades a las interrupciones para garantizar que las más críticas (como las de hardware o red) sean atendidas primero.

* El sistema operativo puede enmascarar ciertas interrupciones para evitar que interfieran mientras se maneja otra de mayor prioridad.

__pseudocodigo:__
~~~
BUFFER ← []               Memoria temporal para almacenar datos del dispositivo
DISPOSITIVO_LISTO ← False   Estado del dispositivo de E/S
INTERRUPCION_PENDIENTE ← False
TAREA_ACTUAL ← "Proceso1"  Representa el proceso en ejecución

 Simula un controlador de interrupciones
PROCEDIMIENTO ControladorInterrupciones()
    SI INTERRUPCION_PENDIENTE ENTONCES
        Guarda el contexto actual
        IMPRIMIR "Guardando contexto del proceso: " & TAREA_ACTUAL

        Llama al manejador de interrupciones
        ManejadorInterrupcion()

        Restaura el contexto y retoma la tarea
        IMPRIMIR "Restaurando contexto del proceso: " & TAREA_ACTUAL
        INTERRUPCION_PENDIENTE ← FALSO
    FIN_SI
FIN_PROCEDIMIENTO

Simula el manejador de interrupciones para un dispositivo de E/S
PROCEDIMIENTO ManejadorInterrupcion()
    IMPRIMIR "Interrupción recibida. Procesando dispositivo de E/S..."
    
    Simula la lectura de datos desde un dispositivo
    SI DISPOSITIVO_LISTO ENTONCES
        DATO ← LeerDispositivo()
        AGREGAR DATO A BUFFER
        IMPRIMIR "Dato recibido: " & DATO
    SINO
        IMPRIMIR "Error: Dispositivo no está listo."
    FIN_SI
FIN_PROCEDIMIENTO

Simula el proceso de lectura desde un dispositivo de E/S
FUNCION LeerDispositivo()
    IMPRIMIR "Leyendo datos del dispositivo..."
    RETORNAR "DatoSimulado"
FIN_FUNCION

Simula el sistema operativo en funcionamiento
PROCEDIMIENTO SistemaOperativo()
    MIENTRAS VERDADERO HACER
        Verifica si hay interrupciones pendientes
        SI INTERRUPCION_PENDIENTE ENTONCES
            ControladorInterrupciones()
        FIN_SI

        Simula la ejecución de un proceso
        IMPRIMIR "Ejecutando: " & TAREA_ACTUAL
        ESPERAR(1) # Simula tiempo de ejecución

        Simula la llegada de una interrupción aleatoria
        SI GenerarEventoAleatorio() ENTONCES
            INTERRUPCION_PENDIENTE ← VERDADERO
            DISPOSITIVO_LISTO ← VERDADERO
        FIN_SI
    FIN_MIENTRAS
FIN_PROCEDIMIENTO

Simula un evento aleatorio para generar interrupciones
FUNCION GenerarEventoAleatorio()
    RETORNAR RANDOM(1, 10) > 7 # Simula un 30% de probabilidad de interrupción
FIN_FUNCION

Inicia el sistema operativo
SistemaOperativo()

~~~

###### 2. Escribe un programa que utilice el manejo de interrupciones en un sistema básico de simulación.
El programa muestra un bucle en ejecucion que simula al sistema operativo ejecutando un proceso
~~~
while (1) {
    printf("Programa principal ejecutándose...\n");
    sleep(2); 
}
~~~

El programa muestra el PID (Process ID) para permitir que el usuario envíe señales al proceso:
~~~
    printf("Proceso iniciado. PID: %d\n", getpid());
    printf("Use 'kill -USR1 %d' o 'kill -USR2 %d' para enviar interrupciones.\n", getpid(), getpid());
~~~

Los manejadores de interupciones se ejecutan al recibir SIGUSR1 o SIGUSR2. Estas son señales definidas por <signal.h>, y son señales de los sistemas operativos basados en Unix o Linux. Son usados para permitir a un proceso informar a otro sobre un evento.
~~~
void manejador_interrupcion1(int signo) {
    printf("\nManejador de interrupcion 1: Señal recibida (%d).\n", signo);
    sleep(1); // Simula el tiempo de manejo de la interrupción
    printf("Manejador de interrupcion 1 completado.\n");
}

void manejador_interrupcion2(int signo) {
    printf("\nManejador de interrupcion 2: Señal recibida (%d).\n", signo);
    sleep(1); // Simula el tiempo de manejo de la interrupción
    printf("Manejador de interrupcion 2 completado.\n");
}
~~~
Y estas señales se vinculan a los manejadores:
~~~
signal(SIGUSR1, manejador_interrupcion1); 
signal(SIGUSR2, manejador_interrupcion2); 
~~~

Al ejecutarse empieza a ejecutarse el bucle, imprime un mensaje y el PID para recibir la señal de interrupcion
```bash
$ ./manejo_interrup
Proceso iniciado. PID: 127
Use 'kill -USR1 127' o 'kill -USR2 127' para enviar interrupciones.
Programa principal ejecutándose...
Programa principal ejecutándose...
Programa principal ejecutándose...
```

Desde otra terminal se puede ejecutar kill -USR1 127 para mandar la señal de interrupcion
```bash
david@LAPTOP-VE1GRO8B ~
$ kill -USR1 127
```

Cuando la primer termial recibe la señal manda el siguiente mensaje:
```bash
Programa principal ejecutándose...
Programa principal ejecutándose...

Manejador de interrupcion 1: Señal recibida (30).
Manejador de interrupcion 1 completado.
Programa principal ejecutándose...
Programa principal ejecutándose...
```

y continua con el bucle despues de mandar el mensaje.

Codigo completo:
~~~
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Manejadores de "interrupciones" simuladas
void manejador_interrupcion1(int signo) {
    printf("\nManejador de interrupcion 1: Señal recibida (%d).\n", signo);
    sleep(1); // Simula el tiempo de manejo de la interrupción
    printf("Manejador de interrupcion 1 completado.\n");
}

void manejador_interrupcion2(int signo) {
    printf("\nManejador de interrupcion 2: Señal recibida (%d).\n", signo);
    sleep(1); // Simula el tiempo de manejo de la interrupción
    printf("Manejador de interrupcion 2 completado.\n");
}

int main() {
    // Registrar los manejadores de señales
    signal(SIGUSR1, manejador_interrupcion1); // Interrupción simulada 1
    signal(SIGUSR2, manejador_interrupcion2); // Interrupción simulada 2

    printf("Proceso iniciado. PID: %d\n", getpid());
    printf("Use 'kill -USR1 %d' o 'kill -USR2 %d' para enviar interrupciones.\n", getpid(), getpid());

    // Bucle infinito que simula un programa en ejecución
    while (1) {
        printf("Programa principal ejecutándose...\n");
        sleep(2); // Simula el trabajo normal del programa
    }

    return 0;
}
~~~


### Listar dispositivos conectados
```bash
__lsblk__: Enumera los dispositivos de bloque
resultado en la terminal:
David@SistemasOperativos:~$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
loop0	7:0	0 	4K  1 loop /snap/bare/5
loop1	7:1	0  74.2M  1 loop /snap/core22/1621
loop2	7:2	0   272M  1 loop /snap/firefox/5091
loop3	7:3	0  73.9M  1 loop /snap/core22/1722
loop4	7:4	0  11.7M  1 loop /snap/desktop-security-center/32
loop5	7:5	0  10.7M  1 loop /snap/firmware-updater/127
loop6	7:6	0 273.7M  1 loop /snap/firefox/5437
loop7	7:7	0 505.1M  1 loop /snap/gnome-42-2204/176
loop8	7:8	0  91.7M  1 loop /snap/gtk-common-themes/1535
loop9	7:9	0  11.1M  1 loop /snap/firmware-updater/147
loop10   7:10   0	14M  1 loop /snap/prompting-client/51
loop11   7:11   0  10.7M  1 loop /snap/snap-store/1218
loop12   7:12   0  89.7M  1 loop /snap/gtk-common-themes/1536
loop13   7:13   0  38.8M  1 loop /snap/snapd/21759
loop14   7:14   0  44.3M  1 loop /snap/snapd/23258
loop15   7:15   0   568K  1 loop /snap/snapd-desktop-integration/253
loop16   7:16   0   564K  1 loop /snap/snapd-desktop-integration/247
sda  	8:0	0  25.5G  0 disk
├─sda1   8:1	0 	1M  0 part
└─sda2   8:2	0  25.5G  0 part /
sr0 	11:0	1  1024M  0 rom  
David@SistemasOperativos:~$
```


__lsusb__: Lista los dispositivos conectados a los puertos USB.
# Listar los dispositivos de bloque en el sistema
```bash
David@SistemasOperativos:~$ lsusb 
Bus 001 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
Bus 001 Device 002: ID 80ee:0021 VirtualBox USB Tablet
Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```
__lspci__: Muestra los dispositivos conectados al bus PCI.
```bash
David@SistemasOperativos:~$ lspci
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01)
00:02.0 VGA compatible controller: VMware SVGA II Adapter
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
00:04.0 System peripheral: InnoTek Systemberatung GmbH VirtualBox Guest Service
00:05.0 Multimedia audio controller: Intel Corporation 82801AA AC'97 Audio Controller (rev 01)
00:06.0 USB controller: Apple Inc. KeyLargo/Intrepid USB
00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
00:0b.0 USB controller: Intel Corporation 82801FB/FBM/FR/FW/FRW (ICH6 Family) USB2 EHCI Controller
00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)
```

__dmesg | grep usb__: Muestra los mensajes del kernel relacionados con dispositivos USB.
Sin permiso de usuario privilegiado o administrador sale esto:
```bash
David@SistemasOperativos:~$ dmesg | grep usb
dmesg: fallo al leer el «buffer» del núcleo: Operación no permitida
```

Con permiso de usuario al poner __sudo__ al principio y poner la ocntraseña sale esto:
```bash
David@SistemasOperativos:~$ sudo dmesg | grep usb
[sudo] contraseña para David: 
[    2.516211] usbcore: registered new interface driver usbfs
[    2.516232] usbcore: registered new interface driver hub
[    2.516255] usbcore: registered new device driver usb
[    3.581033] usb usb1: New USB device found, idVendor=1d6b, idProduct=0001, bcdDevice= 6.11
[    3.581033] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    3.581033] usb usb1: Product: OHCI PCI host controller
[    3.581033] usb usb1: Manufacturer: Linux 6.11.0-9-generic ohci_hcd
[    3.581033] usb usb1: SerialNumber: 0000:00:06.0
[    3.661928] usb usb2: New USB device found, idVendor=1d6b, idProduct=0002, bcdDevice= 6.11
[    3.661936] usb usb2: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    3.661940] usb usb2: Product: EHCI Host Controller
[    3.661944] usb usb2: Manufacturer: Linux 6.11.0-9-generic ehci_hcd
[    3.661948] usb usb2: SerialNumber: 0000:00:0b.0
[    4.399736] usb 1-1: new full-speed USB device number 2 using ohci-pci
[    4.709080] usb 1-1: New USB device found, idVendor=80ee, idProduct=0021, bcdDevice= 1.00
[    4.709095] usb 1-1: New USB device strings: Mfr=1, Product=3, SerialNumber=0
[    4.709104] usb 1-1: Product: USB Tablet
[    4.709112] usb 1-1: Manufacturer: VirtualBox
[    5.307841] usbcore: registered new interface driver usbhid
[    5.307848] usbhid: USB HID core driver
[    5.526382] input: VirtualBox USB Tablet as /devices/pci0000:00/0000:00:06.0/usb1/1-1/1-1:1.0/0003:80EE:0021.0001/input/input6
[    5.529774] hid-generic 0003:80EE:0021.0001: input,hidraw0: USB HID v1.10 Mouse [VirtualBox USB Tablet] on usb-0000:00:06.0-1/input0

```

¿Qué tipos de dispositivos se muestran en la salida de __lsblk__?}
Tiene dispositivos loop que son dispositivos virtuales que el sistema crea para montar imagenes de disco. Tienen un tamaño y la ruta donde esta montado su paquete snap.

¿Cuál es la diferencia entre __lsusb__ y __lspci__?
El lsusb muestra dispositivos externos conectados por medio de los puertos USB, y lspci muestra dispositivos internos conectados al bus PCI como la tarjeta grafica virtual (SVGA II)

¿Qué información adicional proporciona __dmesg | grep usb__?
Muestra informacion detallada de cada dispositivo encontrado, especifica los controladores, los dispositivos fisicos, etc.

### Verificar dispositivos de almacenamiento

Use el comando __fdisk -l__ para listar todos los discos y particiones.
Al usar sudo antes del coamndo me deja ver lo siguiente:
```bash
David@SistemasOperativos:~$ sudo fdisk -l
Disco /dev/loop0: 4 KiB, 4096 bytes, 8 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop1: 74.25 MiB, 77852672 bytes, 152056 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop2: 271.98 MiB, 285192192 bytes, 557016 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop3: 73.87 MiB, 77459456 bytes, 151288 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop4: 11.71 MiB, 12283904 bytes, 23992 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop5: 10.72 MiB, 11239424 bytes, 21952 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop6: 273.68 MiB, 286969856 bytes, 560488 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop7: 505.09 MiB, 529625088 bytes, 1034424 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/sda: 25.54 GiB, 27426832384 bytes, 53568032 sectores
Disk model: VBOX HARDDISK   
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes
Tipo de etiqueta de disco: gpt
Identificador del disco: 8892DD80-1146-4D01-A5E2-28F00035B23A

Dispositivo Comienzo    Final Sectores Tamaño Tipo
/dev/sda1       2048     4095     2048     1M Arranque de BIOS
/dev/sda2       4096 53565439 53561344  25.5G Sistema de ficheros de Linux


Disco /dev/loop8: 91.69 MiB, 96141312 bytes, 187776 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop9: 11.11 MiB, 11649024 bytes, 22752 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop11: 10.67 MiB, 11186176 bytes, 21848 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop10: 13.99 MiB, 14667776 bytes, 28648 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop12: 89.69 MiB, 94044160 bytes, 183680 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop14: 44.3 MiB, 46448640 bytes, 90720 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop15: 568 KiB, 581632 bytes, 1136 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop16: 564 KiB, 577536 bytes, 1128 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes


Disco /dev/loop13: 38.83 MiB, 40714240 bytes, 79520 sectores
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes
```

Utilice __blkid__ para ver los identificadores UUID y los tipos de sistema de archivos.
Al usar el comando blkid sale esto:
```bash
David@SistemasOperativos:~$ sudo blkid
/dev/sda2: UUID="5d380995-4c3c-4890-b90a-3ad80489f3ff" BLOCK_SIZE="4096" TYPE="ext4" PARTUUID="39ccac10-cc60-470d-8d16-64e428f3548e"
/dev/loop1: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop8: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop15: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop6: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop13: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop4: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop11: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop2: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop0: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop9: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop16: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop7: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/sda1: PARTUUID="456ed05b-304c-4d2c-afba-70ed24d7fae8"
/dev/loop14: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop5: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop12: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop3: BLOCK_SIZE="131072" TYPE="squashfs"
/dev/loop10: BLOCK_SIZE="131072" TYPE="squashfs"
```

Use __df -h__ para listar los dispositivos montados y su espacio disponible.
Al usar este comando sale esto:
```bash
David@SistemasOperativos:~$ df -h
S.ficheros     Tamaño Usados  Disp Uso% Montado en
tmpfs            376M   1.7M  374M   1% /run
/dev/sda2         25G   6.4G   18G  27% /
tmpfs            1.9G      0  1.9G   0% /dev/shm
tmpfs            5.0M   8.0K  5.0M   1% /run/lock
tmpfs            1.9G    16K  1.9G   1% /tmp
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-journald.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-udev-load-credentials.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-tmpfiles-setup-dev-early.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-tmpfiles-setup-dev.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-sysctl.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-tmpfiles-setup.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-resolved.service
```

¿Qué dispositivos de almacenamiento están conectados a su sistema?
El disco birtual /dev/sda2 que tiene un tamaño de 25GB y varios dispositivos loop.

¿Qué particiones están montadas actualmente?
segun el comando df -h estas diferentes particiones temporales (tmpfs) que estan en /run /dev/shm y /tmp. Y tambien esta un particion /dev/sda2 que esta montado en la raiz con un tamaño de 25GB.

¿Qué tipo de sistemas de archivos se usan en las particiones?
El ext4 que es el sistema de archivos principal.
Tambien squashfs que es un sistema de archivos de solo lectura.
Y los sitemas temporales tmpfs

### Explorar dispositivos de entrada
Ejecute __cat /proc/bus/input/devices__ para listar los dispositivos de entrada.
Esto sale al ingresar el comando:
```bash
David@SistemasOperativos:~$ cat /proc/bus/input/devices
I: Bus=0019 Vendor=0000 Product=0001 Version=0000
N: Name="Power Button"
P: Phys=LNXPWRBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXPWRBN:00/input/input0
U: Uniq=
H: Handlers=kbd event0 
B: PROP=0
B: EV=3
B: KEY=8000 10000000000000 0

I: Bus=0019 Vendor=0000 Product=0003 Version=0000
N: Name="Sleep Button"
P: Phys=LNXSLPBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSLPBN:00/input/input1
U: Uniq=
H: Handlers=kbd event1 
B: PROP=0
B: EV=3
B: KEY=4000 0 0

I: Bus=0011 Vendor=0001 Product=0001 Version=ab41
N: Name="AT Translated Set 2 keyboard"
P: Phys=isa0060/serio0/input0
S: Sysfs=/devices/platform/i8042/serio0/input/input2
U: Uniq=
H: Handlers=sysrq kbd event2 leds 
B: PROP=0
B: EV=120013
B: KEY=402000000 3803078f800d001 feffffdfffefffff fffffffffffffffe
B: MSC=10
B: LED=7

I: Bus=0019 Vendor=0000 Product=0006 Version=0000
N: Name="Video Bus"
P: Phys=LNXVIDEO/video/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A03:00/LNXVIDEO:00/input/input4
U: Uniq=
H: Handlers=kbd event3 
B: PROP=0
B: EV=3
B: KEY=3e000b00000000 0 0 0

I: Bus=0011 Vendor=0002 Product=0006 Version=0000
N: Name="ImExPS/2 Generic Explorer Mouse"
P: Phys=isa0060/serio1/input0
S: Sysfs=/devices/platform/i8042/serio1/input/input5
U: Uniq=
H: Handlers=mouse0 event4 
B: PROP=1
B: EV=7
B: KEY=1f0000 0 0 0 0
B: REL=143

I: Bus=0003 Vendor=80ee Product=0021 Version=0110
N: Name="VirtualBox USB Tablet"
P: Phys=usb-0000:00:06.0-1/input0
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb1/1-1/1-1:1.0/0003:80EE:0021.0001/input/input6
U: Uniq=
H: Handlers=mouse1 event5 js0 
B: PROP=0
B: EV=1f
B: KEY=1f0000 0 0 0 0
B: REL=1940
B: ABS=3
B: MSC=10

I: Bus=0001 Vendor=80ee Product=cafe Version=0000
N: Name="VirtualBox mouse integration"
P: Phys=
S: Sysfs=/devices/pci0000:00/0000:00:04.0/input/input7
U: Uniq=
H: Handlers=mouse2 event6 js1 
B: PROP=0
B: EV=b
B: KEY=10000 0 0 0 0
B: ABS=3

```

Use __evtest__ para monitorear eventos de dispositivos de entrada (requiere permisos de superusuario).
Resultado de usar sudo evtest:
```bash
David@SistemasOperativos:~$ sudo evtest
No device specified, trying to scan all of /dev/input/event*
Available devices:
/dev/input/event0:	Power Button
/dev/input/event1:	Sleep Button
/dev/input/event2:	AT Translated Set 2 keyboard
/dev/input/event3:	Video Bus
/dev/input/event4:	ImExPS/2 Generic Explorer Mouse
/dev/input/event5:	VirtualBox USB Tablet
/dev/input/event6:	VirtualBox mouse integration
Select the device event number [0-6]: 4
```

Si escojo 4 por ejemplo:
```bash
Input driver version is 1.0.1
Input device ID: bus 0x11 vendor 0x2 product 0x6 version 0x0
Input device name: "ImExPS/2 Generic Explorer Mouse"
Supported events:
  Event type 0 (EV_SYN)
  Event type 1 (EV_KEY)
    Event code 272 (BTN_LEFT)
    Event code 273 (BTN_RIGHT)
    Event code 274 (BTN_MIDDLE)
    Event code 275 (BTN_SIDE)
    Event code 276 (BTN_EXTRA)
  Event type 2 (EV_REL)
    Event code 0 (REL_X)
    Event code 1 (REL_Y)
    Event code 6 (REL_HWHEEL)
    Event code 8 (REL_WHEEL)
Properties:
  Property type 0 (INPUT_PROP_POINTER)
Testing ... (interrupt to exit)
Event: time 1733966672.937819, type 1 (EV_KEY), code 272 (BTN_LEFT), value 1
Event: time 1733966672.937819, -------------- SYN_REPORT ------------
Event: time 1733966673.091261, type 1 (EV_KEY), code 272 (BTN_LEFT), value 0
Event: time 1733966673.091261, -------------- SYN_REPORT ------------
Event: time 1733966673.510296, type 1 (EV_KEY), code 272 (BTN_LEFT), value 1
Event: time 1733966673.510296, -------------- SYN_REPORT ------------
Event: time 1733966673.629718, type 1 (EV_KEY), code 272 (BTN_LEFT), value 0
Event: time 1733966673.629718, -------------- SYN_REPORT ------------

```
Comienza a generar el reporte del dispositivo.

¿Qué eventos genera cada dispositivo al interactuar con ellos?
El mouse genera por ejemplo EV_KEYS que son los eventos de botones como click derecho (BTN_RIGHT) e izquierdo(BTN_LEFT), o como REL_WHEEL para la rueda del raton.
El teclado genera igual EV_KEY con codigos de tecla como KEY_A, KEY_S, KEY_W segun el mapeo del teclado.
Los controladores USB no generan interaccion directa como el teclado o el mouse, pero puede geenrar eventos como cuando se conecta o desconecta un dispositivo

¿Cómo se identifican los dispositivos en /proc/bus/input/devices?
Cada dispositivio tiene su bloque y esta dividido por jemplo:
~~~
I: Bus=0011 Vendor=0002 Product=0006 Version=0000
N: Name="ImExPS/2 Generic Explorer Mouse"
P: Phys=isa0060/serio1/input0
S: Sysfs=/devices/platform/i8042/serio1/input/input6
U: Uniq=
H: Handlers=mouse1 event4 
B: PROP=1
B: EV=7
B: KEY=1f0000 0 0 0 0
B: REL=143
~~~
Que aqui se refiere al teclado, por ejemplo dice el nombre en N, la ubicaicion fisica en P, el controlador en H, y los eventos que tiene en B.

### Examinar dispositivos de salida
Use __xrandr__ para listar las pantallas conectadas y sus resoluciones.
Al usar el comando sale el la pantalla y sus resoluciones:
```bash
David@SistemasOperativos:~$ xrandr
Screen 0: minimum 16 x 16, current 1920 x 1080, maximum 32767 x 32767
Virtual-1 connected 1920x1080+0+0 (normal left inverted right x axis y axis) 0mm x 0mm
   1920x1080     59.96*+
   1440x1080     59.99  
   1400x1050     59.98  
   1280x1024     59.89  
   1280x960      59.94  
   1152x864      59.96  
   1024x768      59.92  
   800x600       59.86  
   640x480       59.38  
   320x240       59.52  
   1680x1050     59.95  
   1440x900      59.89  
   1280x800      59.81  
   1152x720      59.97  
   960x600       59.63  
   928x580       59.88  
   800x500       59.50  
   768x480       59.90  
   720x480       59.71  
   640x400       59.95  
   320x200       58.96  
   1600x900      59.95  
   1368x768      59.88  
   1280x720      59.86  
   1024x576      59.90  
   864x486       59.92  
   720x400       59.55  
   640x350       59.77  
```

Ejecute __aplay -l__ para listar las tarjetas de sonido disponibles.
Al usar el comando sale esto:
```bash
David@SistemasOperativos:~$ aplay -l
**** Lista de PLAYBACK dispositivos hardware ****
tarjeta 0: I82801AAICH [Intel 82801AA-ICH], dispositivo 0: Intel ICH [Intel 82801AA-ICH]
  Subdispositivos: 1/1
  Subdispositivo #0: subdevice #0
```

Use __lsof /dev/snd/*__ para ver qué procesos están utilizando la tarjeta de sonido.
Al usar el comando salen estos procesos:
```bash
David@SistemasOperativos:~$ lsof /dev/snd/*
COMMAND    PID  USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
pipewire  1992 David   57u   CHR  116,1      0t0  425 /dev/snd/seq
pipewire  1992 David   58u   CHR  116,1      0t0  425 /dev/snd/seq
wireplumb 2003 David   29u   CHR  116,5      0t0  740 /dev/snd/controlC0
```

¿Qué salidas de video están disponibles en su sistema?
La pantalla screen 0 con las diferentes resoluciones que salen en la imagen.

¿Qué dispositivos de sonido se detectaron?
La tarjeta 0 que lo detecta como Intel 82801AA-ICH.

¿Qué procesos están usando la tarjeta de sonido?
pipewire es un servidor de audio y multimedia que maneja el audio.
wireplumber controla como se conectan los flujos de audio y video entre aplicaciones y hardware.

### Crear un script de resumen
Cree un archivo llamado __dispositivos.sh__ y agregue el siguiente contenido: ```bash #!/bin/bash echo "Dispositivos de bloque:" lsblk echo "Dispositivos USB:" lsusb echo "Dispositivos PCI:" lspci echo "Dispositivos de entrada:" cat /proc/bus/input/devices echo "Salidas de video:" xrandr echo "Tarjetas de sonido:" aplay -l ```
~~~
#!/bin/bash
echo "Dispositivos de bloque:"
lsblk
echo "Dispositivos USB:"
lsusb
echo "Dispositivos PCI:"
lspci
echo "Dispositivos de entrada:"
cat /proc/bus/input/devices
echo "Salidas de video:"
xrandr
echo "Tarjetas de sonido:"
aplay -l
~~~

Ejecute el script usando __bash dispositivos.sh__.
~~~
Dispositivos de bloque:
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
loop0    7:0    0  73.9M  1 loop /snap/core22/1722
loop1    7:1    0  74.2M  1 loop /snap/core22/1621
loop2    7:2    0     4K  1 loop /snap/bare/5
loop3    7:3    0   272M  1 loop /snap/firefox/5091
loop4    7:4    0  11.7M  1 loop /snap/desktop-security-center/32
loop5    7:5    0  10.7M  1 loop /snap/firmware-updater/127
loop6    7:6    0 273.7M  1 loop /snap/firefox/5437
loop7    7:7    0  11.1M  1 loop /snap/firmware-updater/147
loop8    7:8    0 505.1M  1 loop /snap/gnome-42-2204/176
loop9    7:9    0    14M  1 loop /snap/prompting-client/51
loop10   7:10   0  89.7M  1 loop /snap/gtk-common-themes/1536
loop11   7:11   0  10.7M  1 loop /snap/snap-store/1218
loop12   7:12   0  91.7M  1 loop /snap/gtk-common-themes/1535
loop13   7:13   0  38.8M  1 loop /snap/snapd/21759
loop14   7:14   0   564K  1 loop /snap/snapd-desktop-integration/247
loop15   7:15   0  44.3M  1 loop /snap/snapd/23258
loop16   7:16   0   568K  1 loop /snap/snapd-desktop-integration/253
sda      8:0    0  25.5G  0 disk 
├─sda1   8:1    0     1M  0 part 
└─sda2   8:2    0  25.5G  0 part /
sr0     11:0    1  1024M  0 rom  

Dispositivos USB:
Bus 001 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
Bus 001 Device 002: ID 80ee:0021 VirtualBox USB Tablet
Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

Dispositivos PCI:
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01)
00:02.0 VGA compatible controller: VMware SVGA II Adapter
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
00:04.0 System peripheral: InnoTek Systemberatung GmbH VirtualBox Guest Service
00:05.0 Multimedia audio controller: Intel Corporation 82801AA AC'97 Audio Controller (rev 01)
00:06.0 USB controller: Apple Inc. KeyLargo/Intrepid USB
00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
00:0b.0 USB controller: Intel Corporation 82801FB/FBM/FR/FW/FRW (ICH6 Family) USB2 EHCI Controller
00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)

Dispositivos de entrada:
I: Bus=0019 Vendor=0000 Product=0001 Version=0000
N: Name="Power Button"
P: Phys=LNXPWRBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXPWRBN:00/input/input0
U: Uniq=
H: Handlers=kbd event0 
B: PROP=0
B: EV=3
B: KEY=8000 10000000000000 0

I: Bus=0019 Vendor=0000 Product=0003 Version=0000
N: Name="Sleep Button"
P: Phys=LNXSLPBN/button/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSLPBN:00/input/input1
U: Uniq=
H: Handlers=kbd event1 
B: PROP=0
B: EV=3
B: KEY=4000 0 0

I: Bus=0011 Vendor=0001 Product=0001 Version=ab41
N: Name="AT Translated Set 2 keyboard"
P: Phys=isa0060/serio0/input0
S: Sysfs=/devices/platform/i8042/serio0/input/input2
U: Uniq=
H: Handlers=sysrq kbd event2 leds 
B: PROP=0
B: EV=120013
B: KEY=402000000 3803078f800d001 feffffdfffefffff fffffffffffffffe
B: MSC=10
B: LED=7

I: Bus=0003 Vendor=80ee Product=0021 Version=0110
N: Name="VirtualBox USB Tablet"
P: Phys=usb-0000:00:06.0-1/input0
S: Sysfs=/devices/pci0000:00/0000:00:06.0/usb1/1-1/1-1:1.0/0003:80EE:0021.0001/input/input5
U: Uniq=
H: Handlers=mouse0 event3 js0 
B: PROP=0
B: EV=1f
B: KEY=1f0000 0 0 0 0
B: REL=1940
B: ABS=3
B: MSC=10

I: Bus=0011 Vendor=0002 Product=0006 Version=0000
N: Name="ImExPS/2 Generic Explorer Mouse"
P: Phys=isa0060/serio1/input0
S: Sysfs=/devices/platform/i8042/serio1/input/input6
U: Uniq=
H: Handlers=mouse1 event4 
B: PROP=1
B: EV=7
B: KEY=1f0000 0 0 0 0
B: REL=143

I: Bus=0019 Vendor=0000 Product=0006 Version=0000
N: Name="Video Bus"
P: Phys=LNXVIDEO/video/input0
S: Sysfs=/devices/LNXSYSTM:00/LNXSYBUS:00/PNP0A03:00/LNXVIDEO:00/input/input7
U: Uniq=
H: Handlers=kbd event5 
B: PROP=0
B: EV=3
B: KEY=3e000b00000000 0 0 0

I: Bus=0001 Vendor=80ee Product=cafe Version=0000
N: Name="VirtualBox mouse integration"
P: Phys=
S: Sysfs=/devices/pci0000:00/0000:00:04.0/input/input8
U: Uniq=
H: Handlers=mouse2 event6 js1 
B: PROP=0
B: EV=b
B: KEY=10000 0 0 0 0
B: ABS=3


Salidas de video:
Screen 0: minimum 16 x 16, current 1280 x 800, maximum 32767 x 32767
Virtual-1 connected primary 1280x800+0+0 (normal left inverted right x axis y axis) 0mm x 0mm
   1280x800      59.81*+
   1024x768      59.92  
   800x600       59.86  
   640x480       59.38  
   320x240       59.52  
   1152x720      59.97  
   960x600       59.63  
   928x580       59.88  
   800x500       59.50  
   768x480       59.90  
   720x480       59.71  
   640x400       59.95  
   320x200       58.96  
   1280x720      59.86  
   1024x576      59.90  
   864x486       59.92  
   720x400       59.55  
   640x350       59.77  

Tarjetas de sonido:
**** Lista de PLAYBACK dispositivos hardware ****
tarjeta 0: I82801AAICH [Intel 82801AA-ICH], dispositivo 0: Intel ICH [Intel 82801AA-ICH]
  Subdispositivos: 1/1
  Subdispositivo #0: subdevice #0
  
  
#!/bin/bash
echo "Dispositivos de bloque:"
lsblk
echo "Dispositivos USB:"
lsusb
echo "Dispositivos PCI:"
lspci
echo "Dispositivos de entrada:"
cat /proc/bus/input/devices
echo "Salidas de video:"
xrandr
echo "Tarjetas de sonido:"
aplay -l
~~~

Modifique el script para guardar la salida en un archivo llamado __resumendispositivos.txt__.
~~~
output_file="resumendispositivos.txt"

echo "Dispositivos de bloque:" > "$output_file"
lsblk >> "$output_file"

echo -e "\nDispositivos USB:" >> "$output_file"
lsusb >> "$output_file"

echo -e "\nDispositivos PCI:" >> "$output_file"
lspci >> "$output_file"

echo -e "\nDispositivos de entrada:" >> "$output_file"
cat /proc/bus/input/devices >> "$output_file"

echo -e "\nSalidas de video:" >> "$output_file"
xrandr >> "$output_file"

echo -e "\nTarjetas de sonido:" >> "$output_file"
aplay -l >> "$output_file"

echo "El resumen de dispositivos se ha guardado en $output_file"
~~~

¿Qué ventajas tiene usar un script para recopilar esta información?
Que puede servir como un reporte de los dispositivos del equipo.

¿Qué cambios realizaría para personalizar el script?
Añadir algun comando para ver cuando se realizo todo el reporte o mejorar el formato visual.

## Comandos de Entrada y Salida, Discos y Archivos
### Ejercicio 1: Montar y Desmontar Discos

Primero cree el directorioy luego monte la memoria usb que estaba en dev/sdb1
~~~
David@SistemasOperativos:~$ sudo mkdir /mnt/usb
David@SistemasOperativos:~$ sudo mount /dev/sdb1 /mnt/usb
~~~
```bash
David@SistemasOperativos:~$ df -h
S.ficheros     Tamaño Usados  Disp Uso% Montado en
tmpfs            376M   1.7M  374M   1% /run
/dev/sda2         25G   6.5G   18G  28% /
tmpfs            1.9G      0  1.9G   0% /dev/shm
tmpfs            5.0M   8.0K  5.0M   1% /run/lock
tmpfs            1.9G    16K  1.9G   1% /tmp
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-journald.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-udev-load-credentials.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-tmpfiles-setup-dev-early.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-tmpfiles-setup-dev.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-sysctl.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-tmpfiles-setup.service
tmpfs            1.0M      0  1.0M   0% /run/credentials/systemd-resolved.service
tmpfs            376M   120K  376M   1% /run/user/1000
/dev/sdb1        7.3G    16K  7.3G   1% /mnt/usb
```
Siendo el ultimo


Pase un archivo al directorio llamado prueba.txt:
~~~
David@SistemasOperativos:~$ cp archivo.txt /mnt/usb/
~~~

Y la desmonte con:
~~~
David@SistemasOperativos:~$ sudo umount /mnt/usb
~~~

### Ejercicio 2: Redirección de Entrada y Salida
Hago el listado de archivos con:
~~~
 David@SistemasOperativos:~$ ls -l > listado.txt
~~~
Luego se llama desde la terminal
```bash
David@SistemasOperativos:~$ cat listado.txt
total 72
-rw-rw-r-- 1 David David  1039 dic 14 14:05 bitacora.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Descargas
-rwxrwxr-x 1 David David   828 dic 11 12:32 dispositivos.sh
drwxr-xr-x 2 David David  4096 dic  4 11:06 Documentos
drwxr-xr-x 2 David David  4096 dic  4 11:06 Escritorio
-rw-rw-r-- 1 David David 14270 dic 11 19:31 Guardado.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Imágenes
-rw-rw-r-- 1 David David     0 dic 14 14:12 listado.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Música
drwxr-xr-x 2 David David  4096 dic  4 11:06 Plantillas
-rw-rw-r-- 1 David David    24 dic 14 14:06 prueba.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Público
-rw-rw-r-- 1 David David  5286 dic 11 19:37 resumendispositivos.txt
drwx------ 6 David David  4096 dic 10 15:00 snap
drwxr-xr-x 2 David David  4096 dic  4 11:06 Vídeos
```

Luego se usa el siguiente comando para añadir la fecha al archivo:
~~~
date >> listado.txt
~~~
Y en la terminal sale como:
```bash
David@SistemasOperativos:~$ cat listado.txt
total 72
-rw-rw-r-- 1 David David  1039 dic 14 14:05 bitacora.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Descargas
-rwxrwxr-x 1 David David   828 dic 11 12:32 dispositivos.sh
drwxr-xr-x 2 David David  4096 dic  4 11:06 Documentos
drwxr-xr-x 2 David David  4096 dic  4 11:06 Escritorio
-rw-rw-r-- 1 David David 14270 dic 11 19:31 Guardado.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Imágenes
-rw-rw-r-- 1 David David     0 dic 14 14:12 listado.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Música
drwxr-xr-x 2 David David  4096 dic  4 11:06 Plantillas
-rw-rw-r-- 1 David David    24 dic 14 14:06 prueba.txt
drwxr-xr-x 2 David David  4096 dic  4 11:06 Público
-rw-rw-r-- 1 David David  5286 dic 11 19:37 resumendispositivos.txt
drwx------ 6 David David  4096 dic 10 15:00 snap
drwxr-xr-x 2 David David  4096 dic  4 11:06 Vídeos
sáb 14 dic 2024 14:16:37 CST
```

### Ejercicio 3: Copiar y Mover Archivos
Creo un archivo con:
~~~
echo "Este es un archivo de prueba" > archivo1.txt
~~~

Movi el archivo l siguiente directorio:
~~~
cp archivo1.txt /tmp/
~~~

Renomnro el archivo:
~~~
mv /tmp/archivo1.txt /tmp/archivo2.txt
~~~

Y lo paso al directorio original:
~~~
mv /tmp/archivo2.txt .
~~~
con ls salen los archivos en home, ahi se ve el archivo1 y el 2:
```bash
David@SistemasOperativos:~$ ls
archivo1.txt
archivo2.txt
bitacora.txt
Descargas
dispositivos.sh
Documentos
Escritorio
Guardado.txt
Imágenes
listado.txt
Música
Plantillas
prueba.txt
Público
resumendispositivos.txt
snap
Vídeos
```
### Ejercicio 4: Comprimir y Descomprimir Archivos
Creo el directorio con:
```bash
David@SistemasOperativos:~$ sudo mkdir /backup/
```

Y le paso los siguiente archivos que habia hecho en el ejercicio anterior (se usa sudo por que el directorio se creo con permisos de superusuario):
```bash
David@SistemasOperativos:~$ sudo cp archivo1.txt /backup/
David@SistemasOperativos:~$ sudo cp archivo1.txt /backup/
```

Al usar el comando para comprimir sale lo siguiente:
```bash
David@SistemasOperativos:~$ tar -czvf backup.tar.gz /backup/
tar: Eliminando la `/' inicial de los nombres
/backup/
/backup/archivo2.txt
/backup/archivo1.txt
```
tar elimina / para evitar problemas

Para borrar el directorio con todo y archivos, usé el siguiente comando:
```bash
David@SistemasOperativos:~$ sudo rm -r /backup/
```

El archivo comprimido se muestra en el homre:
```bash
David@SistemasOperativos:~$ ls
archivo1.txt   Descargas    	Guardado.txt  Plantillas           	snap
archivo2.txt   dispositivos.sh  Imágenes  	prueba.txt           	Vídeos
backup.tar.gz  Documentos   	listado.txt   Público
bitacora.txt   Escritorio   	Música    	resumendispositivos.txt
```

Y use el siguiente comando para descomprimir y mostró esto:
```bash
David@SistemasOperativos:~$ tar -xzvf backup.tar.gz
backup/
backup/archivo2.txt
backup/archivo1.txt
```

### Ejercicio 5: Permisos y Propiedades de Archivos

Cree un archivo con:
```bash
David@SistemasOperativos:~$ touch privado.txt
```

Se cambian los permisos del archivo para que solo el propietario pueda leer y escribir:
```bash
David@SistemasOperativos:~$ chmod 600 privado.txt
```

Para usar el siguiente comando se necesita darle permisos a otro usuario, pero no hay mas en el sistema asi que cree uno de la siguiente manera:
```bash
David@SistemasOperativos:~$ sudo adduser invitado1
[sudo] contraseña para David:
info: Añadiendo el usuario `invitado1' ...
info: Selecting UID/GID from range 1000 to 59999 ...
info: Añadiendo el nuevo grupo `invitado1' (1001) ...
info: Adding new user `invitado1' (1001) with group `invitado1 (1001)' ...
info: Creando el directorio personal `/home/invitado1' ...
info: Copiando los ficheros desde `/etc/skel' ...
Nueva contraseña:
CONTRASEÑA INCORRECTA: No se ha proporcionado ninguna contraseña
Vuelva a escribir la nueva contraseña:
Las contraseñas no coinciden.
Nueva contraseña:
Vuelva a escribir la nueva contraseña:
passwd: contraseña actualizada correctamente
Cambiando la información de usuario para invitado1
Introduzca el nuevo valor, o presione INTRO para el predeterminado
	Nombre completo []:
	Número de habitación []:
	Teléfono del trabajo []:
	Teléfono de casa []:
	Otro []:
¿Es correcta la información? [S/n] S
info: Adding new user `invitado1' to supplemental / extra groups `users' ...
info: Añadiendo al usuario `invitado1' al grupo `users' ...

```

Ahora si uso el comando para cambiar propietario:
```bash
David@SistemasOperativos:~$ sudo chown invitado1 privado.txt
```

Y ahora aparece asi cuando lo quiero abrir con mi usuario normal:
![Permiso denegado](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Listar_disp_conectados/Permiso%20denegado.jpg?raw=true)

### Ejercicio 6: Exploración de Dispositivos
Al usar el comando lbslk sale los disco y particiones, asi como la memoria que inserté:
```bash
David@SistemasOperativos:~$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
loop0	7:0	0 	4K  1 loop /snap/bare/5
loop1	7:1	0  73.9M  1 loop /snap/core22/1722
loop2	7:2	0  11.7M  1 loop /snap/desktop-security-center/32
loop3	7:3	0  74.2M  1 loop /snap/core22/1621
loop4	7:4	0   272M  1 loop /snap/firefox/5091
loop5	7:5	0 273.7M  1 loop /snap/firefox/5437
loop6	7:6	0  10.7M  1 loop /snap/firmware-updater/127
loop7	7:7	0  11.1M  1 loop /snap/firmware-updater/147
loop8	7:8	0 505.1M  1 loop /snap/gnome-42-2204/176
loop9	7:9	0  91.7M  1 loop /snap/gtk-common-themes/1535
loop10   7:10   0  89.7M  1 loop /snap/gtk-common-themes/1536
loop11   7:11   0  10.7M  1 loop /snap/snap-store/1218
loop12   7:12   0	14M  1 loop /snap/prompting-client/51
loop13   7:13   0  38.8M  1 loop /snap/snapd/21759
loop14   7:14   0   568K  1 loop /snap/snapd-desktop-integration/253
loop15   7:15   0   564K  1 loop /snap/snapd-desktop-integration/247
loop16   7:16   0  44.3M  1 loop /snap/snapd/23258
sda  	8:0	0  25.5G  0 disk
├─sda1   8:1	0 	1M  0 part
└─sda2   8:2	0  25.5G  0 part /
sdb  	8:16   1   7.3G  0 disk
└─sdb1   8:17   1   7.3G  0 part /media/David/ESD-USB
sr0 	11:0	1  1024M  0 rom  
```

Si pongo la direccion de la memoria USB sale el siguiente tamaño del contenido:
```bash
David@SistemasOperativos:~$ du -sh /media/David/ESD-USB
20K	/media/David/ESD-USB
```

Y con df -h verificó el uso de la memoria:
```bash
David@SistemasOperativos:~$ df -h
S.ficheros 	Tamaño Usados  Disp Uso% Montado en
tmpfs        	376M   1.7M  374M   1% /run
/dev/sda2     	25G   6.5G   18G  28% /
tmpfs        	1.9G  	0  1.9G   0% /dev/shm
tmpfs        	5.0M   8.0K  5.0M   1% /run/lock
tmpfs        	1.9G	16K  1.9G   1% /tmp
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-journald.service
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-udev-load-credentials.service
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-tmpfiles-setup-dev-early.service
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-tmpfiles-setup-dev.service
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-sysctl.service
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-tmpfiles-setup.service
tmpfs        	1.0M  	0  1.0M   0% /run/credentials/systemd-resolved.service
tmpfs        	376M   132K  376M   1% /run/user/1000
/dev/sdb1    	7.3G	20K  7.3G   1% /media/David/ESD-USB
```

### Ejercicio 7: Crear y Formatear Particiones
Al usar el comando 
~~~
sudo fdisk -l
~~~

Identifique el tamaño de la memoria, asi que elegi ese para la particion:
~~~
Disco /dev/sdb: 7.27 GiB, 7803174912 bytes, 15240576 sectores
Disk model: DT 101 G2  	 
Unidades: sectores de 1 * 512 = 512 bytes
Tamaño de sector (lógico/físico): 512 bytes / 512 bytes
Tamaño de E/S (mínimo/óptimo): 512 bytes / 512 bytes
Tipo de etiqueta de disco: dos
Identificador del disco: 0x35538f5b
~~~

Asi que use el siguient comando para la particion:
```bash
David@SistemasOperativos:~$ sudo fdisk /dev/sdb

Bienvenido a fdisk (util-linux 2.40.2).
Los cambios solo permanecerán en la memoria, hasta que decida escribirlos.
Tenga cuidado antes de utilizar la orden de escritura.
```

Use la opcion o para una nueva etiqueta 
```bash
  g   crea una nueva tabla de particiones GPT vacía
   G   crea una nueva tabla de particiones SGI (IRIX) vacía
   o   create a new empty MBR (DOS) partition table
   s   crea una nueva tabla de particiones Sun vacía


Orden (m para obtener ayuda): g
Failed to create 'gpt' disk label: No queda espacio en el dispositivo

Orden (m para obtener ayuda): o

Created a new DOS (MBR) disklabel with disk identifier 0x0882a3ab.
```

y cree la particion de la siguiente manera:
```bash
Orden (m para obtener ayuda): n
Tipo de partición
   p   primaria (0 primary, 0 extended, 4 free)
   e   extendida (contenedor para particiones lógicas)
Seleccionar (valor predeterminado p): p
Número de partición (1-4, valor predeterminado 1): 1
Primer sector (0-4294967295, valor predeterminado 0): 0
Last sector, +/-sectors or +/-size{K,M,G,T,P} (0-4294967295, valor predeterminado 4294967295): 0-4294967295
Last sector, +/-sectors or +/-size{K,M,G,T,P} (0-4294967295, valor predeterminado 4294967295): 4294967295

Crea una nueva partición 1 de tipo 'Linux' y de tamaño 2 TiB.
```

Despues se formatea la particion:
```bash
David@SistemasOperativos:~$ sudo mkfs.ext4 /dev/sdb1
mke2fs 1.47.1 (20-May-2024)
/dev/sdb1 contiene un sistema de ficheros vfat etiquetado 'ESD-USB'
¿Continuar de todas formas? (s,N) s
Se está creando un sistema de ficheros con 1904640 bloques de 4k y 476720 nodos-i
UUID del sistema de ficheros: 61af20ad-07bf-4aa4-9cc0-8bf3f28a32fa
Respaldos del superbloque guardados en los bloques:
	32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632

Reservando las tablas de grupo: hecho                       	 
Escribiendo las tablas de nodos-i: hecho                       	 
Creando el fichero de transacciones (16384 bloques):
hecho
Escribiendo superbloques y la información contable del sistema de archivos:  0/5hecho
```

Ahora creo un directorio para montar ahi la particion:
```bash
David@SistemasOperativos:~$ sudo mkdir /mnt/nueva_particion
David@SistemasOperativos:~$ sudo mount /dev/sdb1 /mnt/nueva_particion
```

Y creó un archivo en el directorio:
```bash
David@SistemasOperativos:~$ sudo echo "Prueba de escritura" > /mnt/nueva_particion/test.txt
David@SistemasOperativos:~$ ls /mnt/nueva_particion
lost+found  test.txt
```