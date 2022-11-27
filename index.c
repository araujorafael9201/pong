#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

int main() {

    int FRAMERATE = 30;

    al_init();

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* display = al_create_display(600, 600);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FRAMERATE);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT e;
    
    bool redraw = true;

    al_start_timer(timer);
    while(1) {
        al_wait_for_event(queue, &e);
        if (e.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        } else if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

/*         switch (e.type) { */
/*             case ALLEGRO_EVENT_TIMER: */
/*                 redraw = true; */

/*             case ALLEGRO_EVENT_DISPLAY_CLOSE: */
/*                 printf("Fechando..."); */
/*                 break; */
/*             case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: */
/*                 printf("Apertou o Mouse!"); */
/*         } */


        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), 10, 10, 0, "Hello, World!");
            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}
