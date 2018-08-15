#include <stdio.h>
#include <string.h>

char text[1000];
char encryptedText[1000];
int keyword();
FILE *fp;

int main() {
  fp = fopen("words.txt");
  /*printf("Enter a message: ");
  fgets(text, 1000, stdin);*/
  printf("Enter encrypted message: ");
  fgets(encryptedText, 1000, stdin);
  keyword();
  return 0;
}


int keyword2() {
  char ch;
  char ech;
  char keys[sizeof(text)];

  for (int i = 0; i < strlen(text); i++) {
    ch = text[i];
    ech = encryptedText[i];

    ch = text[i];


    if ((ch >= 'a' && ch <= 'z') && (ech >= 'a' && ech <= 'z')) {
      if (ech >= ch) {
        keys[i] = ech - ch + 97;
      }
      else {
        keys[i] = (122 - ch) + ech + 1;
      }
    }

  }

  printf("%s\n", keys);

  return 0;
}


int keyword() {

}
