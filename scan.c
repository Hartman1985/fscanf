/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>

char const* const VERSIONSNR = "0.1.3-Aplpha";
int laenge,laenge2,laenge3,laenge4,laenge5,laenge6,laenge7,laenge8,laenge9;
int const DB_SIZE = 40;

struct person
{
    int  position;
    char vorname[40];
    char nachname[40];
    char geburtsdatum[30];
    char todestag[30];
    char familienname[40];
    char beziehungsstatus[20];
    char adresse[50];
    int  kinder;
    int kindvon;

};
size_t MyStrlen( const char* string )
{
	  size_t Count = 0;

	    while( *string++ )
		        Count++;

	      return Count;
}
typedef struct person person_t;

static void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    printf("Knotennr  |Vorname                                 |Nachname                                |Geburtsdatum                            |Todestag                      |Familienname                  |Beziehungsstatus                        |Adresse                            |Anz. Kinder\t|Kind von\t | \n"); 
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
   person_t database[DB_SIZE];
    while(fscanf(filepointer,
                 "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d \n",
                 &database[zaehler].position,
                 database[zaehler].vorname,
                 database[zaehler].nachname,
                 database[zaehler].geburtsdatum,
		 database[zaehler].todestag,
		 database[zaehler].familienname,
		 database[zaehler].beziehungsstatus,
		 database[zaehler].adresse,
		 &database[zaehler].kinder,
		 &database[zaehler].kindvon)
          != EOF)
	   
    {
	laenge=MyStrlen( database[zaehler].vorname );
	laenge2=MyStrlen( database[zaehler].nachname );
	laenge3=MyStrlen( database[zaehler].geburtsdatum );
	laenge4=MyStrlen( database[zaehler].todestag );
	laenge5=MyStrlen( database[zaehler].familienname );
	laenge6=MyStrlen( database[zaehler].beziehungsstatus );
	laenge7=MyStrlen( database[zaehler].adresse );
	
	
		
        printf("|%d        |%*s|%*s|%*s|%*s|%*s|%*s|%*s|%d |%d | \n",
               database[zaehler].position,
	       40,
               database[zaehler].vorname,
	       40,
               database[zaehler].nachname,
	       40,
               database[zaehler].geburtsdatum,
	       30,
	       database[zaehler].todestag,
	       30,
               database[zaehler].familienname,
	       40,
	       database[zaehler].beziehungsstatus,
	       20,
	       database[zaehler].adresse,
	       
	       database[zaehler].kinder,
	       database[zaehler].kindvon);
	
	
        zaehler++;
	if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }


    
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}
int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
 /* GtkWidget *window;
	    GtkWidget *fixed;
	    GtkWidget *btn1;
	    GtkWidget *btn2;
	    GtkWidget *btn3;
	    gtk_init(&argc, &argv);
	    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	    gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
	    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	    fixed = gtk_fixed_new();
	    gtk_container_add(GTK_CONTAINER(window), fixed);
	    btn1 = gtk_button_new_with_label("test");
	    snprintf(buffer, sizeof(buffer), "%i",database[1].vorname);
	    gtk_button_set_label(GTK_BUTTON(btn1),buffer);

	    gtk_fixed_put(GTK_FIXED(fixed), btn1, 150, 50);
	    gtk_widget_set_size_request(btn1, 80, 30);
	    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
	    gtk_widget_show_all(window);
	    gtk_main();*/

			
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}
