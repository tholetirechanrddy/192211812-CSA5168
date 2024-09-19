#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encryptCaesarCipher(char *text, int shift) {
	
    shift = shift % 26;

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';

            text[i] = (ch - base + shift) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int shift;

    printf("Enter the message to encrypt: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t length = strlen(text);
    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    }

    printf("Enter the shift value (1-25): ");
    if (scanf("%d", &shift) != 1) {
        printf("Invalid input for shift value.\n");
        return 1;
    }

    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Please enter a number between 1 and 25.\n");
        return 1;
    }

    encryptCaesarCipher(text, shift);

    printf("Encrypted message: %s\n", text);

    return 0;
}

