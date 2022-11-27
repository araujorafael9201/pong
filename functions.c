#include "utils.h"

void change_dir(Racket *r) {
    r->vel *= -1;
}

void change_x_dir(Ball b) {
    b.vel_x *= -1;
}

void change_y_dir(Ball b) {
    b.vel_y *= -1;
}

void move_racket(Racket *r) {
    r->y += r->vel;
}

void move_ball(Ball b) {
    b.y += b.vel_y;
    b.x += b.vel_x;
}
