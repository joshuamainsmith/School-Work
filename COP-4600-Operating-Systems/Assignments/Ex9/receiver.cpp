#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <cstring>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

// reads the key from the file
char* readKey(string fileName) {
	ifstream file(fileName.c_str());
	string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	char* key = (char*)malloc(strlen(contents.c_str()) * sizeof(char) + 1);
	strcpy(key, (char*)contents.c_str());
	file.close();
	return key;
}

//helper function to converts private key from opened file (FILE*) to RSA format
RSA* convertPrivateKeyToRSA(FILE* fp) {
	RSA* r = NULL;
	RSA* x = PEM_read_RSAPrivateKey(fp, &r, NULL, NULL);
	return r; 
}

//helper function to converts public key from opened file (FILE*) to RSA format
RSA* convertPublicKeyToRSA(FILE* fp) {
	RSA* r = NULL;
	RSA* temp = PEM_read_RSA_PUBKEY(fp, &r, NULL, NULL);
	return r;
}

int main()
{
	int err = 0;
	
	// 1. Read the keys
	ifstream pubKey;
    ifstream privKey;

    pubKey.open("publicKey.txt");

    if (!pubKey) {
        std::cout << "Failed to open publicKey.txt" << endl;
        cerr << "Error: " << strerror(errno) << endl;
        return 1;
    }

    privKey.open("privateKey.txt");

    if (!privKey) {
        std::cout << "Failed to open privateKey.txt" << endl;
        cerr << "Error: " << strerror(errno) << endl;
        return 2;
    }

    FILE* fPubKey = fopen("publicKey.txt", "r");

    if (fPubKey == NULL) {
            printf("%s\n",strerror(errno));
            return 3;
    }

     FILE* fPrivKey = fopen("privateKey.txt", "r");

    if (fPrivKey == NULL) {
        printf("%s\n",strerror(errno));
        return 4;
    }
	
	// 2. Display the keys
	cout << "Public key of receiver: " << endl << pubKey.rdbuf() << endl;
    cout << "Private key of receiver: " << endl << privKey.rdbuf() << endl;
	
	// 3. Open the named pipe in write only mode
	fstream fd;
    fd.open("pipeEx9", ios::out);

    if (!fd) {
        std::cout << "failed to open pipeEx9" << endl;
        cerr << "Error: " << strerror(errno) << endl;
        return 5;
    }
	
	// 4. Write the public key to the pipe and close the pipe
	//fd << pubKey.rdbuf();
    system("cat publicKey.txt > pipeEx9");
    privKey.close();
    pubKey.close();
    fd.close();
	
	// 5. Convert the private key to RSA format
	RSA* rsa_pub = convertPublicKeyToRSA(fPubKey);
	
	// 6. Open the pipe again in read only mode
	int fd2 = open("pipeEx9", O_RDONLY);

    if (fd2 == -1) {
       printf("%s\n",strerror(errno));
       return 6;
   }
   
	// 7. Read the incoming message length and the incoming message
	int keyRSASize = RSA_size(rsa_pub);

    if (keyRSASize == 0) {
        cout << "Failed to obtain key size" << endl;
        return 7;
    }

    char* eMessage = (char*)malloc(keyRSASize);

    if (eMessage == NULL) {
        cout << "Failed to create space for eMessage" << endl;
        return 8;
    }

    err = read(fd2, eMessage, keyRSASize);

    if (err == -1) {
        printf("%s\n",strerror(errno));
        return 9;
    }
	
	// 8. Close the pipe
	err = close(fd2);

    if (err == -1) {
        printf("%s\n",strerror(errno));
        return 10;
    }
	
	// 9. Display the received encrypted message
	cout << "Encrypted Message: " << endl << eMessage << endl;
	
	// 10. Decrypt the message using RSA private decryption API
	RSA* rsa_priv = convertPrivateKeyToRSA(fPrivKey);
	
	keyRSASize = RSA_size(rsa_priv);

    if (keyRSASize == 0) {
        cout << "Failed to obtain key size" << endl;
        return 11;
    }

    char* dMessage = (char*)malloc(keyRSASize);

    if (dMessage == NULL) {
        cout << "Failed to create space for dMessage" << endl;
        return 12;
    }

    err = RSA_private_decrypt(keyRSASize, (const unsigned char*)eMessage, (unsigned char*)dMessage, rsa_priv, RSA_PKCS1_OAEP_PADDING);

    if (err == -1) {
        cout << "Failed to decrypt the message. Error code: " << ERR_get_error() << endl;
        return 13;
    }
	
    // 11. Display the decrypted message
    cout << "Decrypted Message: " << endl << dMessage << endl;
		
	// 12. Free memory used		
	err = fclose(fPubKey);

    if (err != 0) {
        printf("%s\n",strerror(errno));
        return 14;
    }

    err = fclose(fPrivKey);

    if (err != 0) {
        printf("%s\n",strerror(errno));
        return 15;
    }

    free(dMessage);
    free(eMessage);

    return 0;
}