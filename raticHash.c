#include "raticHash.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

ratic_context* ratic_init(int length) {
	ratic_context* result;
	
	result = (ratic_context*) calloc(1, sizeof(ratic_context));
	result->LCG = 0xaa;
	result->hash_len = length;
	result->state = calloc(length, sizeof(char));
	result->prev_state = calloc(length, sizeof(char));
	return result;
}

void ratic_update(ratic_context* ctx, const char* data, int length) {
	unsigned char carryover = 0;
	for (unsigned int i = 0; i < length; carryover = data[i++]) {
		for (unsigned int j = 0; j < ctx->hash_len; j++) {
			ctx->LCG = ~(ctx->LCG + carryover) % UCHAR_MAX + 1;
			ctx->state[j] ^= ctx->LCG;
			carryover = ctx->prev_state[j];
			ctx->prev_state[j] = ctx->LCG;
		}
	}
}

void ratic_final(char* result, ratic_context* ctx) {
	char* padding;
	unsigned int pad_len;
	unsigned char tmp;

	pad_len = ctx->hash_len - (ctx->message_len % ctx->hash_len);
	tmp = ctx->message_len % UCHAR_MAX + 1;
	padding = (char*) calloc(pad_len, sizeof(char));
	for (int i = 0; i < pad_len; i++) {
		if (i % 2) {
			padding[i] = ~tmp;
		} else {
			padding[i] = tmp;
			tmp -= ctx->hash_len;
		}
	};
	ratic_update(ctx, padding, pad_len);
	memcpy(result, ctx->state, ctx->hash_len);
	free(ctx->state);
	free(ctx->prev_state);
	free(ctx);
}

void print_ratic(const char* string, unsigned int hash_len) {
	ratic_context* context;
	unsigned char* result;
	result = (unsigned char*) calloc(hash_len, sizeof(unsigned char));
	context = ratic_init(hash_len);
	ratic_update(context, string, strlen(string) + 1);
	ratic_final(result, context);
	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");
}

int main() {
	print_ratic("the quick brown fox jumps over the lazy dog", 8);
	print_ratic("the quick brown fox jumps ouer the lazy dog", 8);
	print_ratic("the quick brown fox jumps over the lazy doh", 8);
}
