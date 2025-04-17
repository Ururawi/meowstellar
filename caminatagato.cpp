#include<stdio.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
//#include<allegro5\allegro_font.h>
//#include<allegro5\allegro_ttf.h>
//#include<allegro5\allegro_primitives.h>

void inicializar()
{
    int fin=0;
    if(al_init()==0)
    {
        printf("No se pudo incicializar allegro");
        fin=1;
    }
    /*if(al_init_primitives_addon()==0)
    {
        printf("No se pudo inicializar primitives");
        fin=1;
    }*/

    if(!al_install_keyboard())
    {
        printf("No se inicializ%C el teclado", 162);
        fin=1;
    }
    
    //al_init_font_addon();   //iniciar fuentes
    //al_init_ttf_addon();    //iniciar ttf
    al_init_image_addon(); //iniciar las imágenes
    return; 
}


typedef struct 
{
    int sx, sy, sw, sh;
} cuadros;
enum orientacua 
{
    CDERECHA = 0,
    CIZQUIERDA = 1,
    CARRIBA = 2,
    CABAJO = 3
};
cuadros coordenadas[4][3] = //matriz
{
    { {330,  32, 109, 150}, {451, 33, 109, 150}, {580,  30, 109, 150} }, // Derecha
    { {580, 219, 109, 150}, {460, 222, 109, 150}, {331, 216, 109, 150} }, // Izquierda
    { {331, 405, 109, 150}, {453, 420, 109, 150}, {588, 406, 109, 150} }, // Arriba
    { {326, 586, 109, 150}, {455, 594, 109, 150}, {598, 597, 109, 150} }  // Abajo
  
};


int main()
{
    
    inicializar();

    ALLEGRO_DISPLAY *disp;
    ALLEGRO_EVENT_QUEUE* eventos;
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP *gato;
    ALLEGRO_TIMER *tempocar;
    
    
    disp=al_create_display(1000,700); //generar disp
    al_set_window_title (disp, "Meowstellar");//nombre de la ventana
    eventos = al_create_event_queue(); //eventos->crear cola de eventos

    tempocar=al_create_timer(0.08);

    al_register_event_source(eventos, al_get_timer_event_source(tempocar));
    al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos,al_get_keyboard_event_source());

    al_start_timer(tempocar);

    int actual = 0; //cuadro que se esté usando
    int orienta = CABAJO, x=472, y=312;
    int fin =0,camina=0, otravez=0;
    int mdere= 0, mizq=0, marrib=0, mabaj=0;
    
    gato=al_load_bitmap("carnaran.png");
    if(!gato)
    {
        printf("No se carg%c la imagen", 163);
        fin=1;
    }

    
    while(fin==0)
    {

        ALLEGRO_EVENT evento;
        al_wait_for_event(eventos, &evento);

        switch (evento.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;

            case ALLEGRO_EVENT_TIMER:
            if (mdere) 
            {
                x += 6;
                if (x > 950) x = 950;
                orienta = CDERECHA;
                camina = 1;
            }
            if (mizq) 
            {
                x -= 4;
                if (x < 0) x = 0;
                orienta = CIZQUIERDA;
                camina = 1;
            }
            if (marrib) {
                y -= 4;
                if (y < 0) y = 0;
                orienta = CARRIBA;
                camina = 1;
            }
            if (mabaj) 
            {
                y += 4;
                if (y > 620) y = 620;
                orienta = CABAJO;
                camina = 1;
            }

            if (camina)
                actual = (actual + 1) % 3;
            else
                actual = 0;

            otravez = 1;
            break;

            case ALLEGRO_EVENT_KEY_DOWN:
            switch (evento.keyboard.keycode) 
            {
                case ALLEGRO_KEY_RIGHT:
                    mdere = 1;
                    break;
                case ALLEGRO_KEY_LEFT:
                    mizq = 1;
                    break;
                case ALLEGRO_KEY_UP:
                    marrib = 1;
                    break;
                case ALLEGRO_KEY_DOWN:
                    mabaj = 1;
                    break;
            }
            break;
        
        case ALLEGRO_EVENT_KEY_UP:
            switch (evento.keyboard.keycode) {
                case ALLEGRO_KEY_RIGHT:
                    mdere = 0;
                    break;
                case ALLEGRO_KEY_LEFT:
                    mizq = 0;
                    break;
                case ALLEGRO_KEY_UP:
                    marrib = 0;
                    break;
                case ALLEGRO_KEY_DOWN:
                    mabaj = 0;
                    break;
            }
            if (!mdere && !mizq&& !marrib && !mabaj)
                    camina = 0;
            break;
        }

        if (otravez && al_is_event_queue_empty(eventos)) 
        {
            otravez = 0;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            cuadros f = coordenadas[orienta][actual];
            float escala = 0.7;

            al_draw_scaled_bitmap(gato, f.sx, f.sy, f.sw, f.sh, x, y, f.sw * escala, f.sh * escala, 0);

            al_flip_display();
        }
    }
    
    al_destroy_display(disp);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(gato);

    return 0;
}
