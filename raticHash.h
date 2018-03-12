typedef struct _ratic_context {
	int hash_len;
	int message_len;
	unsigned char LCG;
	unsigned char* state;
	unsigned char* prev_state;
} ratic_context;

ratic_context* ratic_init(int);
void ratic_update(ratic_context*, const char*, int);
void ratic_final(char*, ratic_context*);
