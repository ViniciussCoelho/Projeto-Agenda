#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[30];
    char email[30]; 
    char celular[30];
} contato;

int main () {
    int escolha, i = 0, id, z = 0;
    contato c[30];

    do {
        printf("S:\n1.Incluir um novo contato\n2.Excluir um contato existente\n3.Alterar um contato existente\n4.Listar todos os contatos cadastrados\n5.Finalizar o Programa\n");
        scanf("%d", &escolha);

        switch(escolha) {
            case 1:
                printf("Digite o nome: ");
                scanf(" %s", c[i].nome);
                printf("Digite o email: ");
                scanf(" %s", c[i].email);
                printf("Digite o número de celular: ");
                scanf(" %s", c[i].celular);
                i++;
            break;

            case 2:
                printf("Digite o id do contato que você deseja apagar: ");
                scanf("%d", &id);
                id--;

                for(int j = id;j<30;j++){
                c[j] = c[j+1];
                }
                i--;
                printf("Cadastro Excluido Com Sucesso\n");
            break;

            case 3:
                printf("Digite o id do contato que você deseja alterar: ");
                scanf("%d", &id);
                id--;

                printf("Digite o novo nome: ");
                printf(" %s", c[id].nome);
                printf("Digite o novo email: ");
                scanf(" %s", c[id].email);
                printf("Digite o novo número de celular: ");
                scanf(" %s", c[id].celular);
            break;

            case 4:
                for(int j = 0; j < i; j++) {
                    printf("%d. Nome: %s Email: %s Celular: %s\n", j+1, c[j].nome, c[j].email, c[j].celular);
                }
            break;

            case 5:
                return 0;
        }
    } while(escolha != 5);
}