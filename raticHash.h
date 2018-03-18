typedef struct _ratic_context {
	unsigned int hash_len;
	unsigned int message_len;
	unsigned int difficulty;
	char PRNG;
	char* state;
	char* prev_state;
} ratic_context;

ratic_context* ratic_init(unsigned int, unsigned int);
void ratic_update(ratic_context*, const char*, int);
void ratic_final(char*, ratic_context*);
