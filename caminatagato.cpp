//camina simple
#include<stdio.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>

int fin=0;

ALLEGRO_DISPLAY *disp;
ALLEGRO_EVENT_QUEUE *eventos;
ALLEGRO_EVENT evento;
ALLEGRO_TIMER *tempocar;
ALLEGRO_BITMAP *gato;

void inicializar()
{
    if (!al_init())
    {
        printf("No se pudo inicializar Allegro\n");
        fin = 1;
    }

    if (!al_init_image_addon())
    {
        printf("No se pudieron iniciar las imágenes\n");
        fin = 1;
    }

    if (!al_install_keyboard())
    {
        printf("No se pudo inicializar el teclado\n");
        fin = 1;
    }
}

typedef struct 
{
    int sx, sy, sw, sh;
} cuadros;

enum orientacua //enumerar el tipo de movimientos
{
    movder = 0, //movimiento a la derecha
    movizqu = 1, //movimiento a la izquierda
    movarrib = 2, //movimiento arriba
    movabaj = 3 //movimiento abajo
};

cuadros coordenadas[4][3] = //matriz, son las coordenadas de cada cuadro en orden para formar su movimiento
{
    { {330,  32, 109, 150}, {451, 33, 109, 150}, {580,  30, 109, 150} }, // Derecha
    { {580, 219, 109, 150}, {460, 222, 109, 150}, {331, 216, 109, 150} }, // Izquierda
    { {331, 405, 109, 150}, {453, 420, 109, 150}, {588, 406, 109, 150} }, // Arriba
    { {455, 594, 109, 150},{326, 586, 109, 150}, {598, 597, 109, 150} }  // Abajo
  
};

int main()
{
    int mdere = 0, mizq = 0, marrib = 0, mabaj = 0;
    
    inicializar();

    disp=al_create_display(1000,700); //generar disp
    al_set_window_title (disp, "Meowstellar");//nombre de la ventana
    eventos = al_create_event_queue(); //eventos->crear cola de eventos

    tempocar=al_create_timer(0.08);

    al_register_event_source(eventos, al_get_timer_event_source(tempocar));
    al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos,al_get_keyboard_event_source());

    al_start_timer(tempocar);
    gato=al_load_bitmap("carnaran.png");
    if(!gato)
    {
        printf("No se carg%c la imagen", 163);
        fin=1;
    }

    int actual = 0; //cuadro que se esté usando
    int orienta = movabaj, x=472, y=312, camina=0;

    al_wait_for_event(eventos, &evento);

    while(fin==0)
    {
        switch (evento.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;
            //detectar si se presiona la tecla 
            case ALLEGRO_EVENT_KEY_DOWN:
                    switch (evento.keyboard.keycode)
                    {
                        case 83: 
                            mdere=1; 
                            break;
                        case 82: 
                            mizq=1; 
                            break;
                        case 84: 
                            marrib=1;
                            break;
                        case 85: 
                            mabaj=1; 
                            break;
                    }
                    break;
            
            case ALLEGRO_EVENT_KEY_UP:
                    switch (evento.keyboard.keycode)
                    {
                        case 83: 
                            mdere=0; 
                            break;
                        case 82: 
                            mizq=0; 
                            break;
                        case 84: 
                            marrib=0;
                            break;
                        case 85: 
                            mabaj=0; 
                            break;
                    }
                    if (!mdere && !mizq && !marrib && !mabaj)
                        camina = 0;
                    break;

            case ALLEGRO_EVENT_TIMER:
                camina = mdere || mizq || marrib || mabaj;

                if(mdere) 
                { 
                    if(x+8<1000)
                    {
                        x+=8; 
                        orienta=movder; 
                    }
                }
                if(mizq)  
                { 
                    if(x-8>0)
                    {
                        x-=8; 
                        orienta=movizqu; 
                    }
                }
                if(marrib)
                { 
                    if(y-8>0)
                    {
                        y-=8; 
                        orienta=movarrib;
                    } 
                }
                if(mabaj) 
                { 
                    if(y+8<630)
                    {
                        y+=8; 
                        orienta=movabaj; 
                    }
                }
                if(camina)
                    actual=(actual+1)%3;
                else
                actual = 0;
                 
                al_clear_to_color(al_map_rgb(0, 0, 0));//al_draw_scaled_bitmap(fondo, 0, 0, 1000, 700, 0, 0, 1000, 700, 0); por si hay fondo

                cuadros f = coordenadas[orienta][actual];
                float escala = 0.7;
                al_draw_scaled_bitmap(gato, f.sx, f.sy, f.sw, f.sh, x, y, f.sw * escala, f.sh * escala, 0);

                al_flip_display();
                break;
        }
    }
    al_destroy_display(disp);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(gato);
    return 0;
}
