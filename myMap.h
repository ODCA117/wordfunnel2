typedef struct Value {
    int value;
} Value;

typedef struct Key {
    char * key;
} Key;

typedef struct Map {
    struct Key;
    struct Value;
} Map;

int get_Hash(char *word);

Value * getValue(Key key);
