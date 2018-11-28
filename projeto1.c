#include <stdio.h>
#include <string.h>
#include "projeto.h"



int main() {
    char id[MAXCHARLEN], c, id2[MAXCHARLEN];
    int capacidade, valor, i, total_voos = 0;
    indice_atual = 0;
    c = getchar();
    while (c != 'X') {
        switch (c) {
            case 'A':
                getchar();
                scanf("%s", id);
                scanf("%d", &capacidade);
                adiciona_aeroporto(id, capacidade);
                break;
            case 'I':
                getchar();
                scanf("%s", id);
                scanf("%d", &capacidade);
                altera_capacidade_max(id, capacidade);
                break;
            case 'F':
                getchar();
                scanf("%s", id);
                scanf("%s", id2);
                adiciona_voo(id, id2);
                break;
            case 'G':
                getchar();
                scanf("%s", id);
                scanf("%s", id2);
                adiciona_rota(id, id2);
                break;
            case 'R':
                getchar();
                scanf("%s", id);
                scanf("%s", id2);
                remove_voo(id, id2);
                break;
            case 'S':
                getchar();
                scanf("%s", id);
                scanf("%s", id2);
                remove_voo_ida_volta(id, id2);
                break;
            case 'N':
                getchar();
                scanf("%s", id);
                scanf("%s", id2);
                numero_voos(id, id2);
                break;
            case 'P':
                mais_voos();
                break;
            case 'Q':
                mais_conectado();
                break;
            case 'V':
                mais_popular();
                break;
            case 'C':
                getchar();
                scanf("%s", id);
                encerra(id);
                break;
            case 'O':
                getchar();
                scanf("%s", id);
                reabre(id);
                break;
            case 'L':
                getchar();
                scanf("%d", &valor);
                if (valor==0) listagem0();
                else if(valor==1) listagem1();
                else if(valor==2) listagem2();
                break;
        }
        getchar();
        c = getchar();
    }
    int numero_voos[indice_atual];
    for (i = 0; i<indice_atual; i++)
        numero_voos[i] = conta_voos_entra(i) + conta_voos_sai(i);
    for (i = 0; i<indice_atual; i++) 
        total_voos = total_voos + numero_voos[i];
    printf("%d:%d\n", (total_voos/2), (indice_atual));
    return 0;
        
}

