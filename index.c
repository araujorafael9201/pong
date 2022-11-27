#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "utils.h"

int main() {

    int RACKET_WIDTH = 20;
    int RACKET_HEIGHT = 150;

    int DISPLAY_WIDTH = 600;
    int DISPLAY_HEIGHT = 600;

    int FRAMERATE = 30;

    al_init();
    al_init_primitives_addon();

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FRAMERATE);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT e;
    
    bool redraw = true;

    al_start_timer(timer);

    Racket player, computer;
    player.x = 0;
    // Puts Racket on the Right side of the screen
    computer.x = (DISPLAY_WIDTH - RACKET_WIDTH);
    
    // Centralizes Rackets vertically
    player.y = ((DISPLAY_HEIGHT / 2) - (RACKET_HEIGHT / 2)); 
    computer.y = ((DISPLAY_HEIGHT / 2) - (RACKET_HEIGHT / 2));

    while(1) {
        al_wait_for_event(queue, &e);
        if (e.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        } else if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }


        if (redraw && al_is_event_queue_empty(queue)) {
            // White Background
            al_clear_to_color(al_map_rgb(255, 255, 255));
            
            // Draw Rackets
            al_draw_filled_rectangle(player.x, player.y, (player.x + RACKET_WIDTH), (player.y + RACKET_HEIGHT), al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(computer.x, computer.y, (computer.x + RACKET_WIDTH), (computer.y + RACKET_HEIGHT), al_map_rgb(0, 0, 0));

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}
