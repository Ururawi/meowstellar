#include<stdio.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_primitives.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main()
{
    //Declarar
    ALLEGRO_DISPLAY *disp; //para el display
    ALLEGRO_EVENT_QUEUE* eventos; //para eventos-> cola de eventos
    ALLEGRO_EVENT evento;  //evento-> evento de la cola de eventos
    ALLEGRO_BITMAP *fondo; //para el fondo
    ALLEGRO_FONT *menuFuente; 
    ALLEGRO_FONT *menuFuente2; //fuentes menú
    ALLEGRO_COLOR blanco= al_map_rgb(255,255,255);
    ALLEGRO_BITMAP *vestIcono;
    int fin=0;
    int x=270, y=270; //coordenadas del circulo que se mueve

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
    menuFuente= al_load_font("C:\\Users\\hp\\DESKTOP\\typopixel.ttf",  60, 0);//para la fuente
    menuFuente2= al_load_font("C:\\Users\\hp\\DESKTOP\\PixelDraft.ttf",  50, 0);
    if(evento.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                evento.type=0;
    al_register_event_source(eventos,al_get_display_event_source(disp));
    al_register_event_source(eventos,al_get_keyboard_event_source());
    //cargar fondo
    fondo=al_load_bitmap("C:\\Users\\hp\\DESKTOP\\imagmenu.png"); //Ruta de la imagen
    vestIcono=al_load_bitmap("C:\\Users\\hp\\DESKTOP\\icon.png");
    //si no se carga el fondo
    if(!fondo||!vestIcono)
    {
        printf("No se carg%c la imagen", 162);
        fin=1;
    }
    while(fin==0)
    {
        if(al_event_queue_is_empty(eventos))
        {
            al_draw_scaled_bitmap(fondo,0,0,1000,700,0,0,1000,700,0);
            al_draw_scaled_bitmap(vestIcono,386,224,180,172,880,600,70,66,0);//imagen persona
            al_draw_scaled_bitmap(vestIcono,707,248,180,172,865,500,300,302,0);//gato vestuario
            //los primeros son de la ventana y los segundos de la imagen

            //dibujar cuadros
            al_draw_rectangle(320,235,740,310,blanco, 4);
            al_draw_rectangle(320,335,740,410,blanco, 4);
            al_draw_rectangle(320,435,740,510,blanco, 4);
            al_draw_rectangle(320,535,740,610,blanco, 4);
            al_draw_rectangle(870,500,960,582,blanco, 4);
            al_draw_rectangle(870,590,960,675,blanco, 4);
            al_draw_line(130,200,870,200,blanco, 4);
            //bordes circulos
            al_draw_circle(270,270,30,blanco,4);
            al_draw_circle(270,370,30,blanco,4);
            al_draw_circle(270,470,30,blanco,4);
            al_draw_circle(270,570,30,blanco,4);


            al_draw_text (menuFuente, blanco,130, 100, 0, "MEOWSTELLAR");//título
            al_draw_text (menuFuente2, blanco, 350, 250, 0, "Jugar");
            al_draw_text (menuFuente2, blanco, 350, 350, 0, "Nueva Partida");
            al_draw_text (menuFuente2, blanco, 350, 450, 0, "Ajustes");
            al_draw_text (menuFuente2, blanco, 350, 550, 0, "Logros");

            al_draw_filled_circle(x,y,20,blanco); //cículo para seleccionar modo

            al_flip_display();//mandarlo al display
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
                if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    if(y+100<610)
                    y += 100;  // mover hacia abajo
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_UP) {
                    if(y-100>200)
                    y -= 100;  // mover hacia arriba
                }
                break;
            }
    }
    //destruir:
    al_destroy_display(disp);
    al_destroy_font(menuFuente);
    al_destroy_font(menuFuente2);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(fondo);
    
    return 0;
}