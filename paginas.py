import random

max_paginas = 100
max_procesos = 10
tam_pagina = 4

tabla_paginas = []
for i in range (max_paginas):
    tam_pagina[i] = -1
    
def asignar_proceso(id_proceso, tamano_proceso):    
    num_paginas = (tamano_proceso + tam_pagina - 1) // tam_pagina
    paginas_asignadas = 0
    paginas_disponibles = 0
    
    for i in range (max_paginas):
        if tam_pagina[i] == -1:
            paginas_disponibles = paginas_disponibles + 1
            
    if paginas_disponibles >= num_paginas:
        while paginas_asignadas < num_paginas:
            pagina = random.randint(0, len(tabla_paginas) - 1)  
            if tabla_paginas[pagina] == -1: 
                tabla_paginas[pagina] = id_proceso 
                paginas_asignadas += 1
                
    print(f"No hay suficiente memoria para asignar el proceso {id_proceso}.")
    
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
        print("2. Liberar proceso")
        print("3. Mostrar estado de la tabla de páginas")
        print("4. Salir")
        opcion = int(input("Seleccione una opción: "))

        if opcion == 1:
            id_proceso = int(input("Ingrese el ID del proceso: "))
            tamano_proceso = int(input("Ingrese el tamaño del proceso (KB): "))
            asignar_proceso(id_proceso, tamano_proceso)
        elif opcion == 2:
            num_acceso = int(input("Ingrese el numero de accesos aleatorios: "))
            acceso_aleatorio(num_acceso)
        elif opcion == 3:
            
        elif opcion == 4:
            print("Saliendo del programa.")
            break
        else:
            print("Opción no válida.")