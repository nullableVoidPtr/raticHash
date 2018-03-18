#include "raticHash.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void print_ratic(const char* string, unsigned int hash_len) {
	ratic_context* context;
	unsigned char* result;
	
	result = (char*) calloc(hash_len, sizeof(char));
	context = ratic_init(hash_len, 1);
	ratic_update(context, string, strlen(string) + 1);
	ratic_final(result, context);
	
	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");
}

void zero_ratic(unsigned int hash_len, unsigned int message_len) {
	ratic_context* context;
	unsigned char* result;
	unsigned char* input;

	result = (unsigned char*) calloc(hash_len, sizeof(char));
	input = (unsigned char*) calloc(message_len, sizeof(char));
	context = ratic_init(hash_len, 1);
	ratic_update(context, input, message_len);
	ratic_final(result, context);

	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");
}

void partial_update(unsigned int hash_len, unsigned int message_len) {
	ratic_context* context;
	unsigned char* result;
	unsigned char* input;

	result = (unsigned char*) calloc(hash_len, sizeof(char));
	input = (unsigned char*) calloc(message_len, sizeof(char));
	memset(input, 'a', message_len);
	context = ratic_init(hash_len, 1024);
	ratic_update(context, input, message_len);
	ratic_final(result, context);

	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");

	context = ratic_init(hash_len, 1024);
	for (int i = 0; i < message_len; i++) {
		ratic_update(context, &input[0], 1);
	}
	ratic_final(result, context);

	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");
}

int main() {
	print_ratic("the quick brown fox jumps over the lazy dog", 32);
	print_ratic("the quick brown fox jumps ouer the lazy dog", 32);
	print_ratic("the quick brown fox jumps over the lazy doh", 32);
	zero_ratic(32, 32);
	partial_update(32, 32);
}
