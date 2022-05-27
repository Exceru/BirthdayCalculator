#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int tag;
    int monat;
    int jahr; } Geburtstag;

int alterInTagen(Geburtstag const *datum, int refJahr) {
    int alter = 0;
    int tageJahre = 0;

    // Zähle die Tage aus der Differenz der Jahre
    if(refJahr > datum->jahr) {
        tageJahre = (abs(refJahr - datum->jahr) - 1) * 365;
    } else if(refJahr < datum->jahr) {
        tageJahre = (abs(refJahr - datum->jahr)) * 365;
    }

    // Zähle die Tage der Monate
    int monatsTage = 0;

    for (int i = 1; i <= (datum->monat - 1); i++) {
        int tage;

        switch (i) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                tage = 31;
                break;
            case 2:
                tage = 28;
                break;
            default:
                tage = 30;
                break;
        }

        monatsTage += tage;
    }

    // Zähle nun die "normalen" Tage hinzu und
    // ziehe eins ab, weil es keinen nullten Tag im Jahr gibt.
    monatsTage += (datum->tag - 1);

    // Addiere oder subtrahiere die gezählten Tage je nachdem ob das RefJahr in der Vergangenheit liegt
    if(refJahr <= datum->jahr) {
        alter -= tageJahre;
        alter -= monatsTage;
    } else {
        alter += tageJahre;
        alter += 365 - monatsTage;
    }


    return alter;
}

int meinRand(int untereGrenze, int obereGrenze) {
    return rand() % (obereGrenze - untereGrenze + 1) + untereGrenze;
}

Geburtstag *zufaelligerGeburtstag(unsigned int laenge) {
    Geburtstag * array = calloc(laenge, sizeof(Geburtstag));

    srand(time(0));

    for(int i = 0; i < laenge; i++) {
        Geburtstag eintrag;
        eintrag.jahr = meinRand(1900, 2100);
        eintrag.monat = meinRand(1,12);

        int ende;

        switch (eintrag.monat) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                ende = 31;
                break;
            case 2:
                ende = 28;
                break;
            default:
                ende = 30;
                break;
        }

        eintrag.tag = meinRand(1, ende);


        array[i] = eintrag;
    }

    return array;
}

void printGeburtstag(Geburtstag const *const daten, unsigned int laenge, int refJahr) {
    for(int i = 0; i < laenge; i++) {
        if(refJahr > daten[i].jahr) {
            int tage = alterInTagen(&daten[i], refJahr);
            printf("Geboren am %02d.%02d.%d; Alter in Tagen bis zum Jahr %d: %d.\n",
                   daten[i].tag, daten[i].monat, daten[i].jahr, refJahr, tage);

        } else {
            int tage = -1 * alterInTagen(&daten[i], refJahr);

            printf("Oh nooo, es ist das Jahr %d und ich werde erst in %d Tagen am %02d.%02d.%d geboren.\n",
                   refJahr, tage, daten[i].tag, daten[i].monat, daten[i].jahr);
        }
    }
}

int vergleichGeburtstage(const void *geb1, const void *geb2) {
    int alter1 = alterInTagen(geb1, 2000);
    int alter2 = alterInTagen(geb2, 2000);

    if(alter1 < alter2) {
        return -1;
    } else if(alter1 > alter2){
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char const *argv[]) {

    int laenge;

    // Programmargumente prüfen
    if(argc != 2) {
        fprintf(stderr, "Fehlerhafte Programmargumente.");
        exit(EXIT_FAILURE);
    } else {
        if(atoi(argv[1]) < 1) {
            fprintf(stderr, "Anzahl der zu generierenden Geburtstage muss mindestens 1 betragen.");
            exit(EXIT_FAILURE);
        } else {
            laenge = atoi(argv[1]);
        }
    }

    // Referenzjahr über scanf() einlesen
    int ref;

    printf("Referenzjahr: \n");
    if(scanf("%d", &ref) != 1)  {
        fprintf(stderr, "Fehler bei der Eingabe.\n");
        exit(EXIT_FAILURE);
    }

    Geburtstag * geburtstage = zufaelligerGeburtstag(laenge);

    printGeburtstag(geburtstage, laenge, ref);

    printf("Die Geburtstage werden sortiert.....\n");
    qsort(geburtstage, laenge, sizeof(Geburtstag), vergleichGeburtstage);

    printGeburtstag(geburtstage, laenge, ref);



    return 0;
}
