#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

void menu()
{
  return;
}

int main ()
{
  ALLEGRO_DISPLAY* disp;
  ALLEGRO_EVENT_QUEUE*eventos;
  ALLEGRO_EVENT evento;
  ALLEGRO_FONT menuFuente, menuFuent2;
  ALLEGRO_BITMAP *fondoMenu, *vestIcono, *iconoJuego;
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
    menuFuente= al_load_font("Desktop\\Starborn.ttf",  60, 0);
    menuFuent2= al_load_font("Desktop\\Starborn.ttf",  40, 0);
    vestIcono=al_load_bitmap("");
    iconoJuego=al_load_bitmap("C:\\Users\\LACE\\Desktop\\.png");
    al_set_display_icon(disp, iconoJuego);
    al_register_event_source(eventos, al_get_display_event_source(disp));
    al_register_event_source(eventos, al_get_keyboard_event_source());
    while (fin==0)
    {
      if (al_event_queue_is_empty(eventos))
      {
        al_draw_text (menuFuente, al_map_rgb(255, 255, 255),300, 15, 0, "MENÚ");
        al_draw_text (menuFuent2, al_map_rgb(255, 255, 255), 300, 80, 0, "Jugar");
        al_draw_text (menuFuent2, al_map_rgb(255, 255, 255), 300, 140, 0, "Ajustes");
        al_draw_text (menuFuent2, al_map_rgb(255, 255, 255), 300, 200, 0, "Logros");
        al_draw_scaled_bitmap (vestIcono, x, y, largo, ancho, xvent, yvent, largo, ancho, 0);
      }
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
    al_destroy_font(menuFuent2);
    al_destroy_bitmap (fondoMenu);
    al_destroy_bitmap (vestIcono);
    al_destroy_bitmap (iconoJuego);
  }
  return 0;
}
