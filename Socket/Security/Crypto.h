//
// Created by chryc on 08/12/2019.
//


#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string>
#include <iostream>
#include "../../Utils/base64.h"
#include <chrono>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#ifndef CHAT_SERVER_CRYPTO_H
#define CHAT_SERVER_CRYPTO_H

using namespace std;
using namespace std::chrono;

class Crypto {
private:
    RSA *keypair;
    RSA *client_key;
    EVP_CIPHER_CTX *e_ctx;
    EVP_CIPHER_CTX *d_ctx;

public:
    char *pub_key;
    unsigned char *AES_Key;
    unsigned char *AES_iv;
    int AES_BLOCK_SIZE = 16;
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

        //Generating AES-256 key and IV
        time_t time_sec = time(NULL);
        RAND_seed(&time_sec, sizeof(time_sec));

        AES_Key = new unsigned char[32];
        AES_iv = new unsigned char[AES_BLOCK_SIZE];
        RAND_bytes(AES_Key, 32);
        RAND_bytes(AES_iv, AES_BLOCK_SIZE);

        //Creating and initialising the context cipher
        e_ctx = EVP_CIPHER_CTX_new();
        d_ctx = EVP_CIPHER_CTX_new();
        if (EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, AES_Key, AES_iv) != 1) {
            cout << "Error during the initialization of EVP!!!\n";
            handleErrors();
        }

        if (EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, AES_Key, AES_iv) != 1) {
            cout << "Error during the initialization of EVP!!!\n";
            handleErrors();
        }

    }

    virtual ~Crypto() {
        RSA_free(keypair);
        RSA_free(client_key);
        delete[] pub_key;
        EVP_CIPHER_CTX_free(e_ctx);
        EVP_CIPHER_CTX_free(d_ctx);
        delete[] AES_Key;
        delete[] AES_iv;
        cout << "Released keys and ciphers\n";
    }

    char *encrypt_RSA(char *msg);

    char *decrypt_RSA(char *msg);

    void setClientPublicKey(char *key) {
        BIO *mem = BIO_new_mem_buf(key, strlen(key));
        RSA *rsa = PEM_read_bio_RSAPublicKey(mem, nullptr, nullptr, nullptr);
        this->client_key = rsa;
        BIO_free(mem);
    }

    char *encrypt_AES(char *msg);

    string decrypt_AES(char *msg);

    void handleErrors(void) {
        ERR_print_errors_fp(stderr);
    }
};


#endif //CHAT_SERVER_CRYPTO_H
