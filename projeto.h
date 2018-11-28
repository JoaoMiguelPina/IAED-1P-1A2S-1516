#define MAXCHARLEN 3
#define MAXAEROPORTOS 1000

typedef struct { char code[MAXCHARLEN]; int capmax; int state; } aeroporto;
typedef struct { aeroporto a1; aeroporto a2; } voo;


int matriz[MAXAEROPORTOS][MAXAEROPORTOS];
int contador_aeroportos, indice_atual;
aeroporto aeroportos[MAXAEROPORTOS];


void adiciona_aeroporto(char code[], int capacidade);
void altera_capacidade_max(char code[], int capacidade);
void adiciona_voo(char code1[], char code2[]);
void adiciona_rota(char code1[], char code2[]);
void remove_voo(char code1[], char code2[]);
void remove_voo_ida_volta(char code1[], char code2[]);
void numero_voos(char code1[], char code2[]);
void mais_voos();
void mais_conectado();
void mais_popular();
void encerra(char code[]);
void reabre(char code[]);
void listagem0();
void listagem1();
void listagem2();

/*funcoes auxiliares*/
int conta_voos_entra(int indice);
int conta_voos_sai(int indice);
int indice_aeroporto(char code[]);
int maior_numero(int vetor[]);
