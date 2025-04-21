#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>

//DECLARACIÓN DE VARIABLES ENTERAS GLOBALESS
int fin=0;
int desafioActivo=0;
int rondaActual=0;
int totalRondas=6;
int eponplaca=0; //si se pone en placa
int luzencendida=-1;  //-1=ninguna
int mostrarTextoInicio=0;

int mostrarDialogoConejo=0;
int esperandoTecla=0;
int conejoListo=0; //El conejo está en el lugar que debe


int descompleto=0; //desafío completado
int desafio2Activo=0;

char mensajeRonda[30]="";

//Variables tipo ALLEGRO
ALLEGRO_DISPLAY *disp;
ALLEGRO_EVENT_QUEUE *eventos;
ALLEGRO_EVENT evento;

ALLEGRO_BITMAP *gato;
ALLEGRO_BITMAP *fondo;
ALLEGRO_BITMAP *fondo2;
ALLEGRO_BITMAP *luzBlanca, *luzRoja,*luzMorada,*luzAmarilla;

ALLEGRO_COLOR blanco= al_map_rgb(255,255,255);
ALLEGRO_FONT *fuente, *fuente2; 

ALLEGRO_TIMER *tiempoplaca;
ALLEGRO_TIMER *tempocar;
ALLEGRO_TIMER *tiempTexto;

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

//SEGUNDA PARTE ("conejo")
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

void inicializar()//inicializar
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
}
//Para el desafío del conejo
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
    pantjueg=al_create_display(ldisp,adisp);

    bestam=al_load_bitmap("estambre.png");
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
                if(al_key_down(&tecla, 84) && estambre.y-tamest>0)
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
    al_destroy_display(pantjueg);
    al_destroy_timer(tiempo);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(bestam);

    return ganaste;
}
int main()
{
    //DECLARACIÓN DE VARIABLES 
    int mdere=0, mizq=0, marrib= 0, mabaj=0;
    int actual=0, orienta=movabaj, x=161, y=403, camina=0;

    //botón 
    int boton=1,botonX=610,botonY=220,botonX2=49,botonY2=72;

    

    inicializar(); 

    disp=al_create_display(1000,700); //generar disp
    eventos = al_create_event_queue(); //eventos->crear cola de eventos
    tempocar=al_create_timer(0.08);
    tiempoplaca=al_create_timer(6.0); // 8s para colocarse en placa
    tiempTexto=al_create_timer(3.50); //Tiempo en antalla para el texto ¨Desafío iniciado"

    al_set_window_title (disp, "Meowstellar");//nombre de la ventana
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

    al_start_timer(tempocar); //se inicia el contador del timer para la animación del gato

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

    while(!fin) 
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

                //ERAN PARA COMPROBAR LAS COORDENADAS TT
                //al_draw_rectangle(184, 438, 275, 506,al_map_rgb(255,255,255),3);//morada
                //al_draw_rectangle(308, 373, 401, 442,al_map_rgb(255,255,255),3);//amarilla
                //al_draw_rectangle(436, 373, 530, 442,al_map_rgb(255,255,255),3);//roja
                //al_draw_rectangle(559, 438, 652, 506,al_map_rgb(255,255,255),3);//blanca

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

                    if (conejoY >= conejoDestinoY) {
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
                
                if (mostrarDialogoConejo) {
                    al_draw_filled_rectangle(100, 500, 900, 640, al_map_rgb(0, 0, 0));
                    al_draw_rectangle(100, 500, 900, 640, blanco, 3);
                    al_draw_text(fuente, blanco, 120, 530, 0, "ENEMIGO: ¡¡Antes de irte deberás completar mi desafío!!");
                    al_draw_text(fuente2, blanco, 120, 570, 0, "// Presiona ENTER para continuar");
                    al_draw_text(fuente2, blanco, 120, 570, 0, "(El desafío se repetirá hasta que lo completes)");
                }
            al_flip_display();
            break;         
        }
    }
    al_destroy_display(disp);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(gato);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
    al_destroy_timer(tiempoplaca);
    al_destroy_timer(tiempTexto);
    al_destroy_timer(tempocar);
    
    return 0;    
}