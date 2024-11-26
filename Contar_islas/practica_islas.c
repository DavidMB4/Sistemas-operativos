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
