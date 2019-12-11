//
// Created by chryc on 08/12/2019.
//


#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string>
#include <iostream>
#include "../Utils/base64.h"
#include <chrono>


#ifndef CHAT_SERVER_CRYPTO_H
#define CHAT_SERVER_CRYPTO_H

using namespace std;
using namespace std::chrono;

class Crypto {
private:
    RSA *keypair;
    RSA *client_key;

public:
    char *pub_key;
    int lastCryptedLen;

    Crypto() {

        this->keypair = RSA_generate_key(1024, 3, NULL, NULL);
        BIO *pub = BIO_new(BIO_s_mem());
        PEM_write_bio_RSAPublicKey(pub, keypair);
        int pub_len = BIO_pending(pub);
        pub_key = new char[pub_len + 1];
        BIO_read(pub, pub_key, pub_len);
        pub_key[pub_len] = '\0';
        BIO_free(pub);

    }

    virtual ~Crypto() {
        RSA_free(keypair);
        RSA_free(client_key);
        delete[] pub_key;
    }

    char *encrypt(char *msg) {
        int len = RSA_size(client_key);
        int keyTimes = strlen(msg) / 80;
        int remain = strlen(msg) % 80;
        if (keyTimes == 0) {
            keyTimes++;
        } else {
            if (remain > 0) {
                keyTimes++;
            }
        }
        //cout << "Buff size: " << len * keyTimes + 6 << "\n";
        char *encrypted = new char[len * keyTimes + 4];
        memcpy(encrypted, &keyTimes, 4);
        //sprintf(encrypted, "%d", keyTimes);
        //encrypted[5] = '\0';

        int remainBytes = strlen(msg);
        int bytesToRead = 80;
        int index = 0;
        lastCryptedLen = 0;
        while (remainBytes > 0) {
            if (remainBytes < bytesToRead) {
                bytesToRead = remainBytes;
            }
            int encryptedLen = RSA_public_encrypt(bytesToRead, (unsigned char *) msg + index * 80,
                                                  (unsigned char *) encrypted + 4 + 128 * index,
                                                  client_key, RSA_PKCS1_OAEP_PADDING);

            if (encryptedLen == -1) {
                ERR_load_crypto_strings();
                char *buffError = new char[200];
                ERR_error_string(ERR_get_error(), buffError);
                cout << "Error during encryption: " << buffError << "\n";
                delete[] buffError;
                break;
            }
            //cout << "Encryption n." << index << "\n";
            remainBytes -= bytesToRead;
            lastCryptedLen += encryptedLen;
            index++;
        }

        lastCryptedLen += 4;
        //cout << "Encrypted: " << lastCryptedLen << "bytes"  <<  "\n";
        return encrypted;
    }

    char *decrypt(char *msg) {
        int len = RSA_size(keypair);

        //int keyTimes = atoi(msg);
        int keyTimes = 0;
        memcpy(&keyTimes, msg, 4);
        char *decrypted = new char[len * keyTimes + 1];

        int remainBytes = len * keyTimes;

        int index = 0;
        int end = 0;
        while (remainBytes > 0) {

            int decryptedLen = RSA_private_decrypt(len, (unsigned char *) msg + 4 + index * 128,
                                                   (unsigned char *) decrypted + 80 * index,
                                                   keypair, RSA_PKCS1_OAEP_PADDING);
            if (decryptedLen == -1) {
                ERR_load_crypto_strings();
                char *buffError = new char[200];
                ERR_error_string(ERR_get_error(), buffError);
                cout << "Error during decryption: " << buffError << "\n";
                delete[] buffError;
                break;
            }

            remainBytes -= len;
            end += decryptedLen;

            index++;

        }
        decrypted[end] = '\0';
        //cout << "Decrypted: " << keyTimes * 80 << "bytes" << "   Duration: " << duration.count() << "\n";
        return decrypted;
    }

    void setClientPublicKey(char *key) {

        BIO *mem = BIO_new_mem_buf(key, strlen(key));
        RSA *rsa = PEM_read_bio_RSAPublicKey(mem, nullptr, nullptr, nullptr);
        //cout << "chiave caricata: " << rsa << "\n";
        this->client_key = rsa;
        BIO_free(mem);
        //cout << "Key loaded\n";
    }

};


#endif //CHAT_SERVER_CRYPTO_H
