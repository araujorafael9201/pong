typedef struct {
    int x;
    int y;

    // Negative vel for UP, Positive vel for DOWN
    int vel;
} Racket;

typedef struct {
    int x;
    int y;

    // Negative vel_x for LEFT, Positive vel_x for RIGHT
    int vel_x;

    // Negative vel_y for UP, Positive vel_y for DOWN
    int vel_y;
} Ball;


void change_dir(Racket *r);
void change_x_dir(Ball *b);
void change_y_dir(Ball *b);
void move_racket(Racket *r);
void move_ball(Ball *b);
