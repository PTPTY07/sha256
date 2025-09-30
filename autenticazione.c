#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>  // Per SHA256
//sudo apt update
//sudo apt install build-essential libssl-dev
//gcc autenticazione.c -o autenticazione -lcrypto

int main() {
    char input[1024];     // Buffer per l'input dell'utente
    char messaggio[1024]; // Buffer per il messaggio
    char chiave[1024];      // Ultimi 10 caratteri = chiave (+1 per il terminatore '\0')

    // 1. Chiedere input all'utente
    printf("Messaggio con chiave: ");
    fgets(input, sizeof(input), stdin);

    // Rimuove eventuale '\n' lasciato da fgets
    int pos = strcspn(input, "\n");
    input[pos] = '\0';

    // 2. Separare chiave (ultimi 10 caratteri) e messaggio (resto)
    int len = strlen(input);

    if (len < 10) {
        printf("Errore: l'input deve contenere almeno 10 caratteri.\n");
        return 1;
    }

    // Copia ultimi 10 caratteri in chiave
    strcpy(chiave, input + len - 10);

    // Copia tutto tranne gli ultimi 10 caratteri in messaggio
    strncpy(messaggio, input, len - 10);
    messaggio[len - 10] = '\0'; // Terminatore stringa

    // 3. Calcolare SHA256
    unsigned char hash[SHA256_DIGEST_LENGTH]; // 32 byte
    SHA256((unsigned char*)input, strlen(input), hash);

    // Convertire hash in stringa esadecimale
    char hash_hex[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_hex + (i * 2), "%02x", hash[i]);
    }
    hash_hex[SHA256_DIGEST_LENGTH * 2] = '\0';

    // 4. Stampare i risultati
    printf("Messaggio: %s\n", messaggio);
    printf("Chiave: %s\n", chiave);
    printf("SHA256: %s\n", hash_hex);
    
     FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }

    fprintf(fp, "%s\n", messaggio);  // Scrive il messaggio
    fprintf(fp, "%s\n", hash_hex);   // Scrive l'hash
    fclose(fp);

    return 0;
}

