typedef struct _ratic_context {
	unsigned int hash_len;
	unsigned int message_len;
	unsigned int difficulty;
	char state;
	char* vector;
	char* prev_inputs;
} ratic_context;

ratic_context* ratic_init(unsigned int, unsigned int);
void ratic_update(ratic_context*, const unsigned char*, int);
void ratic_final(char*, ratic_context*);
