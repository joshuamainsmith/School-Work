#include <string.h>
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

//helper function to converts public key from opened file (FILE*) to RSA format
RSA* convertPublicKeyToRSA(FILE* fp) {
    RSA* r = NULL;
    RSA* x = PEM_read_RSA_PUBKEY(fp, &r, NULL, NULL);	
    return r;
}

int main()
{
    unsigned int errcount = 0;
	// 1. Open the named pipe in read only mode
   int fd = open("pipeEx9", O_RDONLY);

   if (fd == -1) {
       printf("%s\n",strerror(errno));
       return 1;
   }

   FILE* fPubKey = fopen("publicKey.txt", "r");

    if (fPubKey == NULL) {
        printf("%s\n",strerror(errno));
        return 2;
    }

 	// 2. Read the public key of the receiver from the pipe
    char* pubKey = (char*) malloc(1000);

    if (pubKey == NULL) {
        cout << "Failed to create space for pubKey" << endl;
        return 3;
    }

	int err = read(fd, pubKey, 1000);

    if (err == -1) {
        printf("%s\n",strerror(errno));
        return 4;
    }

    // 3. Close the pipe
    err = close(fd);

    if (err == -1) {
        printf("%s\n",strerror(errno));
        return 5;
    }

    // 4. Display the received public key
    cout << "Public key of receiver: " << endl << pubKey << endl;
 
    // 5. Input a message from the user using standard input
	cout << "Enter the message: " << endl;
    string line;
    getline(std::cin, line);

    const char* msg = line.data();

	// 6. Convert the public key that the reciever sent through the pipe from string to RSA format
    // (Hint: You may need to read the char* as a FILE* -- look into posix string streams)
	RSA* rsa = convertPublicKeyToRSA(fPubKey);

	err = fclose(fPubKey);

    if (err != 0) {
        printf("%s\n",strerror(errno));
        return 6;
    }

	// 7. Encrypt the message using the RSA public encryption API
	int keyRSASize = RSA_size(rsa);

    if (keyRSASize == 0) {
        cout << "Failed to obtain key size" << endl;
        return 7;
    }

	char* eMsg = (char*)malloc(keyRSASize);

    if (eMsg == NULL) {
        cout << "Failed to create space for eMsg" << endl;
        return 8;
    }

	err = RSA_public_encrypt(keyRSASize - 42, (const unsigned char*)msg, (unsigned char*)eMsg, rsa, RSA_PKCS1_OAEP_PADDING);

    if (err == -1) {
        cout << "Failed to encrypt the message. Error code: " << ERR_get_error() << endl;
        return 9;
    }

	// 8. Display the encrypted message
    cout << "Encrypted Message: " << endl << eMsg << endl;

    // 9. Open the named pipe in write only mode
    fd = open("pipeEx9", O_WRONLY);

    if (fd == -1) {
       printf("%s\n",strerror(errno));
       return 10;
   }

    // 10. Write the encrypted message to the pipe 
	err = write(fd, eMsg, keyRSASize);

    if (err == -1) {
       printf("%s\n",strerror(errno));
       return 11;
   }

	// 11. Close the pipe
    err = close(fd);

    if (err == -1) {
        printf("%s\n",strerror(errno));
        return 12;
    }

	// 12. Free memory used
    free(pubKey);
	free(eMsg);

    return 0;
}
