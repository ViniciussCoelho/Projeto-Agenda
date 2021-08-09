#include <stdio.h>

typedef struct {
  char name[30];
  char email[30]; 
  char phone[30];
  int status;
  int id;
} Contact;

void insert(){
  printf("inserir");
}
void removeContact(){
  printf("remover");
}
void update(){
  printf("atualizar");
}
void list(){
  printf("listar");
}
void search(char *src){
  printf("pesquisa %s", src);
}

void menu(){
  int resp;
  do
  {
    printf("1. Incluir\n2. Excluir\n3. Alterar\n4. Listar\n5. Buscar\n0. Sair\n");
    scanf("%i", &resp);
    switch (resp)
    {
      case 1:
        insert();
        break;
      case 2:
        removeContact();
        break;
      case 3:
        update();
        break;
      case 4:
        list();
        break;
      case 5:
        search("as");
        break;
      default:
        break;
    }
  } while (resp != 0);
}

int main(int argc, char const *argv[])
{
  menu();
  return 0;
}