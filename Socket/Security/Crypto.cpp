//
// Created by chryc on 12/12/2019.
//

#include "Crypto.h"

char *Crypto::encrypt_RSA(char *msg) {
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

char *Crypto::decrypt_RSA(char *msg) {
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


char *Crypto::encrypt_AES(char *msg) {

    int len = strlen(msg) + 1;
    int c_len = len + AES_BLOCK_SIZE, f_len = 0;
    auto *ciphertext = new unsigned char[c_len + 4];

    /* allows reusing of 'e' for multiple encryption cycles */
    EVP_EncryptInit_ex(e_ctx, nullptr, nullptr, nullptr, nullptr);

    /* update ciphertext, c_len is filled with the length of ciphertext generated,
      *len is the size of plaintext in bytes */
    EVP_EncryptUpdate(e_ctx, ciphertext + 4, &c_len, reinterpret_cast<const unsigned char *>(msg), len);

    /* update ciphertext with the final remaining bytes */
    EVP_EncryptFinal_ex(e_ctx, ciphertext + 4 + c_len, &f_len);

    lastCryptedLen = c_len + f_len;
    memcpy(ciphertext, &len, 4);
    lastCryptedLen += 4;
    return reinterpret_cast<char *>(ciphertext);
}

string Crypto::decrypt_AES(char *msg) {
    int msg_len = 0;
    memcpy(&msg_len, msg, 4);

    int p_len = 16 - (msg_len % AES_BLOCK_SIZE) + msg_len;
    int f_len = 0;

    char *plaintext = new char[p_len];

    EVP_DecryptInit_ex(d_ctx, nullptr, nullptr, nullptr, nullptr);
    EVP_DecryptUpdate(d_ctx, reinterpret_cast<unsigned char *>(plaintext), &p_len, (const unsigned char *) msg + 4,
                      p_len);
    EVP_DecryptFinal_ex(d_ctx, reinterpret_cast<unsigned char *>(plaintext + p_len), &f_len);

    string pollo(plaintext);
    delete[] plaintext;
    pollo = pollo.substr(0, msg_len);
    return pollo;
}

