#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>


int main()
{
	char messaggio[1024];
	char chiave[11];
	char mess_chiav[1024];
	char hash_code[SHA256_DIGEST_LENGTH * 2 + 1];

	printf("Inserisci il messaggio: ");
	fgets(messaggio, sizeof(messaggio), stdin);

	messaggio[strcspn(messaggio, "\n")] = '\0';

	printf("Inserisci la chiave: ");
	fgets(chiave, sizeof(chiave), stdin);

	chiave[strcspn(chiave, "\n")] = '\0';

	printf("Inserisci il codice hash per il confronto: ");
	fgets(hash_code, sizeof(hash_code), stdin);

	hash_code[strcspn(hash_code, "\n")] = '\0';

	strcpy(mess_chiav, messaggio);
	strcat(mess_chiav, chiave);





	return 0;
}
