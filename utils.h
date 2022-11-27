typedef struct {
    int x;
    int y;

    // 1 for UP, -1 for DOWN
    int vel;
} Racket;

typedef struct {
    int x;
    int y;

    // 1 for RIGHT, -1 for LEFT
    int vel_x;

    // 1 for UP, -1 for DOWN
    //
    int vel_y;
} Ball;


void change_dir(Racket r);
void change_x_dir(Ball b);
void change_y_dir(Ball b);
