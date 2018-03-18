#include "raticHash.h"

#include <math.h>

void print_ratic(const char* string, unsigned int hash_len) {
	ratic_context* context;
	unsigned char* result;
	
	result = (char*) calloc(hash_len, sizeof(char));
	context = ratic_init(hash_len);
	ratic_update(context, string, strlen(string) + 1);
	ratic_final(result, context);
	
	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");
}

void zero_ratic(unsigned int hash_len, unsigned int message_len) {
	ratic_context* context;
	unsigned char* result;
	unsigned char* input;
	result = (char*) calloc(hash_len, sizeof(char));
	input = (char*) calloc(message_len, sizeof(char));
	context = ratic_init(hash_len);
	ratic_update(context, input, message_len);
	ratic_final(result, context);

	for (int i = 0; i < hash_len; printf("%02x", result[i++]));
	printf("\n");
}

int main() {
	print_ratic("the quick brown fox jumps over the lazy dog", 32);
	print_ratic("the quick brown fox jumps ouer the lazy dog", 32);
	print_ratic("the quick brown fox jumps over the lazy doh", 32);
	zero_ratic(32, 32);
}
