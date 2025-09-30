#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
    char messaggio[1024];
    char chiave[1024];
    char mess_chiav[2048]; // Messaggio + chiave
    char hash_code[SHA256_DIGEST_LENGTH * 2 + 1];     // Hash letto da file
    char hash_calcolato[SHA256_DIGEST_LENGTH * 2 + 1]; // Hash ricalcolato

    // 1. Legge messaggio e hash dal file
    FILE *fp = fopen("output.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file output.txt");
        return 1;
    }

    if (fgets(messaggio, sizeof(messaggio), fp) == NULL) {
        printf("Errore nella lettura del messaggio dal file.\n");
        fclose(fp);
        return 1;
    }

    if (fgets(hash_code, sizeof(hash_code), fp) == NULL) {
        printf("Errore nella lettura dell'hash dal file.\n");
        fclose(fp);
        return 1;
    }

    // Rimuove newline (\n) eventualmente presenti
    messaggio[strcspn(messaggio, "\n")] = '\0';
    hash_code[strcspn(hash_code, "\n")] = '\0';

    fclose(fp);

    // 2. Chiede la chiave all’utente
    printf("Inserisci la chiave (password): ");
    fgets(chiave, sizeof(chiave), stdin);
    chiave[strcspn(chiave, "\n")] = '\0';
    
    printf("Messaggio del file: %s\n", messaggio);
    printf("Hash file: %s\n", hash_code);

    // 3. Concatena messaggio + chiave
    strcpy(mess_chiav, messaggio);
    strcat(mess_chiav, chiave);

    // 4. Calcola SHA256 del messaggio + chiave
    unsigned char hash_bin[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)mess_chiav, strlen(mess_chiav), hash_bin);

    // 5. Converte l'hash in esadecimale
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_calcolato + (i * 2), "%02x", hash_bin[i]);
    }
    hash_calcolato[SHA256_DIGEST_LENGTH * 2] = '\0';
	
	printf("Hash calcolato: %s\n", hash_calcolato);
    // 6. Confronta hash calcolato con quello letto dal file
    if (strcmp(hash_code, hash_calcolato) == 0) {
        printf("Autenticazione riuscita! Hash corrispondente.\n");
    } else {
        printf("Autenticazione fallita. Hash non corrispondente.\n");
    }

    return 0;
}

