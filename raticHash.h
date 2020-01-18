// SPDX-License-Identifier: MIT

#pragma once

typedef struct _ratic_context {
	unsigned int hash_len;
	unsigned int message_len;
	unsigned int difficulty;
	char state;
	char* vector;
	char* prev_inputs;
} ratic_context;

void ratic_init(ratic_context*, unsigned int, unsigned int);
void ratic_update(ratic_context*, const unsigned char*, unsigned int);
void ratic_final(ratic_context*, char*);
