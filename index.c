#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "utils.h"

int RACKET_WIDTH = 20;
int RACKET_HEIGHT = 160;

int BALL_SIZE = 20;

int DISPLAY_WIDTH = 600;
int DISPLAY_HEIGHT = 500;

int FRAMERATE = 20;

void set_ball(Ball *ball) {
    ball->x = (DISPLAY_WIDTH / 2) - (BALL_SIZE / 2);
    ball->y = (DISPLAY_HEIGHT /2) - (BALL_SIZE / 2);
    ball->vel_x = (rand() % 2) == 1 ? 10 : -10;
    ball->vel_y = (rand() % 2) == 1 ? 10 : -10;
}

void set_racket(Racket *racket, bool is_player) {
    if (is_player) {
        racket->x = 0;
    } else {
        racket->x = (DISPLAY_WIDTH - RACKET_WIDTH);
    }
    // Centralizes Rackets vertically
    racket->y = (DISPLAY_HEIGHT / 2) - (RACKET_HEIGHT / 2);
    
    // Gives Racket a random initial direction
    racket->vel = rand() % 2 == 1 ? 10 : -10;
}

int main() {
    
    // Initialize rand()
    srand(time(NULL));

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FRAMERATE);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_set_window_title(display, "Pong");

    ALLEGRO_EVENT e;
    
    bool redraw = true;

    Racket player, computer;
    set_racket(&player, true);
    set_racket(&computer, false);

    Ball ball;
    set_ball(&ball);

    al_start_timer(timer);

    while(1) {
        al_wait_for_event(queue, &e);
        if (e.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        } else if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if (e.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (e.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                change_dir(&player);
            }
        }


        if (redraw && al_is_event_queue_empty(queue)) {
            // White Background
            al_clear_to_color(al_map_rgb(255, 255, 255));
            
            // Draw Rackets and Ball
            al_draw_filled_rectangle(player.x, player.y, (player.x + RACKET_WIDTH), (player.y + RACKET_HEIGHT), al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(computer.x, computer.y, (computer.x + RACKET_WIDTH), (computer.y + RACKET_HEIGHT), al_map_rgb(0, 0, 0));
            
            al_draw_filled_rectangle(ball.x, ball.y, (ball.x + BALL_SIZE), (ball.y + BALL_SIZE), al_map_rgb(0,0,0));
                
            
            // Randomly decides if computer will move
            bool comp_move = rand() % 10 == 1 ? true : false;
            if (comp_move) change_dir(&computer);

            // Check Colision (Rackets + Screen)
            if ((player.y == 0 && player.vel < 0) || ((player.y + RACKET_HEIGHT == DISPLAY_HEIGHT)) && player.vel > 0) {
                change_dir(&player);
            }
 
            if ((computer.y == 0 && computer.vel < 0) || ((computer.y + RACKET_HEIGHT == DISPLAY_HEIGHT)) && computer.vel > 0) {
                change_dir(&computer);
            }

            // Check Colision (Ball + Screen)
            if (ball.y == 0 || ball.y + BALL_SIZE == DISPLAY_HEIGHT) {
                change_y_dir(&ball);
            }

            // Check Colision (Ball + Racket) and Check if Point
            if (ball.x == 0 + RACKET_WIDTH) {
                if (ball.y >= player.y && ball.y + BALL_SIZE <= player.y + RACKET_HEIGHT) {
                    change_x_dir(&ball);
                }
            }

            if (ball.x + BALL_SIZE == DISPLAY_WIDTH - RACKET_WIDTH) {
                if (ball.y >= computer.y && ball.y + BALL_SIZE <= computer.y + RACKET_HEIGHT) {
                    change_x_dir(&ball);
                }
            }

            if (ball.x == 0) {
                set_ball(&ball);
                set_racket(&player, true);
                set_racket(&computer, false);
            } else if (ball.x + BALL_SIZE == DISPLAY_WIDTH) {
                set_ball(&ball);         
                set_racket(&player, true);
                set_racket(&computer, false);
            } 
            
            // Move Rackets and Ball
            move_racket(&player);
            move_racket(&computer);
            move_ball(&ball);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}
