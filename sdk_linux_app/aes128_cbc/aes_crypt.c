//  aes_crypt.c
//  WeChat Embedded
//
//  Created by harlliu on 14-02-26.
//  Copyright 2014 Tencent. All rights reserved.
//

#include "aes_crypt.h"
#include <string.h>
#include <stdlib.h>

int aes_cbc_encrypt_init(AES_CTX *c, const uint8_t key[16])
{
	if (c == NULL || key == NULL)
		return -1;

	// memcpy(c->iv, key, 16);
	memset(c->iv, 0, 16);

	int ret = AES_set_encrypt_key(key, 128, &c->key);
	if(ret != 0) return -1;

	return 0;
}

int aes_cbc_encrypt_update(AES_CTX *c, const uint8_t in[16], uint8_t out[16])
{
	if (c == NULL || in == NULL || out == NULL)
		return -1;

	AES_cbc_encrypt(in, out, 16, &c->key, c->iv);
	return 0;
}

int aes_cbc_encrypt_final(AES_CTX *c, const uint8_t *in, int in_len, uint8_t out[32], int *out_len)
{
	if (c == NULL || in == NULL || in_len <= 0 || in_len > 16 || out == NULL || out_len == NULL)
		return -1;

	//pkcs#7 padding
	int padding_len = 16 - (in_len % 16);
	*out_len = in_len + padding_len;

	if (in != out)
		memcpy(out, in, in_len);
	
	memset(out+in_len, padding_len, padding_len);

	if (*out_len > 16) {
		AES_cbc_encrypt(out, out, 16, &c->key, c->iv);
		out += 16;
		AES_cbc_encrypt(out, out, 16, &c->key, c->iv);
	} else {
		AES_cbc_encrypt(out, out, 16, &c->key, c->iv);
	}

	return 0;
}

int aes_cbc_decrypt_init(AES_CTX *c, const uint8_t key[16])
{
	if (c == NULL || key == NULL)
		return -1;

	// memcpy(c->iv, key, 16);
	memset(c->iv, 0, 16);

	int ret = AES_set_decrypt_key(key, 128, &c->key);
	if(ret != 0) return -1;

	return 0;
}

int aes_cbc_decrypt_update(AES_CTX *c, const uint8_t in[16], uint8_t out[16])
{
	if (c == NULL || in == NULL || out == NULL)
		return -1;

	AES_cbc_decrypt(in, out, 16, &c->key, c->iv);
	return 0;
}

int aes_cbc_decrypt_final(AES_CTX *c, const uint8_t in[16], uint8_t out[16], int *out_len)
{
	if (c == NULL || in == NULL || out == NULL)
		return -1;

	AES_cbc_decrypt(in, out, 16, &c->key, c->iv);
	int padding_len = out[15];
	if (padding_len < 1 || padding_len > 16)
		return -1;
	
	if (out_len != NULL)
		*out_len = 16 - padding_len;

	return 0;
}

void encrypt_data(uint8_t *data,int in_length,uint8_t* key,uint8_t *encrypt_buf, int *encrypt_len)
{
	int len = in_length;
	int offset = 0;

	AES_CTX c;
	aes_cbc_encrypt_init(&c, key);


	while(len > 16) {
		aes_cbc_encrypt_update(&c, data+offset, encrypt_buf+offset);
		offset += 16;
		len -= 16;
	}

	int out_len = 0;
	aes_cbc_encrypt_final(&c, data+offset, len, encrypt_buf+offset, &out_len);
	*encrypt_len = offset + out_len;

}
void decrypt_data(uint8_t *data,int in_length,uint8_t* key,uint8_t *decrypt_buf, int *decrypt_len)
{
	int len = in_length;
	int offset = 0;

	AES_CTX c;
	aes_cbc_decrypt_init(&c, key);

	while(len > 16) {
		aes_cbc_decrypt_update(&c, data+offset, decrypt_buf+offset);
		offset += 16;
		len -= 16;
	}

	int out_len = 0;
	aes_cbc_decrypt_final(&c, data+offset, decrypt_buf+offset, &out_len);
	*decrypt_len = offset + out_len;
}
