#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
int main ()
{
  ALLEGRO_DISPLAY* disp;
  ALLEGRO_EVENT_QUEUE*eventos;
  ALLEGRO_EVENT evento;
  int fin=0;
  if (!al_init())
  {
    printf("No ALLEGRO");
    fin=1;
  }
  return 0;
}
