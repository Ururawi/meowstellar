//Menu prueba que mueve el círculo, pone fondo al seleccionar una opción (en todas las direcciones), te aparece el título de cada sección (usando funciones),
//algunas cosas de cada una de estas
#include<stdio.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_primitives.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
#include <string.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include "iniciar.h" //Biblioteca creada que contiene el inicio del sistema
//Fuentes menú, blanco 
ALLEGRO_FONT *menuFuente; 
ALLEGRO_FONT *menuFuente2; 
ALLEGRO_FONT *menuFuente3;
ALLEGRO_COLOR blanco= al_map_rgb(255,255,255);
ALLEGRO_BITMAP *gatito;
char n=1;
int  xAj=270, yAj=265;

void nuevaPartida()
{
    al_draw_text(menuFuente, blanco,130, 100, 0, "NUEVA PARTIDA");//Título
    al_flip_display();
    return;
}

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
    al_draw_text (menuFuente3, blanco, 350, 250, 0, "Sonido");
    al_draw_text (menuFuente2, blanco, 350, 350, 0, "-------TECLAS-------");
    al_draw_text (menuFuente3, blanco, 350, 450, 0, "Arriba");
    al_draw_text (menuFuente3, blanco, 350, 500, 0, "Abajo");
    al_draw_text (menuFuente3, blanco, 350, 550, 0, "Derecha");
    al_draw_text (menuFuente3, blanco, 350, 600, 0, "Izquierda");
    al_draw_filled_circle(xAj,yAj,20,blanco);
    al_flip_display();
    return;
}

void logros(ALLEGRO_BITMAP *med1, ALLEGRO_BITMAP *med2, ALLEGRO_BITMAP *med3)
{
    al_draw_text(menuFuente, blanco,130, 100, 0, "LOGROS");//Título
    //Información de las medallas
    al_draw_text(menuFuente2, blanco,60, 470, 0, "Único");
    al_draw_text(menuFuente2, blanco,60, 520, 0, "sobreviviente");
    al_draw_text(menuFuente3, blanco,60, 570, 0, "Reparaste tu nave");
    al_draw_text(menuFuente3, blanco,60, 600, 0, "No salvaste a nadie");
    al_draw_text(menuFuente3, blanco,60, 640, 0, "Sobreviviste");
    al_draw_text(menuFuente2, blanco,390, 470, 0, "Noble");
    al_draw_text(menuFuente2, blanco,390, 520, 0, "guerrero");
    al_draw_text(menuFuente3, blanco,390, 570, 0, "Reparaste tu nave");
    al_draw_text(menuFuente3, blanco,390, 600, 0, "Salvaste a tus amigos");
    al_draw_text(menuFuente3, blanco,390, 640, 0, "No sobreviviste");
    al_draw_text(menuFuente2, blanco,700, 470, 0, "Final feliz");
    al_draw_text(menuFuente3, blanco,700, 570, 0, "Reparaste tu nave");
    al_draw_text(menuFuente3, blanco,700, 600, 0, "Salvaste a tus amigos");
    al_draw_text(menuFuente3, blanco,700, 640, 0, "Sobreviviste");
    //Imagenes de las medallas
    al_draw_scaled_bitmap(med1, 0, 0, 210, 230, 100, 200, 300, 300, 0);
    al_draw_scaled_bitmap(med2, 0, 0, 210, 230, 390, 200, 300, 300, 0);
    al_draw_scaled_bitmap(med3, 0, 0, 210, 230, 700, 200, 300, 300, 0);
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

void perfil()
{
    al_draw_text(menuFuente, blanco,130, 100, 0, "TU PERFIL");//Título
    al_draw_text (menuFuente2, blanco, 270, 270, 0, "Nombre");
    /*int xl=270;
    char nom[2]={0, '\0'}, error=1, nombrePlayer[20];//Variable const char para poder dibujar letras (solo acepta const char)
    while(error==1)//Mientras haya un error en el nombre
    {
        error=0;//Regresar error a 0 para que si no hay errores, se pueda salir del ciclo
        for (int i=0; i<20; i++)//Ciclo para recibir cada una de las letras del nombre y mandarlas a pantalla
        {
            nom[0]=getchar();//Recibir el caracter
            if (!nom[0]==67)//Si el usuario no ha presionado enter
            {
                nombrePlayer[i]=nom[0];
                if (nombrePlayer[i]==63)//Si se presiona la tecla para borrar letras
                {
                    i-=1;//Vete al anterior espacio de guardado
                    xl-=30;//Cambia la posicion horizontal de la letra
                    al_draw_text (menuFuente3, al_map_rgb (0, 0, 0), xl, 250, 0, nom);//Borra la letra
                }
                else 
                al_draw_text (menuFuente3, blanco, xl+=30, 350, 0, nom);//Si no, solo dibuja la letra
            }
            else//Si ya termino el usuario de escribir su nombre y presiono enter
            {
                i=20;//Para que el usuario salga del ciclo
            }
        }
        for (int i=0; i<strlen(nombrePlayer)-1; i++)//Ciclo para revisar si el nombre tiene letras y/o numeros
        {
            if (isdigit(nombrePlayer[i])==0 && isalpha(nombrePlayer[i]) == 0)//Si el nombre tiene otro caracter que no sean no. y letras (tampoco puede tener espacios), se marcara error
                error=1;
        }
        if (error==1)//Si se cometio algun error, mandar texto a la pantalla
            al_draw_text (menuFuente3, al_map_rgb (255, 0, 0), 200, 200, 0, "Porfavor, escribe un nombre usando solo letras y números. NO uses espacios ni otros signos especiales");
    }
    al_draw_text (menuFuente2, al_map_rgb (0, 255, 0), 270, 400, 0,"Nombre válido");//Para que sepa que su nombre es valido*/
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
    al_flip_display();
    return;
}

int main()
{
    //Declarar
    ALLEGRO_DISPLAY *disp; //para el display
    ALLEGRO_EVENT_QUEUE* eventos; //para eventos-> cola de eventos
    ALLEGRO_EVENT evento;  //evento-> evento de la cola de eventos
    ALLEGRO_BITMAP *fondo; //para el fondo
    ALLEGRO_BITMAP *vestIcono;
    ALLEGRO_BITMAP *medalla[4];
    char fin=0, numSamples=0, interruptor=1;//interruptor que cambia el menú de acuerdo a la opción que se seleccione
    char m1=0, m2=0, m3=0;//no. del lugar en el que se encuentra cada medalla
    int x=270, y=270; //coordenadas del circulo que se mueve

    fin=inicia(numSamples);//inicializar funciones y devolver fin
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
        medalla[0]= al_load_bitmap("nomedalla.jpg");
        medalla[1]= al_load_bitmap("medalla1.jpg");
        medalla[2]= al_load_bitmap("medalla2.jpg");
        medalla[3]= al_load_bitmap("medalla3.jpg");
        //si no se carga el fondo
        if(!fondo||!vestIcono || !medalla[0] || !medalla[1] || !medalla[2] || !medalla[3])
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
            if (interruptor>=3)//Si no se elige jugar
            {
                al_draw_scaled_bitmap(fondo,0,0,1000,700,0,0,1000,700,0);//Pon el fondo
                al_flip_display();
                switch (interruptor)//Cambia de acuerdo a que se eligió
                {
                    case 3://Nueva partida
                        nuevaPartida();
                        break;
                    case 4://Ajustes
                        ajustes(xAj, yAj); //cículo para seleccionar modo en ajustes
                        al_flip_display();
                        break;
                    case 5://Logros
                        logros(medalla[m1], medalla[m2], medalla[m3]);
                        break;
                    case 6://Vestuario
                        vestuario();
                        break;
                    case 7://Tu perfil
                        perfil();
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
                if (evento.keyboard.keycode == 85) { // mover hacia abajo 
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
                if (evento.keyboard.keycode == 84) { // mover hacia arriba 
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
                if (evento.keyboard.keycode == 67 && x==270 && y==370)//Se selecciono nueva partida y para poner esto se cambia el valor de variable interruptor
                    interruptor=3;
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
    
    return 0;
}