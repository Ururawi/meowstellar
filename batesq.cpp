//BATALLA--->Estilo Undertale :)
#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<allegro5\allegro_image.h>
 
#define ldisp 1000 //largo del display
#define adisp 700 //ancho del display

#define cobs 20 //cantidad de obstaculos
#define tamobs 15 //radio de los obstaculos (circulos)
#define tamest 10

typedef struct
{
    int x, y, vel; //para sus coordenadas y su velocidad
}Estambre; 
typedef struct 
{
    int x, y; //coords 1
    int dx, dy; //coords 2
    int iniciar;
}Obstaculo;

int revisdist(Estambre e, Obstaculo o) //calcula para saber si se están tocando o no
{
    int dx = e.x - o.x;  // dif en x
    int dy = e.y - o.y;  // dif en y
    int dist = dx * dx + dy * dy;  //distancia

    return dist<(tamest+tamobs)*(tamest+tamobs); // ¿se tocan? la distancia menor a los tamaños de los obs y el usuario
}
void apobs(Obstaculo* o)//para colocar los obstaculos alrededdor del disp
{
    int lad= rand()%4; //elige aleatoriammente un lado del disp
    //o es puntero, entonces ->
    switch(lad)
    {
        case 0:
            o->x = 0; //aparece del lado izquierdo
            o->y = rand() % adisp; //lugar
            o->dx = 2 + rand() % 3; //velocidad
            o->dy = (rand() % 3) - 1; //a dónde va?
            break;
        case 1:
            o->x = ldisp; //Desde la derecha
            o->y = rand() % adisp; //lug
            o->dx = - (2 + rand() % 3); //vel
            o->dy = (rand() % 3) - 1; //a donde
            break;
        case 2:
            o->x = rand() % ldisp; //Arriba
            o->y = 0;
            o->dy = 2 + rand() % 3;
            o->dx = (rand() % 3) - 1;
            break;
        case 3:
            o->x = rand() % ldisp; //Abajo
            o->y = adisp;
            o->dy = - (2 + rand() % 3);
            o->dx = (rand() % 3) - 1;
            break;
    }
    o->iniciar=1;
} 

int obsal(Obstaculo obstaculos[]) //para que los obstaculos salgan
{
    for (int i=0;i<cobs;i++) 
    {
        if (obstaculos[i].x>=0 && obstaculos[i].x<=ldisp && obstaculos[i].y >= 0 && obstaculos[i].y <= adisp)
            return 0; // 
    }
    return 1; // Obstaculos afuera
}

int main()
{
    //inicializar:
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();

    
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_EVENT_QUEUE* eventos;
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP *estam;
    ALLEGRO_TIMER *tiempo;
    ALLEGRO_KEYBOARD_STATE tecla;
    ALLEGRO_BITMAP *bestam;
    
    int fin=0;
    //registar
    disp=al_create_display(ldisp,adisp);

    bestam=al_load_bitmap("estambre.png");
    if (!bestam) 
    {
        printf("No se pudo cargar la imagen del jugador.\n");
        fin=1;
    }


    al_set_window_title (disp, "Meowstellar");//nombre de la ventana
    tiempo=al_create_timer(1.0 / 60);
    
    eventos = al_create_event_queue(); //eventos->crear cola de eventos
    al_register_event_source(eventos, al_get_timer_event_source(tiempo));
    al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos,al_get_keyboard_event_source());

    srand(time(NULL)); //semilla de lo aleatorio
    

    Estambre estambre= { ldisp / 2, adisp / 2, 4 };
    Obstaculo obstaculos[cobs];

    for (int i=0;i<cobs;i++)
        apobs(&obstaculos[i]);

    int corre= 1;
    int redibuja= 1;

    double cuenta= al_get_time();
    int ganaste= 0;
    

    al_start_timer(tiempo);
    while(corre)
    {
        al_wait_for_event(eventos, &evento);
        if (evento.type == ALLEGRO_EVENT_TIMER) 
        {
            al_get_keyboard_state(&tecla);
            if (!ganaste) 
            {
                // Para moversw
                if (evento.keyboard.keycode==84 && estambre.y-tamest>0)
                {
                    estambre.y -= estambre.vel;
                }
                if (al_key_down(&tecla, 85) && estambre.y+tamest<adisp)
                {
                    estambre.y += estambre.vel;
                }
                if (al_key_down(&tecla, 82) && estambre.x-tamest>0)
                {
                    estambre.x -= estambre.vel;
                }
                if (al_key_down(&tecla, 83) && estambre.x+tamest<ldisp)
                {
                    estambre.x += estambre.vel;
                }
            }
            // 15 segundos
            if (!ganaste && al_get_time()-cuenta>= 15.0) 
            {
                ganaste= 1;
                printf("Ganaste\n");
            }
            //ejecuta
            for (int i = 0; i < cobs; i++) 
            {
                if (obstaculos[i].iniciar) 
                {
                    obstaculos[i].x += obstaculos[i].dx;
                    obstaculos[i].y += obstaculos[i].dy;

                    if (!ganaste) 
                    {
                        if (revisdist(estambre, obstaculos[i])) 
                        {
                            printf("Perdiste\n");
                            corre=0;
                        }
                        // rep
                        if (obstaculos[i].x < 0 || obstaculos[i].x > ldisp ||obstaculos[i].y < 0 || obstaculos[i].y > adisp) 
                        {
                            apobs(&obstaculos[i]);
                        }
                    }
                    // salen obstaculos
                }
            }
            if (ganaste && obsal(obstaculos)) 
            {
                corre=0;
            }
            redibuja=1;
        }
        if (redibuja && al_is_event_queue_empty(eventos)) 
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_scaled_bitmap(bestam,97,144,238,235,estambre.x-15,estambre.y-15,30,30,0);

            for (int i=0; i < cobs; i++) {
                if (obstaculos[i].iniciar)
                    al_draw_filled_circle(obstaculos[i].x, obstaculos[i].y, tamobs, al_map_rgb(255, 255, 255));
            }
            al_flip_display();
            redibuja=0;
        }
    }
    al_destroy_display(disp);
    al_destroy_timer(tiempo);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(bestam);

    return 0;
}