#include <stdlib.h>
#include <time.h>
#include<stdio.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_primitives.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
//fonsch es el fondo
//foncch es la chispa
int main()
{
    //Declarar
    ALLEGRO_DISPLAY *disp; //para el display
    ALLEGRO_EVENT_QUEUE* eventos; //para eventos-> cola de eventos
    ALLEGRO_EVENT evento;  //evento-> evento de la cola de eventos
    ALLEGRO_BITMAP *fonsch;
    ALLEGRO_BITMAP *foncch; 
    ALLEGRO_BITMAP *cable; 
    ALLEGRO_BITMAP *cola;//para el fondo
    ALLEGRO_BITMAP *fondocab;
    ALLEGRO_BITMAP *fondochis;
    ALLEGRO_BITMAP *fondolib;
    ALLEGRO_TIMER* enchispa;
    ALLEGRO_TIMER* deschispa;
    ALLEGRO_TIMER* mueve;


    srand(time(NULL));
    int fin=0, chis=0, barra=0, limit=0,vic=0;
    int x, y, xfon=1000, xcol=700, ycol=600,n1=225,n2=265,n3=185,x1,x2;
    
    //inicializar funciones
    al_init();  //iniciar allegro
    al_init_primitives_addon(); //iniciar primitivos
    al_install_keyboard();  //iniciar teclado
    al_init_font_addon();   //iniciar fuentes
    al_init_ttf_addon();    //iniciar ttf
    al_init_image_addon(); //iniciar las imágenes

    disp=al_create_display(1000,700); //generar display y su tamaño
    al_set_window_title (disp, "Meowstellar");//nombre de la ventana
    eventos = al_create_event_queue(); //eventos->crear cola de eventos
    al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos, al_get_keyboard_event_source()); // registrar eventos de teclado
    enchispa = al_create_timer(1.5);
    deschispa = al_create_timer(1.0);
    mueve = al_create_timer(0.003);
    al_register_event_source(eventos, al_get_timer_event_source(enchispa));
    al_register_event_source(eventos, al_get_timer_event_source(deschispa));
    al_register_event_source(eventos, al_get_timer_event_source(mueve));
    al_start_timer(enchispa);
    al_start_timer(deschispa);
    al_start_timer(mueve);


    //cargar imagenes
    fonsch=al_load_bitmap("fondo.png"); //Ruta de la imagen de la imagen sin chispa
    foncch=al_load_bitmap("chispa.png"); //Ruta de la imagen de la imagen de la 
    cable=al_load_bitmap("cable.png"); //Ruta de la imagen de la imagen del cable
    cola=al_load_bitmap("colita.png");
    fondocab=al_load_bitmap("fondocab.jpeg");
    fondochis=al_load_bitmap("fondochis.jpeg");
    fondolib=al_load_bitmap("fondolib.jpeg");
    //si no se carga el fondo
    if(!fonsch||!foncch)
    {
        printf("No se carg%c la imagen", 162);
        fin=1;
    }
    x=rand()%3000-950;
    y=rand()%650;
    x1=rand()%233+225;
    x2=rand()%250+475;
    while(fin==0)
    {
        if(n1>724)
            limit=1;
        if(n1<226)
            limit=0;
        if(al_event_queue_is_empty(eventos))
        {
            
            al_draw_bitmap_region(fonsch,xfon,0,1000,700,0,0,0);
            al_draw_scaled_bitmap(cable,115,94,100,280,x,y,60,60,0);
            al_draw_scaled_bitmap(cola,377,0,132,700,xcol,ycol,132,700,0);
            if(chis==1)
                al_draw_scaled_bitmap(foncch,220,120,400,400,x-15,y+20,40,40,0);
            if(barra==1&&vic!=21)
            {
                al_draw_scaled_bitmap(fondocab,0,0,1000,700,0,0,1000,700,0);
                if(chis==1)
                    al_draw_scaled_bitmap(fondochis,0,0,1000,700,0,0,1000,700,0);
                al_draw_filled_rectangle(225,200,725,240,al_map_rgb(200,200,0));
                al_draw_filled_rectangle(x1,200,x2,240,al_map_rgb(200,0,0));
                al_draw_filled_triangle(n1,240,n2,280,n3,280,al_map_rgb(0,200,200));
            }
            if(vic==21)
                al_draw_scaled_bitmap(fondolib,0,0,1000,700,0,0,1000,700,0);
            al_flip_display();//mandarlo al display
            printf("%i",x);
        }
        al_wait_for_event(eventos, &evento);
        switch(evento.type)


        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                printf("\nVentana cerrada");
                fin=1;
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                printf("\nAdentro");
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
                printf ("\nAfuera");
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                printf("\nTecla Allegro: %i", evento.keyboard.keycode);//tecla que presionaste
                if(evento.keyboard.keycode==82)
                {
                   
                    if(xfon>=0)
                    {
                        xfon-=6;
                        x+=6;
                        xcol+=6;
                    }
                }
                if(evento.keyboard.keycode==83)
                {
                    if(xfon<=2000)
                    {
                        xfon+=6;
                        x-=6;
                        xcol-=6;
                    }
                }
                if(evento.keyboard.keycode==23)
                {
                    if(ycol>=0)
                        ycol-=6;     
                }
                if(evento.keyboard.keycode==19)
                {
                    if(ycol<=700)
                        ycol+=6;     
                }
                if(evento.keyboard.keycode==1)
                {
                    if(xcol>=-1000)
                        xcol-=6;     
                }
                if(evento.keyboard.keycode==4)
                {
                    if(xcol<=2000)
                        xcol+=6;     
                }
                if(evento.keyboard.keycode==67)
                {
                    if(xcol>=x&&xcol<=x+60&&ycol>=y&&ycol<=y+60)
                        barra=1; 
                    if(n1>x1&&n1<x2)
                    {
                        x1=rand()%233+225;
                        x2=rand()%250+475;
                        vic+=1;
                    }
                    else
                    {
                        if(barra==1)
                        {
                            barra = 0;
                            vic = 0;
                            x = rand() % 3000 - 950;
                            y = rand() % 650;
                            xfon = 1000;
                            xcol = 700;
                            ycol = 600;
                            n1 = 225;
                            n2 = 265;
                            n3 = 185;
                            x1 = rand() % 233 + 225;
                            x2 = rand() % 250 + 475;
                        }
                    }
                    
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                if(evento.timer.source==enchispa)
                    chis=1;
                
                if(evento.timer.source==deschispa)
                    chis=0;
                if(evento.timer.source==mueve)
                {
                    if(limit==0)
                    {
                        n1+=2;
                        n2+=2;
                        n3+=2;
                    }
                    else
                    { 
                        n1-=2;
                        n2-=2;
                        n3-=2;
                    }
                } 
                break;
                
         
           }
    }
    //destruir:
    al_destroy_display(disp);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(fonsch);
    al_destroy_bitmap(foncch);
    
    return 0;
}