/*
*   Author: Ehiremen Ekore
*   Started: 09/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int inputMessageForProcessing(char secretMessage[]);
void encryptAndPrintMessage(char secretMessage[], int messageLength);
void decryptAndPrintMessage(char secretMessage[], int messageLength);

int main() {
    
    int menuOptionChosen, messageLength;
    char secretMessage[21];

    //create the menu loop in main rather than a separate function
    //because passing values to other functions can be tricky when done outside main()
    while (menuOptionChosen != 3) {
        printf("Hail Caesar, please type in the appropriate number for your task\n");
        printf("(1) Encrypt a message for me\n");
        printf("(2) Decrypt a message for me\n");
        printf("(3) No more secrets; EXIT\n");

        scanf("%i", &menuOptionChosen);
        if (menuOptionChosen == 1) {
            messageLength = inputMessageForProcessing(secretMessage);
            encryptAndPrintMessage(secretMessage, messageLength);
        } else if (menuOptionChosen == 2) {
            messageLength = inputMessageForProcessing(secretMessage);
            decryptAndPrintMessage(secretMessage, messageLength);
        } else if (menuOptionChosen == 3) {
            printf("Hope you have been served\n");
            printf("Bye :)");
        } else {
            printf("Invalid choice, please retry \n");
        }
    }

    fclose(file);
    return 0;
}

//This function reads in the message to be encrypted/decrypted
int inputMessageForProcessing(char secretMessage[]){
    int i = 0;
    int messageLength;
    printf("Please input your message\n");
    for(i=0; i<21; i++){
        scanf("%c", &secretMessage[i]);
        if((i > 0) && (secretMessage[i] == '\n')) break;
        messageLength = i;
    }
    FILE* file = fopen("inputs.txt", "a");
    fprintf(file, "Message: %s\n", secretMessage);

    //calculate and return messageLength for use in other functions because... why not?
    return messageLength;
}

void encryptAndPrintMessage(char secretMessage[], int messageLength){
    int encryptionKey;
    int cipherValue;
    char encryptedMessage[messageLength];

    printf("Encryption Key: ");
    scanf("%i", &encryptionKey);

    fprintf(file, "Process: Encryption\n");
    fprintf(file, "Key: %i\n", encryptionKey);
    
    printf("Lord Caesar's cipher:");
    for(int i=0; i<(messageLength+1); i++){
        //force chars to uppercase in case Julius forgot to type in ALL CAPS
        encryptedMessage[i] = toupper(secretMessage[i]);

        //perform encryption only on alpha chars
        //this prevents issues when dealing with whitespace and other non-alpha chars
        if(isalpha(secretMessage[i])){
            //... + (encryptionKey%26) + 26 fixes issues that may arise when dealing with negative encryptionKeys
            cipherValue = (((int)encryptedMessage[i] - 65 + (encryptionKey%26) +26)%26) + 65;
            encryptedMessage[i] = (char) (cipherValue);
        }
        printf("%c", encryptedMessage[i]);
    }

    //insert blank lines to make output look nicer when looping the menu
    printf("\n\n");
}

//Decryption can be achieved by negating encryptionKey in encryptandPrintMessage() as well
void decryptAndPrintMessage(char secretMessage[], int messageLength){
    int decryptionKey;
    int cipherValue;
    char decryptedMessage[messageLength];

    printf("Decryption Key: ");
    scanf("%i", &decryptionKey);
    
    fprintf(file, "Process: Decryption\n");
    fprintf(file, "Key: %i\n", decryptionKey);

    printf("Lord Caesar's message:");
    for(int i=0; i<(messageLength+1); i++){
        decryptedMessage[i] = toupper(secretMessage[i]);

        if(isalpha(secretMessage[i])){
            cipherValue = 65 + (((int)decryptedMessage[i] - 65 - (decryptionKey%26) + 26)%26);
            decryptedMessage[i] = (char) (cipherValue);
        }
        printf("%c", decryptedMessage[i]);
    }

    printf("\n\n");
}
