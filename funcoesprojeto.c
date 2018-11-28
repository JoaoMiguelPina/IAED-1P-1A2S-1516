#include "projeto.h"
#include <stdio.h>
#include <string.h>


void adiciona_aeroporto(char code[], int capacidade) {
    int i,j;
    if (capacidade <= 0) return;
    if (strlen(code) != MAXCHARLEN) return;
    for (i=0; code[i] != '\0'; i++)
	if (code[i] < 'A' || code[i] > 'Z') return;
    
    
    aeroporto novo;
    strcpy(novo.code, code);
    novo.capmax = capacidade;
    novo.state = 1;
    
    aeroportos[indice_atual] = novo;
    
    
    for (i=0,j=0; i<=indice_atual && j<=indice_atual; i++, j++) {
        matriz[i][indice_atual] = 0;
        matriz[indice_atual][j] = 0;
    }
    indice_atual++;
}

int conta_voos_entra(int indice) {
    int i, voos_entra = 0;
    for (i=0; i<indice_atual;i++)
        voos_entra+=matriz[i][indice];
        
    return voos_entra;
}



int conta_voos_sai(int indice) {
    int j, voos_sai = 0;
    for (j=0; j<indice_atual;j++)
        voos_sai+=matriz[indice][j];
        
    return voos_sai;
}



int indice_aeroporto(char code[]) {
     int indice;
     for (indice=0; indice<indice_atual; indice++) 
        if (strcmp(code, aeroportos[indice].code) == 0) break;
     return indice;
}



void altera_capacidade_max(char code[], int capacidade) {
     
     int indice = indice_aeroporto(code);  
     if (indice==indice_atual){    /*se o aeroporto nao estiver definido, o indice estara num local onde nao existe informacao util*/
        printf("Capacidade de %s inalterada\n", code);
        return;
     }
     int total_voos = conta_voos_entra(indice) + conta_voos_sai(indice);
     int nova_capacidade = aeroportos[indice].capmax + capacidade;
     if (nova_capacidade < 0 || nova_capacidade < total_voos || aeroportos[indice].state == 0)  {
        printf("*Capacidade de %s inalterada\n", code);
        return;
     }
     else aeroportos[indice].capmax = nova_capacidade;
}  
    
       

void adiciona_voo(char code1[], char code2[]) {
    int indice_code1 = indice_aeroporto(code1), indice_code2 = indice_aeroporto(code2);
      
    if (indice_code1==indice_atual || indice_code2==indice_atual || aeroportos[indice_code1].state == 0 || aeroportos[indice_code2].state == 0 || conta_voos_sai(indice_code1) + conta_voos_entra(indice_code1) > (aeroportos[indice_code1].capmax - 2) || conta_voos_sai(indice_code2) + conta_voos_entra(indice_code2) > (aeroportos[indice_code2].capmax - 2)){    
        printf("*Impossivel adicionar voo RT %s %s\n", code1, code2);
        return; }
        
    matriz[indice_code1][indice_code2]++;
    matriz[indice_code2][indice_code1]++;
 }   




void adiciona_rota(char code1[], char code2[]) {
    int indice_code1 = indice_aeroporto(code1), indice_code2 = indice_aeroporto(code2);
    
    if (indice_code1==indice_atual || indice_code2==indice_atual || aeroportos[indice_code1].state == 0 || aeroportos[indice_code2].state == 0 || conta_voos_sai(indice_code1) + conta_voos_entra(indice_code1) > (aeroportos[indice_code1].capmax - 1) || conta_voos_sai(indice_code2) + conta_voos_entra(indice_code2) > (aeroportos[indice_code2].capmax - 1)){    
        printf("*Impossivel adicionar voo %s %s\n", code1, code2);
        return; }
        
    matriz[indice_code1][indice_code2]++;
    
}


void remove_voo(char code1[], char code2[]) {
    int indice_code1 = indice_aeroporto(code1), indice_code2 = indice_aeroporto(code2);
    if (conta_voos_sai(indice_code1) < 1 || conta_voos_entra(indice_code2) < 1) {
        printf("*Impossivel remover voo %s %s\n", code1, code2);
        return;}
    matriz[indice_code1][indice_code2]--;
}

void remove_voo_ida_volta(char code1[], char code2[]) {
    int indice_code1 = indice_aeroporto(code1), indice_code2 = indice_aeroporto(code2);
    if (conta_voos_sai(indice_code1) < 2 || conta_voos_entra(indice_code2) < 2 || indice_code1==indice_atual || indice_code2==indice_atual || aeroportos[indice_code1].state == 0 || aeroportos[indice_code2].state == 0) {
        printf("*Impossivel remover voo RT %s %s\n", code1, code2);
        return;}
    matriz[indice_code1][indice_code2]--;
    matriz[indice_code2][indice_code1]--;
}
    
    
    
void numero_voos(char code1[], char code2[]) {
    int indice_code1 = indice_aeroporto(code1), indice_code2 = indice_aeroporto(code2);
    if (indice_code1==indice_atual){
        printf("Aeroporto %s inexistente\n", code1);
        if (indice_code2==indice_atual){ 
            printf("Aeroporto %s inexistente\n", code2);
            return;}
        else return;}
    printf("Voos entre cidades %s:%s:%d:%d\n", code1, code2, matriz[indice_code1][indice_code2], matriz[indice_code2][indice_code1]);
}
        

void mais_voos() {
    int indice_maior=0, i, voos;
    int voos_total = conta_voos_sai(indice_maior) + conta_voos_entra(indice_maior);
    for (i=0; i<indice_atual; i++) {
        voos = conta_voos_sai(i) + conta_voos_entra(i);
        if (voos > voos_total) {
            voos_total = voos;
            indice_maior = i;
        }
    } 
    printf("Aeroporto com mais rotas %s:%d:%d\n", aeroportos[indice_maior].code, conta_voos_sai(indice_maior), conta_voos_entra(indice_maior));   
}


void mais_conectado() {
    int i, j, contador= 0, contador_atual = 0, big_connect = 0;
    
    for (i=0; i<indice_atual; i++) {
    contador = 0;
        for (j = 0; j<indice_atual; j++) {
            if (matriz[i][j] != 0) 
                contador++;
            else if (matriz[i][j] == 0 && matriz[j][i] != 0)
                contador++;}
        if (contador > contador_atual) {
            contador_atual = contador;
            big_connect = i;}}
    printf("Aeroporto com mais ligacoes %s:%d\n", aeroportos[big_connect].code, contador_atual);
    }
        
 
 void mais_popular() {
    int i, j, max = 0, indice_i = 0, indice_j = 0;
    
    for (i = 0; i<indice_atual; i++) {
        for (j=0; j<indice_atual; j++) {
            if (matriz[i][j] > max) {
                max = matriz[i][j];
                indice_i = i;
                indice_j = j;
            }
        }
    }
    printf("Voo mais popular %s:%s:%d\n", aeroportos[indice_i].code, aeroportos[indice_j].code, max);
}
                           
                
            
     
    


void encerra(char code[]) {
    int indice = indice_aeroporto(code), i;
    if (indice == indice_atual) {
        printf("*Aeroporto %s inexistente\n", code);
        return; }
    for (i=0; i<indice_atual; i++) {
        matriz[indice][i] = 0;
        matriz[i][indice] = 0;}
    aeroportos[indice].state = 0;
}
        

void reabre(char code[]) {
    int indice = indice_aeroporto(code);
    
    if (indice == indice_atual) {
        printf("*Aeroporto %s inexistente\n", code);
        return; }
    if (aeroportos[indice].state == 1){ 
        printf("O aeroporto encontra se aberto\n");
        return; }
    aeroportos[indice].state = 1;
}


void listagem0() {
    int i;
    for (i=0;i<indice_atual;i++)
        printf("%s:%d:%d:%d\n", aeroportos[i].code, aeroportos[i].capmax, conta_voos_sai(i), conta_voos_entra(i));
}  
 
void listagem1() {
    int i, j, a, b;
    aeroporto copia_aeroportos[indice_atual];
    aeroporto copia;
    
    for (b = 0; b<indice_atual; b++)      /*copiamos todos os codigos dos aeroportos para o vetor novo*/
        strcpy(copia_aeroportos[b].code, aeroportos[b].code);
    for (b = 0; b<indice_atual; b++)      /*copiamos o estado dos aeroportos para o vetor novo*/
        copia_aeroportos[b].state = aeroportos[b].state;
    for (b = 0; b<indice_atual; b++)      /*copiamos a capacidade maxima dos aeroportos para o vetor novo*/
        copia_aeroportos[b].capmax = aeroportos[b].capmax;
         
    
    for (i = 1; i<indice_atual; i++) {
        for (j = 1; j<indice_atual;j++) {
        
            if (strcmp(copia_aeroportos[j-1].code, copia_aeroportos[j].code) > 0) {
                strcpy(copia.code, copia_aeroportos[j-1].code);
                copia.capmax = copia_aeroportos[j-1].capmax;
                strcpy(copia_aeroportos[j-1].code, copia_aeroportos[j].code);
                copia_aeroportos[j-1].capmax = copia_aeroportos[j].capmax;
                strcpy(copia_aeroportos[j].code, copia.code);
                copia_aeroportos[j].capmax = copia.capmax;
                
            }
        }
    }
    for (a = 0; a<indice_atual; a++)
        
        printf("%s:%d:%d:%d\n", copia_aeroportos[a].code, copia_aeroportos[a].capmax, conta_voos_sai(indice_aeroporto(copia_aeroportos[a].code)), conta_voos_entra(indice_aeroporto(copia_aeroportos[a].code)));
    
}

    
void listagem2() {
    int i;
    int numero_voos[indice_atual];
    
    
    for (i = 0; i<indice_atual; i++)
        numero_voos[i] = conta_voos_entra(i) + conta_voos_sai(i);
    
    int maximo = maior_numero(numero_voos);
    int contador[maximo];
      
    for (i = 0; i<=maximo; i++) 
        contador[i] =0;
    
    for (i = 0; i<indice_atual; i++) 
        contador[numero_voos[i]]++;
       
    for (i = 0; i<=maximo; i++) 
        if (contador[i] != 0) printf("%d:%d\n", i, contador[i]);
        
}

int maior_numero(int vetor[]) {
    int maior = 0, i;
    for (i = 0; i < indice_atual; i++) {
        if (vetor[i] > maior)
            maior = vetor[i];
    }
    return maior;
}  
