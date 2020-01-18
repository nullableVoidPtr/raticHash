// SPDX-License-Identifier: MIT

#include "raticHash.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void ratic_init(ratic_context* ctx, unsigned int length, unsigned int difficulty) {
	ctx->hash_len = length;
	ctx->difficulty = difficulty;
	ctx->state = 0;
	ctx->message_len = 0;
	ctx->vector = calloc(length, sizeof(char));
	ctx->prev_inputs = calloc(length, sizeof(char));
}

void ratic_update(ratic_context* ctx, const unsigned char* data, unsigned int length) {
	unsigned char carryover;

	for (unsigned int i = 0; i < length; i++) {
		carryover = data[i];
		for (unsigned int j = 0; j < ctx->difficulty; j++) {
			for (unsigned int k = 0; k < ctx->hash_len; k++) {
				ctx->state = ~(ctx->state ^ ctx->hash_len) - carryover;
				ctx->vector[k] ^= ctx->state;
				carryover = ctx->prev_inputs[k];
				ctx->prev_inputs[k] = ctx->state;
			}
		}
		ctx->message_len++;
	}
}

void ratic_final(ratic_context* ctx, char* result)  {
	unsigned char* padding;
	unsigned int pad_len;
	unsigned char counter;

	pad_len = ctx->hash_len - (ctx->message_len % ctx->hash_len);
	pad_len += (pad_len < ctx->hash_len) ? ctx->hash_len : 0;
	counter = ctx->message_len;
	padding = calloc(pad_len, sizeof(char));

	for (int i = 0; i < pad_len; i++) {
		if (i % 2) {
			padding[i] = ~counter;
		} else {
			padding[i] = counter;
			counter -= ctx->hash_len;
		}
	};

	ratic_update(ctx, padding, pad_len);

	memcpy(result, ctx->vector, ctx->hash_len);

	free(padding);
	free(ctx->vector);
	free(ctx->prev_inputs);

	memset(ctx, 0, sizeof(ratic_context));
};
