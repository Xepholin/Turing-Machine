typedef enum    {
    LEFT,
    RIGHT,
    HOLD,
} DIRECTION;

typedef struct tapes    {
    struct tapes * right;
    struct tapes * left;
    char content;
} TAPE;

typedef struct transition   {
    char begin_state;
    char tape_old_symbol;
    char after_state;
    char tape_new_symbol;
    DIRECTION dir;
} TRANSITION;

typedef struct turing_machine   {
    char * states;
    char * symbols;
    char * accept_state;
    char * reject_state;
    TAPE * tape;
    TRANSITION * transition;
} TM;
