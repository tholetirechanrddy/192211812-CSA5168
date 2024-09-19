#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void prepare_key(char *key, char key_table[5][5]) {
    int i, j, k;
    int alphabet[26] = {0};
    int index = 0;
  
    for (i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (isalpha(ch) && alphabet[ch - 'A'] == 0) {
            if (ch == 'J') ch = 'I'; 
            alphabet[ch - 'A'] = 1;
            key_table[index / 5][index % 5] = ch;
            index++;
        }
    }
 
    for (i = 0; i < 26; i++) {
        if (alphabet[i] == 0) {
            if (i == 9) continue;  
            key_table[index / 5][index % 5] = 'A' + i;
            index++;
        }
    }
}

void find_position(char ch, char key_table[5][5], int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key_table[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfair_decrypt(char *ciphertext, char key_table[5][5], char *decrypted) {
    int i, row1, col1, row2, col2;
    int index = 0;

    for (i = 0; i < strlen(ciphertext); i += 2) {
        char ch1 = ciphertext[i];
        char ch2 = ciphertext[i + 1];

        if (ch1 == 'J') ch1 = 'I';  
        if (ch2 == 'J') ch2 = 'I';  

        find_position(ch1, key_table, &row1, &col1);
        find_position(ch2, key_table, &row2, &col2);

        if (row1 == row2) {
            decrypted[index++] = key_table[row1][(col1 + 4) % 5];
            decrypted[index++] = key_table[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            decrypted[index++] = key_table[(row1 + 4) % 5][col1];
            decrypted[index++] = key_table[(row2 + 4) % 5][col2];
        } else {
            decrypted[index++] = key_table[row1][col2];
            decrypted[index++] = key_table[row2][col1];
        }
    }
    decrypted[index] = '\0';
}

int main() {
    char key[] = "PT109";  
    char key_table[5][5];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char decrypted[MAX_LEN];

    prepare_key(key, key_table);
    playfair_decrypt(ciphertext, key_table, decrypted);

    printf("Decrypted message: %s\n", decrypted);
    return 0;
}

