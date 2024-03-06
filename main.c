#include "functions.h"

int main(){
    Queue *huffmanList = createHuffmanQueue(); //Cria uma fila de prioridade
    HashTable *table = createHashTable(); //Cria uma tabela vazia
    FILE *f; //Declara o arquivo "f"

    printf("Por favor, insira o caminho do arquivo que deseja compactar: ");

    //Cria o buffer onde será armazenado o caminho do arquivo escolhido pelo usuário
    char buffer[1000];
    
    //Lê o caminho do arquivo pela entrada padrão e o armazena no buffer
    fgets(buffer, sizeof(buffer), stdin);

    //Substitui a quebra de linha no final pelo caractere de término de string
    buffer[strcspn(buffer, "\n")] = '\0';

    /*
    Abre o arquivo cujo caminho está armazenado no buffer 
    em modo de leitura de bytes
    */
    f = fopen(buffer, "rb");

    //Calcula e armazena o tamanho do arquivo
    long int fSize = fileSize(f);

    /*
    Se houver algum problema na abertura do arquivo ou ele for vazio,
    encerra o programa
    */
    if(f == NULL || fSize == 0){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    //Passa por cada byte do arquivo, adicionando-o à tabela de frequências
    for(int i = 0; i < fSize; i++){
        // Aloca dinamicamente um ponteiro para void
        void *byteP = malloc(sizeof(unsigned char));

        // Lê um byte e o armazena como um inteiro
        fread(byteP, sizeof(unsigned char), 1, f);

        // Adiciona o ponteiro para void à tabela, atualizando sua frequência
        put(table, byteP);
    }

    //Passa por todos os elementos não nulos da tabela adicionando-os à fila de prioridade
    for(int i = 0; i < 256; i++){
        if(table->table[i] != NULL){
            enqueue(huffmanList, table->table[i]->value, table->table[i]->frequency);
        }
    }

    //Imprime a fila
    printQueue(huffmanList);

    //Cria a árvore de Huffman usando a fila contendo os bytes do arquivo
    Node *huffmanTree = createBinaryHuffmanTree(huffmanList->head);

    //Imprime a árvore em pré-ordem
    printHuffmanTreePreOrder(huffmanTree);

    //Fecha o arquivo "f"
    fclose(f);
    return 0;
}
