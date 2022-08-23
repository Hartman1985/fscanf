/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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
    printf("Knotennr  |Vorname                                 |Nachname                                |Geburtsdatum                            |Todestag                      |Familienname                            |Beziehungsstatus              |Adresse                                           |Anz. Kinder|Kind von| \n"); 
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
	       40,
               database[zaehler].familienname,
	       30,
	       database[zaehler].beziehungsstatus,
	       50,
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
