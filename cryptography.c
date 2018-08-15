#include <stdio.h>
#include <string.h>

char selection[10]; // c for Caesar Shift, v for Vigenere Cipher
char algorithm[10]; // Encrypt or Decrypt
char text[1000];    // text given by user
int key;            // used to shift letters
char keyword[100];  // keyword given by user for Vigenere Cipher
char ch;

// declare functions
int caesarEncrypt();
int caesarDecrypt();
int vigenereEncrypt();
int vigenereDecrypt();


// main function
int main() {
  printf("Welcome to the Cryptography Program!\n");
  printf("Would you like to use Caesar Shift or Vigenere Cipher?\n");
  printf("Type 'C' for Caesar Shift or 'V' for Vigenere Cipher: ");
  fgets(algorithm, 10, stdin);

  // Caesar Shift
  if (strncmp(algorithm,"C",1) == 0 || strncmp(algorithm, "c",1) == 0) {
    printf("Would you like to encrypt or decrypt a message?\n");
    printf("Type 'E' for Encrypt or 'D' for Decrypt: ");
    fgets(selection, 10, stdin);

    if (strncmp(selection,"E",1) == 0 || strncmp(selection, "e",1) == 0) {
      printf("Enter a message to encrypt: ");
      fgets(text, 1000, stdin);
      printf("Enter key value: ");
      scanf("%d", &key);
      caesarEncrypt();
      printf("Encrypted message: %s\n", text);
    }
    else if (strncmp(selection,"D",1) == 0 || strncmp(selection, "d",1) == 0) {
      printf("Enter a message to decrypt: ");
      fgets(text, 1000, stdin);
      printf("Enter key value: ");
      scanf("%d", &key);
      caesarDecrypt();
      printf("Decrypted message: %s\n", text);
    }
  }

  // Vigenere Cipher
  else if (strncmp(algorithm,"V",1) == 0 || strncmp(algorithm, "v",1) == 0) {
    printf("Would you like to encrypt or decrypt a message?\n");
    printf("Type 'E' for Encrypt or 'D' for Decrypt: ");
    fgets(selection, 10, stdin);

    if (strncmp(selection,"E",1) == 0 || strncmp(selection, "e",1) == 0) {
      printf("Enter a message to encrypt: ");
      fgets(text, 1000, stdin);
      printf("Enter keyword: ");
      fgets(keyword, 100, stdin);
      vigenereEncrypt();
      printf("Encrypted message: %s\n", text);
    }
    else if (strncmp(selection,"D",1) == 0 || strncmp(selection, "d",1) == 0) {
      printf("Enter a message to decrypt: ");
      fgets(text, 1000, stdin);
      printf("Enter keyword: ");
      fgets(keyword, 100, stdin);
      vigenereDecrypt();
      printf("Decrypted message: %s\n", text);
    }
  }

  return 0;
}


// Perform a Caesar Shift encryption
int caesarEncrypt() {
  for (int i = 0; i < sizeof(text); i++) {
    ch = text[i];
    key = key % 26; // mod the key by 26 to ensure key is within 0-25

    // deal with lowercase and uppercase letters separately
    if (ch >= 'a' && ch <= 'z') {
      ch = ch + key;
      if (ch > 'z') {
        ch = ch - 'z' + 'a' - 1; // if the character is greater than z, calibrate it back to a letter
      }
      text[i] = ch;
    }
    else if (ch >= 'A' && ch <= 'Z') {
      ch = ch + key;
      if (ch > 'Z') {
        ch = ch - 'Z' + 'A' - 1; // if the character is greater than Z, calibrate it back to a letter
      }
      text[i] = ch;
    }
  }
  return 0;
}



// Perform a Caesar Shift decryption
int caesarDecrypt() {
  for (int i = 0; i < sizeof(text); i++) {
    ch = text[i];
    key = key % 26; // mod the key by 26 to ensure key is within 0-25

    // deal with lowercase and uppercase letters separately
    if (ch >= 'a' && ch <= 'z') {
      ch = ch - key;
      if (ch < 'a') {
        ch = ch + 'z' - 'a' + 1; // if the character is less than a, calibrate it back to a letter
      }
      text[i] = ch;
    }
    else if (ch >= 'A' && ch <= 'Z') {
      ch = ch - key;
      if (ch < 'A') {
        ch = ch + 'Z' - 'A' + 1; // if the character is less than A, calibrate it back to a letter
      }
      text[i] = ch;
    }
  }
  return 0;
}



// Perform a Vigenere Cipher encryption
int vigenereEncrypt() {
  // j is used to keep track of the index (current char) of the keyword
  int j = 0;
  for (int i = 0; i < strlen(text); i++) {
    // only apply shift if ch is a letter
    if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) {
      ch = text[i];

      // if the j has reached the end of the keyword, reset to the start of the keyword
      if (j == strlen(keyword)-1) {
        j = 0;
      }
      key = keyword[j];

      // if ch is lowercase and the key is lowercase
      if ((ch >= 'a' && ch <= 'z') &&  (key >= 'a' && key <= 'z')) {
        key = key - 97;
        if ((ch + key) > 'z') {
          key = key - 26; // if (ch+key) is greater than z, calibrate the key
        }
        ch = ch + key;
      }

      // if ch is lowercase and the key is uppercase
      if ((ch >= 'a' && ch <= 'z') &&  (key >= 'A' && key <= 'Z')) {
        key = (key + 32) - 97;
        if ((ch + key) > 'z') {
          key = key - 26; // if (ch+key) is greater than z, calibrate the key
        }
        ch = ch + key;
      }

      // if ch is uppercase and the key is lowercase
      if ((ch >= 'A' && ch <= 'Z') &&  (key >= 'a' && key <= 'z')) {
        // convert ch to lowercase
        ch = ch + 32;
        key = key - 97;
        if ((ch + key) > 'z') {
          key = key - 26; // if (ch+key) is greater than z, calibrate the key
        }
        ch = ch - 32; // return ch back to uppercase
        ch = ch + key;
      }

      // if ch is uppercase and the key is uppercase
      if ((ch >= 'A' && ch <= 'Z') &&  (key >= 'A' && key <= 'Z')) {
        // convert ch and key to lowercase
        ch = ch + 32;
        key = (key + 32) - 97;
        if ((ch + key) > 'z') {
          key = key - 26; // if (ch+key) is greater than z, calibrate the key
        }
        ch = ch - 32; // return ch back to uppercase
        ch = ch + key;
      }

      text[i] = ch;
      j++;
    }
  }

  return 0;
}



// Perform a Vigenere Cipher decryption
int vigenereDecrypt() {
  // j is used to keep track of the index (current char) of the keyword
  int j = 0;
  for (int i = 0; i < strlen(text); i++) {

    // only apply shift if ch is a letter
    if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) {
      ch = text[i];

      // if the j has reached the end of the keyword, reset to the start of the keyword
      if (j == strlen(keyword)-1) {
        j = 0;
      }
      key = keyword[j];

      // if ch is lowercase and the key is lowercase
      if ((ch >= 'a' && ch <= 'z') &&  (key >= 'a' && key <= 'z')) {
        key = -1 * (key - 97);
        if ((ch + key) < 'a') {
          key = key + 26; // if (ch+key) is less than a, calibrate the key
        }
        ch = ch + key;
      }

      // if ch is lowercase and the key is uppercase
      if ((ch >= 'a' && ch <= 'z') &&  (key >= 'A' && key <= 'Z')) {
        key = -1 * ((key + 32) - 97);
        if ((ch + key) < 'a') {
          key = key + 26; // if (ch+key) is less than a, calibrate the key
        }
        ch = ch + key;
      }

      // if ch is uppercase and the key is lowercase
      if ((ch >= 'A' && ch <= 'Z') &&  (key >= 'a' && key <= 'z')) {
        // convert ch to lowercase
        ch = ch + 32;
        key = -1 * (key - 97);
        if ((ch + key) < 'a') {
          key = key + 26; // if (ch+key) is less than a, calibrate the key
        }
        ch = ch - 32; // return ch back to uppercase
        ch = ch + key;
      }

      // if ch is uppercase and the key is uppercase
      if ((ch >= 'A' && ch <= 'Z') &&  (key >= 'A' && key <= 'Z')) {
        // convert ch and key to lowercase
        ch = ch + 32;
        key = -1 * ((key + 32) - 97);
        if ((ch + key) < 'a') {
          key = key + 26; // if (ch+key) is less than a, calibrate the key
        }
        ch = ch - 32; // return ch back to uppercase
        ch = ch + key;
      }

      text[i] = ch;
      j++;
    }
  }

  return 0;
}
