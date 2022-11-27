#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    // Initialize rand()
    srand(time(NULL));

    int RACKET_WIDTH = 20;
    int RACKET_HEIGHT = 160;

    int DISPLAY_WIDTH = 600;
    int DISPLAY_HEIGHT = 600;

    int FRAMERATE = 30;

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FRAMERATE);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    ALLEGRO_EVENT e;
    
    bool redraw = true;

    Racket player, computer;
    player.x = 0;

    // Puts Racket on the Right side of the screen
    computer.x = (DISPLAY_WIDTH - RACKET_WIDTH);
    
    // Centralizes Rackets vertically
    player.y = ((DISPLAY_HEIGHT / 2) - (RACKET_HEIGHT / 2)); 
    computer.y = ((DISPLAY_HEIGHT / 2) - (RACKET_HEIGHT / 2));

    player.vel = 10;
    computer.vel = 10;
    
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
            
            // Draw Rackets
            al_draw_filled_rectangle(player.x, player.y, (player.x + RACKET_WIDTH), (player.y + RACKET_HEIGHT), al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(computer.x, computer.y, (computer.x + RACKET_WIDTH), (computer.y + RACKET_HEIGHT), al_map_rgb(0, 0, 0));

            
            // Randomly decides if computer will move
            bool comp_move = rand() % 11 == 1 ? true : false;
            if (comp_move) change_dir(&computer);

            // Check Colision
            if ((player.y == 0 && player.vel < 0) || ((player.y + RACKET_HEIGHT == DISPLAY_HEIGHT)) && player.vel > 0) {
                change_dir(&player);
            }
 
            if ((computer.y == 0 && computer.vel < 0) || ((computer.y + RACKET_HEIGHT == DISPLAY_HEIGHT)) && computer.vel > 0) {
                change_dir(&computer);
            }
            
            // Move Rackets
            move_racket(&player);
            move_racket(&computer);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}
