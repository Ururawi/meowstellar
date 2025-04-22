#include<stdio.h>
#include<time.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<stdlib.h>
#include<math.h>
//defines comunes para el juego:
#define LARGO 1000 //largo del display
#define ALTO 700 //ancho del display
//define para juego laberinto:
#define FILAS 20
#define COLUMNAS 30
#define TAM_CELDA_LARGO (LARGO / COLUMNAS)
#define TAM_CELDA_ALTO (ALTO / FILAS)
//defines para nivel undertale:
#define cobs 20 //cantidad de obstaculos
#define tamobs 15 //radio de los obstaculos (circulos)
#define tamest 10
ALLEGRO_DISPLAY *disp;
ALLEGRO_EVENT_QUEUE* eventos;
ALLEGRO_EVENT evento;
ALLEGRO_TIMER *tempocar;
ALLEGRO_BITMAP *gato;
ALLEGRO_BITMAP *fondo;
ALLEGRO_BITMAP *fondo2;
ALLEGRO_BITMAP *luzBlanca, *luzRoja,*luzMorada,*luzAmarilla;
ALLEGRO_COLOR blanco= al_map_rgb(255,255,255);
ALLEGRO_FONT *fuente, *fuente2; 
ALLEGRO_TIMER *tiempoplaca;
ALLEGRO_TIMER *tiempTexto;
ALLEGRO_FONT *menuFuente; 
ALLEGRO_FONT *menuFuente2; 
ALLEGRO_FONT *menuFuente3;
ALLEGRO_BITMAP *gatito;
//DECLARACIÓN DE VARIABLES ENTERAS GLOBALESS
int fin=0, capitulo_actual=1;
int rondaActual=0, desafioActivo=0, totalRondas=6;
int eponplaca=0; //si se pone en placa
int luzencendida=-1;  //-1=ninguna
int mostrarTextoInicio=0;
int mostrarDialogoConejo=0;
int esperandoTecla=0;
int conejoListo=0; //El conejo está en el lugar que debe
int descompleto=0; //desafío completado
int desafio2Activo=0;
char mensajeRonda[30]="";
char n=1;
int  xAj=270, yAj=265;
void ajustes(int xAj, int yAj)
{
    
    al_draw_text(menuFuente, blanco,130, 100, 0, "AJUSTES");//Título
    //Círculos para seleccionar opción
    al_draw_circle(270,265,15,blanco,4);
    al_draw_circle(270,465,15,blanco,4);
    al_draw_circle(270,515,15,blanco,4);
    al_draw_circle(270,565,15,blanco,4);
    al_draw_circle(270,615,15,blanco,4);
    //Opciones a elegir
    al_draw_text (menuFuente2, blanco, 350, 350, 0, "-------TECLAS-------");
    al_draw_text (menuFuente3, blanco, 350, 450, 0, "Arriba");
    al_draw_text (menuFuente3, blanco, 350, 500, 0, "Abajo");
    al_draw_text (menuFuente3, blanco, 350, 550, 0, "Derecha");
    al_draw_text (menuFuente3, blanco, 350, 600, 0, "Izquierda");
    al_draw_filled_circle(xAj,yAj,20,blanco);
    al_flip_display();
    return;
}
void vestuario()
{
    ALLEGRO_BITMAP *flecha;
    flecha= al_load_bitmap("flecha.png");
    char gato[20];
    al_draw_text(menuFuente, blanco,130, 100, 0, "VESTUARIO");//Título
    switch (n)
    {
        case 1:
            strcpy(gato, "griscar.png");
            break;
        case 2:
            strcpy(gato, "rayascar.png");
            break;
        case 3:
            strcpy(gato, "prcar.png");
            break;
        case 4:
            strcpy(gato, "carnaran.png");
            break;
        case 5:
            strcpy(gato, "calico.png");
            break;
    }
    gatito=al_load_bitmap(gato);
    al_draw_scaled_bitmap(gatito, 454, 590, 110, 140, 370, 370, 220, 280,0);
    al_draw_scaled_bitmap(flecha, 0, 0, 100, 100, 700, 500, 100, 100, 0);
    al_flip_display();
    return;
}
void menu1(ALLEGRO_BITMAP *fondo, ALLEGRO_BITMAP *vestIcono)
{
    al_draw_scaled_bitmap(fondo,0,0,1000,700,0,0,1000,700,0);
    al_draw_scaled_bitmap(vestIcono,386,224,180,172,880,600,70,66,0);//imagen persona
    al_draw_scaled_bitmap(vestIcono,707,248,180,172,865,500,300,302,0);//gato vestuario
    //los primeros son de la ventana y los segundos de la imagen

    //dibujar cuadros
    al_draw_rectangle(320,235,740,310,blanco, 4);
    //
    al_draw_rectangle(320,435,740,510,blanco, 4);
    //al_draw_rectangle(320,535,740,610,blanco, 4);
    al_draw_rectangle(870,500,960,582,blanco, 4);
    al_draw_rectangle(870,590,960,675,blanco, 4);
    al_draw_line(130,200,870,200,blanco, 4);
    //bordes circulos
    al_draw_circle(270,270,30,blanco,4);
    //al_draw_circle(270,370,30,blanco,4);
    al_draw_circle(270,470,30,blanco,4);
    //al_draw_circle(270,570,30,blanco,4);

    al_draw_text (menuFuente, blanco,130, 100, 0, "MEOWSTELLAR");//título
    al_draw_text (menuFuente2, blanco, 350, 250, 0, "Jugar");
    //al_draw_text (menuFuente2, blanco, 350, 350, 0, "Nueva Partida");
    al_draw_text (menuFuente2, blanco, 350, 450, 0, "Ajustes");
    //al_draw_text (menuFuente2, blanco, 350, 550, 0, "Logros");
    al_flip_display();
    return;
}
int inicializar()//inicializar
{
    if (!al_init()) //si no se inicia allegro
    {
        printf("No se pudo inicializar Allegro\n");
        fin = 1;
    }

    if (!al_init_image_addon()) //iniciar imagénes
    {
        printf("No se pudieron iniciar las imágenes\n");
        fin = 1;
    }

    if (!al_install_keyboard()) //iniciar teclado
    {
        printf("No se pudo inicializar el teclado\n");
        fin = 1;
    }

    if(!al_init_primitives_addon()) //si no se inician los primitivos
    {
        printf("No se pudieron cargar los primitivos");
        fin=1;
    }
    if(!al_init_font_addon())  //iniciar fuentes
    {
        printf("No se cargaron las fuentes");
        fin=1;
    }
    if(!al_init_ttf_addon())   //iniciar ttfurn;
    {
        printf("No se pudo cargar el ttf");
        fin=1;
    }
    return fin; //si no se inicializa, devuelve 1
}
typedef struct //-->parte del de caminata de gato
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
int capitulo0()
{
    // Declaración de variables de Allegro y del juego
    ALLEGRO_BITMAP *fonndosinchispa;
    ALLEGRO_BITMAP *foncch; 
    ALLEGRO_BITMAP *cable; 
    ALLEGRO_BITMAP *cola;
    ALLEGRO_BITMAP *fondocab;
    ALLEGRO_BITMAP *fondochis;
    ALLEGRO_BITMAP *fondolib;
    ALLEGRO_BITMAP *inscolor;
    ALLEGRO_BITMAP *inscor;
    ALLEGRO_BITMAP *insmov;
    ALLEGRO_BITMAP *carnaran;
    ALLEGRO_TIMER* enchispa;
    ALLEGRO_TIMER* deschispa;
    ALLEGRO_TIMER* mueve;
    ALLEGRO_TIMER* tempat;
    ALLEGRO_COLOR colfon;

    srand(time(NULL)); // Inicializa la semilla aleatoria

    // Variables de estado del juego
    int chis=0, barra=0, limit=0,vic=0,ins=1,segp=0,anim=1,xanim=950,actual = 0, orienta = 0, camina = 0,mizq = 0, patinit=0;
    int x, y, xfon=1000, xcol=700, ycol=600,n1=225,n2=265,n3=185,x1,x2;
    al_register_event_source(eventos, al_get_display_event_source(disp));
    al_register_event_source(eventos, al_get_keyboard_event_source());
    enchispa = al_create_timer(1.5);
    deschispa = al_create_timer(1.0);
    mueve = al_create_timer(0.003);
    tempat = al_create_timer(20.0);
    al_register_event_source(eventos, al_get_timer_event_source(enchispa));
    al_register_event_source(eventos, al_get_timer_event_source(deschispa));
    al_register_event_source(eventos, al_get_timer_event_source(mueve));
    al_register_event_source(eventos, al_get_timer_event_source(tempocar));
    al_register_event_source(eventos, al_get_timer_event_source(tempat));
    al_start_timer(enchispa);
    al_start_timer(deschispa);
    al_start_timer(mueve);

    // Cargar imágenes
    fonndosinchispa=al_load_bitmap("fondo.png");
    foncch=al_load_bitmap("chispa.png");
    cable=al_load_bitmap("cable.png");
    cola=al_load_bitmap("colita.png");
    fondocab=al_load_bitmap("fondocab.jpeg");
    fondochis=al_load_bitmap("fondochis.jpeg");
    fondolib=al_load_bitmap("fondolib.jpeg");
    insmov=al_load_bitmap("1.png");
    inscor=al_load_bitmap("2.png");
    carnaran=al_load_bitmap("carnaran.png");
    int finnivel=0;
    // Verifica que las imágenes se hayan cargado correctamente
    if(!fonndosinchispa||!foncch||!carnaran)
    {
        printf("No se carg%c la imagen", 162);
        fin=1;
    }
    // Inicializa posiciones aleatorias para algunos elementos
    x=rand()%3000-950;
    y=rand()%650;
    x1=rand()%233+225;
    x2=rand()%250+475;
    // Bucle principal del juego
    while(fin==0 && finnivel==0)
    { 
        int necesita_redibujar = 1;
        // Lógica para limitar el movimiento de la barra
        if(n1>724)
            limit=1;
        if(n1<226)
            limit=0;
        if(necesita_redibujar==1)
        {
            // Dibuja el fondo y los elementos principales
            al_draw_bitmap_region(fonndosinchispa,xfon,0,1000,700,0,0,0);
            al_draw_scaled_bitmap(cable,115,94,100,280,x,y,60,60,0);
            al_draw_scaled_bitmap(cola,377,0,132,700,xcol,ycol,132,700,0);
            if(chis==1)
                al_draw_scaled_bitmap(foncch,220,120,400,400,x-15,y+20,40,40,0);
            if(ins==1)
                al_draw_scaled_bitmap(insmov,0,0,LARGO,ALTO,0,0,LARGO,ALTO,0);
            if(ins==2)
                al_draw_scaled_bitmap(inscor,0,0,LARGO,ALTO,0,0,LARGO,ALTO,0);
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
            {
                segp=1;
                if(segp==1)
                {
                    al_draw_scaled_bitmap(fonndosinchispa,2000,0,1000,700,0,0,1000,700,0);
                    if(anim==1 || anim==2) 
                    {
                        cuadros f = coordenadas[orienta][actual];
                        float escala = 2.0; // Ajusta esto si quieres hacerlo más grande/pequeño
                        al_draw_scaled_bitmap(carnaran, f.sx, f.sy, f.sw, f.sh, xanim, 300, f.sw * escala, f.sh * escala, 0);
                    }
                }
            }
            al_flip_display();// Muestra en pantalla lo dibujado
            necesita_redibujar = 0;
        }
        al_wait_for_event(eventos, &evento); // Espera un evento
        // Manejo de eventos
        switch(evento.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;
            case ALLEGRO_EVENT_TIMER:
                // Manejo de temporizadores para animaciones y lógica de juego
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
                if(evento.timer.source == tempocar) 
                {
                    if(camina && mizq) 
                    {
                        orienta = movizqu;
                        actual = (actual + 1) % 3;
                    }
                }
                necesita_redibujar = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                necesita_redibujar = 1;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                mizq = 0;
                camina = 0;
                actual = 0;
                if(segp==1)
                    anim=1;
                necesita_redibujar = 1;
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                printf("\nTecla Allegro: %i", evento.keyboard.keycode);//tecla que presionaste
                if(evento.keyboard.keycode==82)
                {
                    mizq = 1;
                    camina = 1;
                    if(xanim>=287&&xanim<=320)
                        finnivel=1;
                    if(segp==1)
                    {
                        xanim-=15;
                        anim=2;
                    }
                    if(xfon>=0)
                    {
                        xfon-=24;
                        x+=24;
                        xcol+=24;
                    }
                }
                if(evento.keyboard.keycode==83)
                {
                    if(xfon<=2000)
                    {
                        xfon+=24;
                        x-=24;
                        xcol-=24;
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
                        ycol+=24;     
                }
                if(evento.keyboard.keycode==1)
                {
                    if(xcol>=-1000)
                        xcol-=24;     
                }
                if(evento.keyboard.keycode==4)
                {
                    if(xcol<=2000)
                        xcol+=24;     
                }
                if(evento.keyboard.keycode==13)
                {
                    if(ins==1)
                        ins=2;
                    else if(ins==2)
                        ins=3;
                }
                if(evento.keyboard.keycode==67)
                {
                    if(barra==1)
                    { 
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
                    if(xcol>=x&&xcol<=x+60&&ycol>=y&&ycol<=y+60)
                        barra=1;
                }
                necesita_redibujar = 1;
                break;
            
        }
    }
    // Libera recursos y termina el programa;
    al_destroy_bitmap(fonndosinchispa);
    al_destroy_bitmap(foncch);
    al_destroy_bitmap(cable);
    al_destroy_bitmap(cola);
    al_destroy_bitmap(carnaran);
    al_destroy_timer(enchispa);
    al_destroy_timer(deschispa);
    al_destroy_timer(mueve);
    al_destroy_timer(tempat);
    al_flush_event_queue(eventos);
    return capitulo_actual=1;
}
int laberinto[FILAS][COLUMNAS] = //son los laberintos que se van a usar representados como matrices
{ // 1 = pared, 0 = espacio vacío
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int laberinto2[FILAS][COLUMNAS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int laberinto3[FILAS][COLUMNAS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
// Función para dibujar el laberinto
void dibujar_laberinto(int laberinto[FILAS][COLUMNAS]) 
{
    for (int i = 0; i < FILAS; i++) 
    {
        for (int j = 0; j < COLUMNAS; j++) 
        {
            if (laberinto[i][j] == 1) 
            {
                al_draw_filled_rectangle(j * TAM_CELDA_LARGO, i * TAM_CELDA_ALTO, (j + 1) * TAM_CELDA_LARGO, (i + 1) * TAM_CELDA_ALTO, al_map_rgb(0, 20, 30));
            }
        }
    }
}
// Verificar colisión con las paredes del laberinto
int colision(int x, int y, int ancho, int alto, int laberinto[FILAS][COLUMNAS]) 
{
    // Verificar las cuatro esquinas del personaje
    int fila1 = y / TAM_CELDA_ALTO;
    int columna1 = x / TAM_CELDA_LARGO;

    int fila2 = (y + alto - 1) / TAM_CELDA_ALTO;
    int columna2 = (x + ancho - 1) / TAM_CELDA_LARGO;

    // Verificar si alguna esquina está fuera de los límites del laberinto
    if (fila1 < 0 || fila2 >= FILAS || columna1 < 0 || columna2 >= COLUMNAS) 
    {
        return 1; // Fuera de los límites
    }

    // Verificar si alguna esquina está en una pared
    if (laberinto[fila1][columna1] == 1 || laberinto[fila1][columna2] == 1 ||laberinto[fila2][columna1] == 1 || laberinto[fila2][columna2] == 1) 
    {
        return 1; // Colisión con una pared
    }

    return 0; // No hay colisión
}
void neblina(int x, int y, ALLEGRO_COLOR colorneblina)
{
    int al= 0;
    for (int i = -50; i < 10000; i++) 
    {
        colorneblina = al_map_rgba(0, 0, 0, al);
        al_draw_circle(x, y, i, colorneblina, 1);
        if (al < 255) 
        {
            al += 1; // Incrementa la opacidad
        }
    }
    return ;
}
int gganaste(int *ganaste_puerta, int x, int y, int nivel_actual)//esquina superior izquierda de la puerta (876,478)
{
    if(x>=872 && x<=928 && y>=478 && y<=552)// esquina inferior derecha de la puerta (928, 552), el limite para la puerta entre (872, 478) y (928, 552) es de 56x74 píxeles
    {    
        *ganaste_puerta=1;
        printf("Ganaste\n");
    }
    return *ganaste_puerta;
}
void dibujanivel(int otravez, ALLEGRO_BITMAP *gato, ALLEGRO_BITMAP *puerta, int x, int y, float escala, cuadros f, ALLEGRO_BITMAP *piso, ALLEGRO_COLOR colorneblina, int laberinto[FILAS][COLUMNAS])
{
    otravez = 0;
    al_draw_scaled_bitmap(piso, 0, 0, 1000, 700, 0, 0, LARGO, ALTO, 0); // Dibuja el fondo
    al_draw_filled_rectangle(0, 0, LARGO, ALTO, al_map_rgba(0,0,0,80)); // Limpiar pantalla
    dibujar_laberinto(laberinto);
    al_draw_scaled_bitmap(puerta, 0, 0, 1024, 1024, 872, 478, 1024*.07, 1024*.07, 0);
    al_draw_scaled_bitmap(gato, f.sx, f.sy, f.sw, f.sh, x, y, f.sw * escala, f.sh * escala, 0);
    neblina(x, y, colorneblina);
    printf("x: %d, y: %d\n", x, y);
    al_flip_display();
}
void mostrar_next_round(int otravez, ALLEGRO_BITMAP *gato, ALLEGRO_BITMAP *puerta, int x, int y, float escala, cuadros f, ALLEGRO_COLOR color, ALLEGRO_BITMAP *piso, ALLEGRO_COLOR colorneblina, int laberinto[FILAS][COLUMNAS])
 {
    for (int alpha = 0; alpha <= 255; alpha += 5) 
    { // Incrementa la opacidad de 0 a 255
        dibujanivel(otravez, gato, puerta, x, y, escala, f, piso, colorneblina, laberinto);
        ALLEGRO_COLOR color = al_map_rgba(0, 0, 0, alpha); // Color blanco con opacidad variable
        al_draw_filled_rectangle(0, 0, LARGO, ALTO, color); // Dibuja un rectángulo blanco con opacidad variable
        al_flip_display(); // Actualiza la pantalla
        al_rest(0.02); // Pausa para controlar la velocidad del efecto
    }
    return ;
}
// funciones y declaraciones para el nivel undertale:
ALLEGRO_BITMAP *conejo;
int conejoFrame=0;
int conejoX = 735, conejoY = 261;
int conejoDestinoY = 427;
int conejoAnimando=0; //falso
typedef struct
{
    int sx, sy, sw, sh;
}CuadroConejo;
CuadroConejo conejoCuadros[4] = 
{
    {111, 110, 225, 363},   // 336-111 = 225 | 473-110 = 363
    {357, 110, 241, 363},   // 598-357 = 241
    {623, 110, 263, 363},   // 886-623 = 263
    {895, 110, 245, 363}    // 1140-895 = 245
};
typedef struct 
{
    int Rx1, Ry1, Rx2, Ry2;
} Rectangulo; //-->para la placa del piso
Rectangulo placas[4] = //coordenadas de las placas
{
    {184, 438, 275, 506}, // Morada
    {308, 373, 401, 442}, // Amarilla
    {436, 373, 530, 442}, // Roja
    {559, 438, 652, 506}  // Blanca
};
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
            o->y = rand() % ALTO; //lugar
            o->dx = 2 + rand() % 3; //velocidad
            o->dy = (rand() % 3) - 1; //a dónde va?
            break;
        case 1:
            o->x = LARGO; //Desde la derecha
            o->y = rand() % ALTO; //lug
            o->dx = - (2 + rand() % 3); //vel
            o->dy = (rand() % 3) - 1; //a donde
            break;
        case 2:
            o->x = rand() % LARGO; //Arriba
            o->y = 0;
            o->dy = 2 + rand() % 3;
            o->dx = (rand() % 3) - 1;
            break;
        case 3:
            o->x = rand() % LARGO; //Abajo
            o->y = ALTO;
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
        if (obstaculos[i].x>=0 && obstaculos[i].x<=LARGO && obstaculos[i].y >= 0 && obstaculos[i].y <= ALTO)
            return 0; // 
    }
    return 1; // Obstaculos afuera
}
int DesafConejo()
{
    ALLEGRO_DISPLAY *pantjueg;
    ALLEGRO_EVENT_QUEUE* eventos;
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP *estam;
    ALLEGRO_TIMER *tiempo;
    ALLEGRO_KEYBOARD_STATE tecla;
    ALLEGRO_BITMAP *bestam;
    
    int fin=0;
    //registar
    pantjueg=al_create_display(LARGO,ALTO);

    bestam=al_load_bitmap("estambreazul.png");
    if (!bestam) 
    {
        printf("No se pudo cargar la imagen del jugador.\n");
        fin=1;
    }


    al_set_window_title (pantjueg, "Meowstellar");//nombre de la ventana
    tiempo=al_create_timer(1.0 / 60);
    
    eventos = al_create_event_queue(); //eventos->crear cola de eventos
    al_register_event_source(eventos, al_get_timer_event_source(tiempo));
    al_register_event_source(eventos, al_get_display_event_source(pantjueg)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos,al_get_keyboard_event_source());

    srand(time(NULL)); //semilla de lo aleatorio
    

    Estambre estambre= { LARGO / 2, ALTO / 2, 4 };
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
                if(al_key_down(&tecla, 84) && estambre.y-tamest>0)
                {
                    estambre.y -= estambre.vel;
                }
                if (al_key_down(&tecla, 85) && estambre.y+tamest<ALTO)
                {
                    estambre.y += estambre.vel;
                }
                if (al_key_down(&tecla, 82) && estambre.x-tamest>0)
                {
                    estambre.x -= estambre.vel;
                }
                if (al_key_down(&tecla, 83) && estambre.x+tamest<LARGO)
                {
                    estambre.x += estambre.vel;
                }
            }
            // 15 segundos
            if (!ganaste && al_get_time()-cuenta>= 25.0) 
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
                        if (obstaculos[i].x < 0 || obstaculos[i].x > LARGO ||obstaculos[i].y < 0 || obstaculos[i].y > ALTO) 
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
    al_destroy_display(pantjueg);
    al_destroy_timer(tiempo);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(bestam);
    return ganaste;
}int nivel_laberintos()
{
    ALLEGRO_COLOR color;
    ALLEGRO_BITMAP *puerta, *piso;
    ALLEGRO_COLOR colorneblina;
    int ganaste_puerta=0, nivel_actual=1;
    int x=56, y=578, actual = 0, camina = 0, orienta = movabaj, otravez = 0, a; // Inicializar variables
    float escala = 0.185;
    int (*laberinto_actual)[COLUMNAS] = laberinto;
    gato=al_load_bitmap("carnaran.png");
    puerta=al_load_bitmap("puerta.png");
    piso=al_load_bitmap("piso.png");
    if(!puerta)
    {
        printf("No se carg%c la imagen", 163);
        fin=1;
    }
    if(!gato)
    {
        printf("No se carg%c la imagen", 163);
        fin=1;
    }
    if(!piso)
    {
        printf("No se carg%c la imagen", 163);
        fin=1;
    }
    while(fin==0)
    {
        cuadros f = coordenadas[orienta][actual]; // Inicializar f con el cuadro actual
        al_wait_for_event(eventos, &evento);
        switch (evento.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;

            case ALLEGRO_EVENT_TIMER:
                if (camina)
                    actual = (actual + 1) % 3;
                else
                    actual = 0;

                otravez = 1;
                break;

            case ALLEGRO_EVENT_KEY_CHAR:
                camina = 1;
                if (evento.keyboard.keycode == 83) 
                { // Derecha
                    orienta = movder;
                    if (!colision(x + 4, y, f.sw * escala, f.sh * escala, laberinto_actual)&&(!gganaste(&ganaste_puerta, x, y, nivel_actual))) // Verifica colisión
                        x += 4;
                }
                if (evento.keyboard.keycode == 82) 
                { // Izquierda
                    orienta = movizqu;
                    if ((!colision(x - 4, y, f.sw * escala, f.sh * escala, laberinto_actual))&&(!gganaste(&ganaste_puerta, x, y, nivel_actual))) // Verifica colisión
                        x -= 4;
                }
                if (evento.keyboard.keycode == 84)
                { // Arriba
                    orienta = movarrib;
                    if (!colision(x, y - 4, f.sw * escala, f.sh * escala, laberinto_actual)&&(!gganaste(&ganaste_puerta, x, y, nivel_actual))) // Verifica colisión
                        y -= 4;
                }
                if (evento.keyboard.keycode == 85) 
                { // Abajo
                    orienta = movabaj;
                    if (!colision(x, y + 4, f.sw * escala, f.sh * escala, laberinto_actual)&&(!gganaste(&ganaste_puerta, x, y, nivel_actual))) // Verifica colisión
                        y += 4;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                camina = 0;
                break;
        }
        if (otravez && al_is_event_queue_empty(eventos)) 
        {
            if (nivel_actual==1)
            {
                if(ganaste_puerta==1)
                {
                    mostrar_next_round(otravez, gato, puerta, x, y, escala, f, color, piso, colorneblina, laberinto_actual);
                    nivel_actual=2;
                    laberinto_actual = laberinto2;
                    ganaste_puerta=0;
                    x=56;
                    y=578;
                }
                else
                {
                    dibujanivel(otravez, gato, puerta, x, y, escala, f, piso, colorneblina, laberinto_actual);
                }
            }
            if (nivel_actual==2)
            {
                if(ganaste_puerta==1)
                {
                    mostrar_next_round(otravez, gato, puerta, x, y, escala, f, color, piso, colorneblina, laberinto_actual);
                    laberinto_actual = laberinto3;
                    ganaste_puerta=0;
                    nivel_actual=3;
                    x=56;
                    y=578;
                }
                else
                {
                    dibujanivel(otravez, gato, puerta, x, y, escala, f, piso, colorneblina, laberinto_actual);
                }
            }
            if (nivel_actual==3)
            {
                if(ganaste_puerta==1)
                {
                    mostrar_next_round(otravez, gato, puerta, x, y, escala, f, color, piso, colorneblina,laberinto_actual);
                    ganaste_puerta=0;
                    fin=1;
                }
                else
                {
                    dibujanivel(otravez, gato, puerta, x, y, escala, f, piso, colorneblina,laberinto_actual);
                }
            }
        }
    }
    al_destroy_bitmap(gato);
    al_destroy_bitmap(puerta);
    al_destroy_bitmap(piso);
    al_flush_event_queue(eventos);
    return capitulo_actual=2;
}
int capitulo2()
{
    //DECLARACIÓN DE VARIABLES 
    int mdere=0, mizq=0, marrib= 0, mabaj=0;
    int actual=0, orienta=movabaj, x=161, y=403, camina=0;
    //botón 
    int boton=1,botonX=610,botonY=220,botonX2=49,botonY2=72;
    tempocar=al_create_timer(0.08);
    tiempoplaca=al_create_timer(6.0); // 8s para colocarse en placa
    tiempTexto=al_create_timer(3.50); //Tiempo en antalla para el texto ¨Desafío iniciado"
    al_start_timer(tempocar);
    al_start_timer(tiempoplaca);
    al_start_timer(tiempTexto);
    al_register_event_source(eventos, al_get_timer_event_source(tempocar)); 
    al_register_event_source(eventos, al_get_timer_event_source(tiempTexto)); 
    al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos,al_get_keyboard_event_source());
    al_register_event_source(eventos, al_get_timer_event_source(tiempoplaca));
    //Rutas o nombre de archivo
    gato = al_load_bitmap("carnaran.png");
    fondo = al_load_bitmap("fninicial.png");
    fondo2 = al_load_bitmap("fnfinal.png");
    luzBlanca = al_load_bitmap("luzblanca.png");
    luzRoja = al_load_bitmap("luzroja.png");
    luzMorada = al_load_bitmap("luzmorada.png");
    luzAmarilla = al_load_bitmap("luzamarilla.png");
    fuente=al_load_font("PixelDraft.ttf",30, 0);
    fuente2=al_load_font("PixelDraft.ttf",20, 0);
    conejo=al_load_bitmap("enemconejo.png");
    if(!luzBlanca||!luzRoja||!luzMorada||!luzAmarilla) //comprobar si se cargaron las imágenes de las luces
    {
        printf("No se cargaron las luces");
        fin=1;
    }
    if(!gato||!fondo||!conejo) //comprobar si se cargaron las imágenes del fondo y el gato ->también conejo
    {
        printf("No se carg%c alguna imagen", 163);
        fin=1;
    }
    while(fin!=1) 
    {
        al_wait_for_event(eventos, &evento);
        switch (evento.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: //si se cierra la ventana se cierra el programa
                fin=1;
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
                    case 67: //Tecla enter, con este es para detectar si presiona el botón que inicia el desafió
                    {
                        cuadros f = coordenadas[orienta][actual];
                        float escala = 0.7;
                        int gatoX2 = f.sw * escala;
                        int gatoY2 = f.sh * escala;
                        // Centro del gato
                        int centroX = x + gatoX2 / 2;
                        int centroY = y + gatoY2 / 2;
                        if ((x+gatoX2>botonX) && (x<botonX+botonX2) && (y+gatoY2>botonY) && (y<botonY+botonY2) && (!desafioActivo)) 
                        {
                            // Iniciar desafío
                            desafioActivo = 1;
                            rondaActual = 0;
                            luzencendida = rand() % 4;
                            al_start_timer(tiempoplaca); // Comenzar primera ronda
                            mostrarTextoInicio = 1;
                            al_start_timer(tiempTexto);
                        }

                        if (esperandoTecla && evento.keyboard.keycode == ALLEGRO_KEY_ENTER) 
                        {
                            mostrarDialogoConejo = 0;
                            esperandoTecla = 0;
                        
                            int resultado = 0;
                            while (!resultado) {
                                resultado = DesafConejo(); // Si pierde, vuelve a intentar
                            }
                            desafio2Activo = 0; // Ya pasó el desafío
                        }

                        break;
                    }
                        
                }
                if (esperandoTecla && evento.keyboard.keycode == ALLEGRO_KEY_ENTER && conejoListo) 
                {
                    mostrarDialogoConejo = 0;
                    esperandoTecla = 0;
                    conejoListo = 0;

                    int resultado = 0;

                    while (!resultado) 
                    {
                        resultado = DesafConejo(); // Repite hasta que lo gane
                    }
                    desafio2Activo = 0;
                }

                break;     
            
            case ALLEGRO_EVENT_KEY_UP:
                if (evento.keyboard.keycode == 83) 
                    mdere=0;
                if (evento.keyboard.keycode == 82) 
                    mizq=0;
                if (evento.keyboard.keycode == 84) 
                    marrib=0;
                if (evento.keyboard.keycode == 85) 
                    mabaj=0;
                camina = 0;
                break;

            case ALLEGRO_EVENT_TIMER:
                if (evento.timer.source == tempocar)  //para caminar
                {
                    // Movimiento
                    camina = mdere || mizq || marrib || mabaj;
                    if(mdere) 
                    { 
                        if(descompleto)
                        {                           
                            if((x+8<1000) && ((y-8>350)&&(y+8<450)))//normal, para arriba y abajo
                            {
                                x+=8; 
                                orienta=movder; 
                            }
                        }
                        else
                        {
                            if((x+8<1000) && (x+8<812))
                            {
                                x+=8; 
                                orienta=movder; 
                            }
                        }
                    }
                    if(mizq)  
                    { 
                        if((x-8>0) && (x-8>125))
                        {
                            x-=8; 
                            orienta=movizqu; 
                        }
                    }
                    if(marrib)
                    { 
                        if(descompleto)
                        {
                            if((y-8>0)&&(y-8>350))
                            {
                                y-=8; 
                                orienta=movarrib;
                            }
                        }
                        else
                        {
                            if((y-8>0) && (y-8>260))
                            {
                                y-=8; 
                                orienta=movarrib;
                            }
                        }
                         
                    }
                    if(mabaj) 
                    { 
                        if(descompleto)
                        {
                            if((y+8<630) && (y+8<450))
                            {
                                y+=8; 
                                orienta=movabaj; 
                            }
                        }
                        else
                        {
                            if((y+8<630) && (y+8<500))
                            {
                                y+=8; 
                                orienta=movabaj; 
                            }
                        }
                        
                    }
                    if(camina)
                        actual=(actual+1)%3;
                    else
                        actual = 0;
                }
                else if (evento.timer.source == tiempoplaca && desafioActivo)
                {
                    cuadros f = coordenadas[orienta][actual];
                    float escala = 0.7;
                    int gatoX2 = f.sw * escala;
                    int gatoY2 = f.sh * escala;
                    int centroX = x + gatoX2 / 2;
                    int centroY = y + gatoY2 / 2;

                    Rectangulo p = placas[luzencendida];

                    if ((centroX>=p.Rx1) && (centroX<=p.Rx2) && (centroY>=p.Ry1) && (centroY<=p.Ry2)) 
                    {
                        //sprintf(mensajeRonda,sizeof(mensajeRonda), "Bien: Ronda %d ", rondaActual + 1);
                        mostrarTextoInicio=1;
                        al_start_timer(tiempTexto);
                    } 
                    else 
                    {
                        //sprintf(mensajeRonda,sizeof(mensajeRonda), "Mal. Vuelve a intentarlo");
                        mostrarTextoInicio=1;
                        al_start_timer(tiempTexto);

                        desafioActivo = 0;
                        luzencendida = -1;
                        al_stop_timer(tiempoplaca);

                        printf("Vuelve a intentarlo\n");
                    }

                    rondaActual++;

                    if (rondaActual >= totalRondas) 
                    {
                        snprintf(mensajeRonda, sizeof(mensajeRonda), "¡Desafío completado!");
                        mostrarTextoInicio = 1;
                        al_start_timer(tiempTexto);

                        desafioActivo = 0;
                        luzencendida = -1;
                        al_stop_timer(tiempoplaca);

                        descompleto=1;

                        conejoAnimando = 1;
                        conejoX = 735;
                        conejoY = 261; // <- posición inicial 
                        conejoFrame = 0;

                        mostrarDialogoConejo = 1;
                        esperandoTecla = 1; // <- espera que presione ENTER para iniciar el desafío
                    }
                    else 
                    {
                        luzencendida = rand() % 4;
                        snprintf(mensajeRonda, sizeof(mensajeRonda), "Ronda: %d", rondaActual + 1);
                        mostrarTextoInicio = 1;
                        al_start_timer(tiempTexto);
                    }
                }
                cuadros f = coordenadas[orienta][actual];
                float escala = 0.7;
                int gatoX2 = f.sw * escala;
                int gatoY2 = f.sh * escala;
                if(descompleto)
                {
                    al_draw_scaled_bitmap(fondo2, 0, 0, 1000, 700, 0, 0, 1000, 700, 0);
                }
                else
                {
                    al_draw_scaled_bitmap(fondo, 0, 0, 1000, 700, 0, 0, 1000, 700, 0);
                }
                al_draw_rectangle(610,221,658,291,blanco,3);
                al_draw_scaled_bitmap(gato, f.sx, f.sy, f.sw, f.sh, x, y, gatoX2, gatoY2, 0);
                // Dibuja texto si está sobre el botón
                if((x+gatoX2>botonX) && (x<botonX+botonX2) && (y+gatoY2>botonY) && (y <botonY+botonY2))
                {
                    al_draw_filled_rectangle(120,500,880,656,al_map_rgb(0,0,0));
                    al_draw_rectangle(120,500,880,656,al_map_rgb(255,255,255),3); 
                    al_draw_text(fuente, blanco, 140, 545, 0, "-> ¿Deseas comenzar con el desafío?");
                    al_draw_text(fuente2, blanco, 140, 575, 0, " //Presiona ENTER para confirmar");
                }
                else if (evento.timer.source == tiempTexto)
                {
                    mostrarTextoInicio = 0;
                    al_stop_timer(tiempTexto);
                }                                    
                // Dibuja la luz encendida
                if ((luzencendida!=-1) && (desafioActivo))
                {
                    if (mostrarTextoInicio)
                    {
                        al_draw_text(fuente, blanco, 160, 600, 0, "En ronda");
                    }
                    ALLEGRO_BITMAP* luz = NULL;
                    if (luzencendida == 0) luz = luzMorada;
                    if (luzencendida == 1) luz = luzAmarilla;
                    if (luzencendida == 2) luz = luzRoja;
                    if (luzencendida == 3) luz = luzBlanca;
                    al_draw_scaled_bitmap(luz, 0, 0, 1000, 700, 0, 0, 1000, 700, 0);
                }
                if (mostrarTextoInicio)
                {
                    al_draw_filled_rectangle(100, 630, 900, 670, al_map_rgb(0,0,0));
                    al_draw_text(fuente2, blanco, 160, 640, 0, mensajeRonda);
                }
                if (conejoAnimando) 
                {
                    conejoY += 3;
                    if (++conejoFrame >= 4) conejoFrame = 0;

                    if (conejoY >= conejoDestinoY) 
                    {
                        conejoAnimando = 0;
                        mostrarDialogoConejo = 1;
                        esperandoTecla = 1;
                        conejoListo = 1; //listo
                    }
                }
                if (conejoAnimando || desafio2Activo) 
                {
                    CuadroConejo c = conejoCuadros[conejoFrame];
                    al_draw_scaled_bitmap(conejo, c.sx, c.sy, c.sw, c.sh, conejoX, conejoY, 64, 64, 0);
                }
                if (mostrarDialogoConejo)
                {
                    al_draw_filled_rectangle(100, 500, 900, 640, al_map_rgb(0, 0, 0));
                    al_draw_rectangle(100, 500, 900, 640, blanco, 3);
                    al_draw_text(fuente, blanco, 120, 530, 0, "ENEMIGO: ¡¡Antes de irte deberás completar mi desafío!!");
                    al_draw_text(fuente2, blanco, 120, 570, 0, "// Presiona ENTER para continuar");
                    al_draw_text(fuente2, blanco, 120, 610, 0, "(El desafío se repetirá hasta que lo completes)");
                }
            al_flip_display();
            break;         
        }
        
    }
    al_destroy_bitmap(gato);
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(luzBlanca);
    al_destroy_bitmap(luzRoja);
    al_destroy_bitmap(luzMorada);
    al_destroy_bitmap(luzAmarilla);
    al_destroy_bitmap(conejo);
    al_destroy_font(fuente);
    al_destroy_font(fuente2);
    al_destroy_timer(tiempoplaca);
    al_destroy_timer(tiempTexto);
    al_flush_event_queue(eventos);
    return 0; // Regresa al menú principal
}
int juego()
{
    tempocar=al_create_timer(0.08);
    al_register_event_source(eventos, al_get_timer_event_source(tempocar));
    al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
    al_register_event_source(eventos,al_get_keyboard_event_source());
    al_start_timer(tempocar);
    capitulo_actual=0;
    if(fin==0)
    {
        capitulo_actual=0;
        while(capitulo_actual<3 && fin==0)
        {
            //llama a la función de cada capitulo
            if (capitulo_actual==0)
            {
                capitulo0();
            }
            if (capitulo_actual==1)
            {
                nivel_laberintos();
            }
            if (capitulo_actual==2)
            {
                capitulo2();
            }
        }
        {
            if(capitulo_actual==0)
            {
                capitulo0();
            }
            if(capitulo_actual==1)
            {
                nivel_laberintos();
            }
            if(capitulo_actual==2)
            {
                capitulo2();
            }
        }
    }
    
    return 0;
}
int main()
{
    //Declarar
    ALLEGRO_BITMAP *fondo; //para el fondo
    ALLEGRO_BITMAP *vestIcono;
    ALLEGRO_BITMAP *medalla[4];
    char numSamples=0, interruptor=1;//interruptor que cambia el menú de acuerdo a la opción que se seleccione
    char m1=0, m2=0, m3=0;//no. del lugar en el que se encuentra cada medalla
    int x=270, y=270; //coordenadas del circulo que se mueve

    inicializar();
    if (fin==0)
    {
        disp=al_create_display(1000,700); //generar display y su tamaño
        al_set_window_title (disp, "Meowstellar");//nombre de la ventana
        eventos = al_create_event_queue(); //eventos->crear cola de eventos
        al_register_event_source(eventos, al_get_display_event_source(disp)); //¿de dónde vienen los eventos?
        menuFuente= al_load_font("typopixel.ttf",  60, 0);//para la fuente
        menuFuente2= al_load_font("PixelDraft.ttf",  50, 0);
        menuFuente3=al_load_font("PixelDraft.ttf", 30, 0);
        if(evento.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                    evento.type=0;
        al_register_event_source(eventos,al_get_display_event_source(disp));
        al_register_event_source(eventos,al_get_keyboard_event_source());
        //cargar fondo
        fondo=al_load_bitmap("imagmenu.png"); //Ruta de la imagen
        vestIcono=al_load_bitmap("icon.png");
        //si no se carga el fondo
        if(!fondo||!vestIcono)
        {
            printf("No se carg%c la imagen", 162);
            fin=1;
        }
    }
    while(fin==0)
    {
        if(al_event_queue_is_empty(eventos))
        {
            if (interruptor==1)
            {
                menu1(fondo, vestIcono);
                al_draw_filled_circle(x,y,20,blanco); //cículo para seleccionar modo
                al_flip_display();//mandarlo al display
            }
            if(interruptor==2)//Si se elige jugar
            {
                juego();//llama a la función juego
                interruptor=1;//regresa al menú principal
                x=270, y=270;
            }
            if (interruptor>=3)//Si no se elige jugar
            {
                al_draw_scaled_bitmap(fondo,0,0,1000,700,0,0,1000,700,0);//Pon el fondo
                al_flip_display();
                switch (interruptor)//Cambia de acuerdo a que se eligió
                {
                    case 4://Ajustes
                        ajustes(xAj, yAj); //cículo para seleccionar modo en ajustes
                        al_flip_display();
                        break;
                }
            }
        }
        al_wait_for_event(eventos, &evento);
        switch(evento.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                printf("\nVentana cerrada");
                fin=1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (evento.keyboard.keycode == 85) 
                { // mover hacia abajo 
                    if (interruptor ==1)//En el menú principal
                    {
                        if(y+100<610 && x==270)
                            y += 100;
                        if(y+100<680 && x==880)
                            y += 100; 
                    }
                    if (interruptor==4)//En el menú Ajustes
                    {
                        if(yAj+50<620)
                        yAj += 50;
                    }
                }
                if (evento.keyboard.keycode == 84) 
                { // mover hacia arriba 
                    if (interruptor==1)//En el menú principal
                    {
                        if(y-100>250 && x==270)
                        y -= 100; 
                        if(y-100>=570 && x==880)
                            y -= 100;
                    }
                    if (interruptor==4)//En el menú Ajustes
                    {
                        if(yAj-50>200)
                            yAj -= 50;
                    }
                }
                if (evento.keyboard.keycode == 82 && interruptor==1)//mover a la izquierda
                {
                    if (interruptor==1)//En el menú principal
                    {
                        if (x==880 && y==570)
                        x=270;
                    }
                    if (interruptor==6)//En el menú vestuario
                    {
                        n-=1;
                        if (n==1)
                            n=5;
                    }
                }
                if (evento.keyboard.keycode == 83) //mover a la derecha
                {
                    if (interruptor==1)//En el menú principal
                    {
                        if (x==270 && y>=570)
                        x=880;
                    }
                    if (interruptor==6)//En el menú vestuario
                    {
                        n+=1;
                        if (n==5)
                            n=1;
                    }
                }
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                if (evento.keyboard.keycode == 67 && x==270 && y==270)//Se selecciono jugar y para poner esto se cambia el valor de variable interruptor
                    interruptor=2;
                if (evento.keyboard.keycode == 67 && x==270 && y==470)//Se selecciono ajustes y para poner esto se cambia el valor de variable interruptor
                    interruptor=4;
                if (evento.keyboard.keycode == 67 && x==270 && y==570)//Se selecciono logros y para poner esto se cambia el valor de variable interruptor
                    interruptor=5;
                if (evento.keyboard.keycode == 67 && x==880 && y==570)//Se selecciono vestuario y para poner esto se cambia el valor de variable interruptor
                    interruptor=6;
                if (evento.keyboard.keycode == 67 && x==880 && y==670)//Se selecciono tu perfil y para poner esto se cambia el valor de variable interruptor
                    interruptor=7;
                if (evento.keyboard.keycode == 26 && interruptor >=2)//Volver al menú principal
                {
                    interruptor=1;
                    x=270, y=270;
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
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(gato);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
    al_destroy_timer(tiempoplaca);
    al_destroy_timer(tiempTexto);
    al_destroy_timer(tempocar);
    return 0;
}
