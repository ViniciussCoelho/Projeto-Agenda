#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  fseek(file, 0, SEEK_END);
  return ftell(file)/sizeof(struct Contact);
}
int validEmail(char* email) {
  int count = 0;
  for (int i = 0; i < strlen(email);i++){
    if(email[i] == '@'){
      count++;
    }
  }

  return count == 1;
}

void insert(){
  FILE *file = openFile("a+");
  struct Contact contact;
  int lastRow = getLastRow(file);

  printf("\nDigite o nome:");
  scanf("%s", contact.name);
  int isValidEmail = 0;
  do{
    printf("\nDigite o email:");
    scanf("%s", contact.email);
    isValidEmail = validEmail(contact.email);
  } while (isValidEmail != 1);
  printf("\nDigite o telefone:");
  scanf("%s", contact.phone);
  contact.status = 1;
  contact.id = lastRow++;
  fwrite(&contact, sizeof(struct Contact), 1, file);
  fclose(file);
}

void removeContact() {
 FILE *file = openFile("r+");
  int id;
  struct Contact contact;
  printf("Qual o ID do contato que deseja excluir? ");
  scanf("%d", &id);

  while (fread(&contact, sizeof(struct Contact), 1, file)) {
    if(contact.id == id) {
      contact.status = 0;
      fseek(file, id*sizeof(struct Contact), SEEK_SET);
      fwrite(&contact, sizeof(struct Contact), 1, file);
      break;
    }
  }
  fclose(file);
}
void update(){
 FILE *file = openFile("r+");
  int id,isValidEmail;
  struct Contact newContact;
  struct Contact contact;
  printf("Qual o ID do contato que deseja editar? ");
  scanf("%d", &id);
  
  printf("\nDigite o novo nome: ");
  scanf("%s", newContact.name);
  do{
    printf("\nDigite o novo email:");
    scanf("%s", newContact.email);
    isValidEmail = validEmail(contact.email);
  } while (isValidEmail != 1);

  printf("\nDigite o novo telefone:");
  scanf("%s", newContact.phone);
  
  while (fread(&contact, sizeof(struct Contact), 1, file)) {
    if(contact.id == id) {
      newContact.id = contact.id;
      newContact.status = contact.status;
      fseek(file, id*sizeof(struct Contact), SEEK_SET);
      fwrite(&newContact, sizeof(struct Contact), 1, file);
      break;
    }
  }
  fclose(file);
}

void list(){
  FILE* file = openFile("r");
  struct Contact contact;
  while(fread(&contact, sizeof(struct Contact), 1, file)){
    if(contact.status != 0) {
      printf("ID: %d Nome: %s Email: %s Telefone: %s\n",
             contact.id,
             contact.name,
             contact.email,
             contact.phone);
      printf("--------------------------------------------------------\n");
    }
  }
}

// int minimum(int x, int y, int z){	
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

// int cost() {
//   	for (i = 1; i <= contact; i++)
//         m[i][0] = m[i-1][0] + 1;
//     for (j = 1; j <= a; j++)
//         m[0][j] = m[0][j-1] + 1;
//     for (i = 1; i <= b; i++)
//         for (j = 1; j <= a; j++)
//             m[i][j] = minimum(m[i-1][j] + 1, m[i][j-1] + 1, m[i-1][j-1] + (palavra1[j-1] == palavra2[i-1] ? 0 : 1));

//     cost = m[b][a];

//     return cost;
// }

// void search(char *src){
//   FILE *file = openFile("r");
//   struct Contact contact;

//   printf("Digite o nome do contato que deseja buscar: ");
// 	scanf("%s",contact.name);
//   struct Contact contact;
//   int matrix[1][2];
//   while(fread(&contact, sizeof(struct Contact), 1, file)){
//     if(contact.status != 0) {
//       // Achar custo
//       // Adicionar Id e custo na matriz
//     }
//   }
//   // Ordenar matriz
//   // Imprimir
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