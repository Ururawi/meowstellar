#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
int main ()
{
  ALLEGRO_DISPLAY* disp;
  ALLEGRO_EVENT_QUEUE*eventos;
  ALLEGRO_EVENT evento;
  ALLEGRO_FONT menuFuente;
  int fin=0;
  if (!al_init())
  {
    printf("No ALLEGRO");
    fin=1;
  }
  if (!al_install_keyboard())
  {
    printf ("No TECLADO");
    fin=1;
  }
  if (!al_init_font_addon() || !al_init_ttf_addon())
  {
      printf ("\nNo se pudo cargar la fuente");
      fin=1;
  }
  if (fin==0)
  {
    disp=al_create_display (800, 600);
    al_set_window_title (disp, "Meowstellar");
    eventos= al_create_event_queue();
    al_register_event_source(eventos, al_get_display_event_source(disp));
    al_register_event_source(eventos, al_get_keyboard_event_source());
    while (fin==0)
    {
      al_wait_for_event;
      switch (evento.type)
      {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            printf("\nVentana cerrada");
            fin=1;
            break;
      }
    }
    al_destroy_event_queue(eventos);
    al_destroy_display(disp);
    al_destroy_font(menuFuente);
  }
  return 0;
}
