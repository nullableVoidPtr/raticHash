#include "raticHash.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

ratic_context* ratic_init(unsigned int length, unsigned int difficulty) {
	ratic_context* result;
	
	result = (ratic_context*) calloc(1, sizeof(ratic_context));
	result->hash_len = length;
	result->difficulty = difficulty;
	result->state = (char*) calloc(length, sizeof(char));
	result->prev_state = (char*) calloc(length, sizeof(char));
	
	return result;
}

void ratic_update(ratic_context* ctx, const char* data, int length) {
	unsigned char carryover;

	for (unsigned int i = 0; i < length; i++) {
		carryover = data[i];
		for (unsigned int j = 0; j < ctx->difficulty; j++) {
			for (unsigned int k = 0; k < ctx->hash_len; k++) {
				ctx->PRNG = ~(ctx->PRNG ^ ctx->hash_len) - carryover;
				ctx->state[k] ^= ctx->PRNG;
				carryover = ctx->prev_state[k];
				ctx->prev_state[k] = ctx->PRNG;
			}
		}
		ctx->message_len++;
	}
}

void ratic_final(char* result, ratic_context* ctx) {
	char* padding;
	unsigned int pad_len;
	unsigned char counter;

	pad_len = ctx->hash_len - (ctx->message_len % ctx->hash_len);
	pad_len += (pad_len < ctx->hash_len) ? ctx->hash_len : 0; 
	counter = ctx->message_len;
	padding = (char*) calloc(pad_len, sizeof(char));
	
	for (int i = 0; i < pad_len; i++) {
		if (i % 2) {
			padding[i] = ~counter;
		} else {
			padding[i] = counter;
			counter -= ctx->hash_len;
		}
	};
	
	ratic_update(ctx, padding, pad_len);
	
	memcpy(result, ctx->state, ctx->hash_len);
	
	free(ctx->state);
	free(ctx->prev_state);
	free(ctx);
}
