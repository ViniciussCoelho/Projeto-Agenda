#include <stdio.h>
#include<stdlib.h>

#define FILENAME "file.txt"

struct Contact {
  char name[30];
  char email[30]; 
  char phone[30];
  int status;
  int id;
};

FILE* openFile(char* mode){
  FILE *f;
  f = fopen(FILENAME, mode);

  if (f == NULL) {
    printf("Não foi possível abrir o arquivo.");
    return 0;
  }

  return f;
}

int getLastRow(FILE* file) {
  int lines = 0;
  struct Contact *contact = malloc(sizeof(struct Contact));
  while(!feof(file)) {
    fread(contact, sizeof(struct Contact), 1, file);
    lines++;
  }
  return lines;
}

void insert(){
  FILE *file = openFile("a+");
  struct Contact *contact = malloc(sizeof(struct Contact));
  int lastRow = getLastRow(file);

  printf("\nDigite o nome:");
  scanf("%s", contact->name);
  int isValidEmail = 1;
  // do{
    printf("\nDigite o email:");
    scanf("%s", contact->email);

  // } while (isValidEmail);
  printf("\nDigite o telefone:");
  scanf("%s", contact->phone);
  contact->status = 1;
  contact->id = lastRow++;
  fwrite(contact, sizeof(struct Contact), 1, file);
  fclose(file);
}

void removeContact() {
 // FILE *file = openFile("r+");
  // int id;
  // struct Contact *contact = malloc(sizeof(struct Contact));

  // printf("Qual o ID do contato que deseja excluir? ");
  // scanf("%d", id);
  // id--;

  //contact->status = 0;
  printf("remover");
}
void update(){
  printf("atualizar");
}

void list(){
  FILE* file;
  file = openFile("r");
  struct Contact *contact = malloc(sizeof(struct Contact));
  while(!feof(file)) {
    fread(contact, sizeof(struct Contact), 1, file);
    if(contact->status != 0) {
      printf("ID: %d\nNome: %s\nEmail: %s\nTelefone: %s\n\n",
        contact->id,
        contact->name,
        contact->email,
        contact->phone
      );
    }
  }
}
void search(char *src){
  // FILE *file = openFile("r+");
  // struct Contact *contact = malloc(sizeof(struct Contact));
  


  
  

	// int a,b,i,j, custo=0;
	
	// char palavra1[a], palavra2[b];
	
	// printf("digite a primeira palavra: ");
	// scanf("%s",palavra1);
	// printf("digite a segunda palavra: ");
	// scanf("%s",palavra2);
	
	
	
	// int m[b+1][a+1];
	// m[0][0]=0;
	
	// for (i = 1; i <= b; i++)
  //       m[i][0] = m[i-1][0] + 1;
  //   for (j = 1; j <= a; j++)
  //       m[0][j] = m[0][j-1] + 1;
  //   for (i = 1; i <= b; i++)
  //       for (j = 1; j <= a; j++)
  //           m[i][j] = min(m[i-1][j] + 1, m[i][j-1] + 1, m[i-1][j-1] + (palavra1[j-1] == palavra2[i-1] ? 0 : 1));

  //   custo = m[b][a];
  //   //testado para a palavra legau e legal.
  //   printf("O custo para transformar %s em %s eh: %d", palavra1, palavra2, custo);
	
	
}
	
// int min(int x, int y, int z){	

// 	if(x <= y && x <= z){
// 		return x;
// 	}else 
// 		if(y <= x && y <= z){
// 			return y;
// 		}else 
// 			if(z <= x && z <= y){
// 				return z;
// 			}
// }

void menu(){
  int resp;
  do
  {
    printf("1. Incluir\n2. Excluir\n3. Alterar\n4. Listar\n5. Buscar\n0. Sair\n");
    scanf("%i", &resp);
    switch (resp)
    {
      case 0: break;
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
      default: printf("Essa opção não e válida.");
        break;
    }
  } while (resp != 0);
}

int main(int argc, char const *argv[])
{
  menu();
  return 0;
}