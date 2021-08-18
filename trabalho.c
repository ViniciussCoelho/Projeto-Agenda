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

struct Temp {
  int id;
  char name[30];
  char email[30]; 
  char phone[30];
  int cost;
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
    if(!isValidEmail) printf("Entre com um email válido.");
  } while (!isValidEmail);
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
    isValidEmail = validEmail(newContact.email);
  } while (!isValidEmail);

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
  FILE* file = openFile("r+");
  struct Contact contact;
  printf("------------------------------------------------------------------------\n");
  while(fread(&contact, sizeof(struct Contact), 1, file)){
    if(contact.status != 0) {
      printf("ID: %d Nome: %s Email: %s Telefone: %s\n",
             contact.id,
             contact.name,
             contact.email,
             contact.phone);
      printf("------------------------------------------------------------------------\n");
    }
  }
  fclose(file);
}

int distance(const char * word1, int len1,const char * word2,int len2) {
  int matrix[len1 + 1][len2 + 1];
  int i;
  for (i = 0; i <= len1; i++) {
    matrix[i][0] = i;
  }
  for (i = 0; i <= len2; i++) {
    matrix[0][i] = i;
  }
  for (i = 1; i <= len1; i++) {
    int j;
    char c1;

    c1 = word1[i-1];
    for (j = 1; j <= len2; j++) {
      char c2;

      c2 = word2[j-1];
      if (c1 == c2) {
        matrix[i][j] = matrix[i-1][j-1];
      } else {
        int delete;
        int insert;
        int substitute;
        int minimum;

        delete = matrix[i-1][j] + 1;
        insert = matrix[i][j-1] + 1;
        substitute = matrix[i-1][j-1] + 1;
        minimum = delete;
        if (insert < minimum) {
          minimum = insert;
        }
        if (substitute < minimum) {
          minimum = substitute;
        }
        matrix[i][j] = minimum;
      }
    }
  }
  return matrix[len1][len2];
}

void search(char *src){
  FILE *file = openFile("r+");
  char name[30];

  printf("Digite o nome do contato que deseja buscar: ");
  scanf(" %s",name);

  struct Contact contact;
  int n = 1;
  struct Temp *vector = calloc(n, sizeof(struct Temp*));

  while(fread(&contact, sizeof(struct Contact), 1, file)){
    if(contact.status != 0) {
      int cost = distance(name, strlen(name), contact.name, strlen(contact.name));
      if(cost <= 5 && n != 1) {
        vector = (struct Temp*) realloc(vector, (n)*sizeof(struct Temp*));
        vector[n-1].cost = cost;
        vector[n - 1].id = contact.id;
        strcpy(vector[n-1].name, contact.name);
        strcpy(vector[n-1].email, contact.email);
        strcpy(vector[n-1].phone, contact.phone);
        n++;
      }

      if(cost <= 5 && n == 1) {
        vector[0].cost = cost;
        vector[0].id = contact.id;
        strcpy(vector[0].name, contact.name);
        strcpy(vector[0].email, contact.email);
        strcpy(vector[0].phone, contact.phone);
        n++;
      }
    }
  }

  struct Temp aux;
  for(int i=0; i<n-1; i++ ){
    for (int j = i + 1; j < n - 1; j++)
    {
      if (vector[i].cost > vector[j].cost)
      {
        aux = vector[i];
        vector[i] = vector[j];
        vector[j] = aux;
      }
    }
  }

  printf("------------------------------------------------------------------------\n");
  for (int i = 0; i < n-1;i++){
    printf("%d. ID: %i Nome: %s Email: %s Telefone: %s Custo: %d\n",
           i + 1,
           vector[i].id,
           vector[i].name,
           vector[i].email,
           vector[i].phone,
           vector[i].cost);
    printf("------------------------------------------------------------------------\n");
  }
}
	
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
      default: printf("Essa opção não é válida.\n");
        break;
    }
  } while (resp != 0);
}

int main(int argc, char const *argv[])
{
  printf("Bem vindo a agenda, escolha uma opção para prosseguir...\n");
  menu();
  return 0;
}