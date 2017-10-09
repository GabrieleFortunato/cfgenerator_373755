/**
 *
 * @file cfutils.h
 * @author LabInf
 * @date 30/Mag/2015
 *
 * Interfaccia dei metodi inerenti cfutils.
 *
 *
 */

#ifndef CFUTILS_H_
#define CFUTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "list/list.h"
#include "cfgenerator.h"

/** Carattere separatore nella stringa del path (modificare a seconda del S.O.) */
#define OS_SEP '/'

/**
 * Tipo di dato puntatore a funzione per filtrare le persone presenti nella lista.
 *
 * @param[in] data puntatore a struttura #person contenente i dati anagrafici di una persona.
 * @return	valore booleano
 */
typedef bool (*filter_fn)(const person* data);


/**
 * Controlla se il sesso di una persona e' maschile.
 *
 * Data una struttura #person, legge il campo person#sex e ritorna
 * true se 'M' oppure false altrimenti.
 * Viene richiamata (da un puntatore a funzione) in #list_to_file_males_AL
 *
 * @param[in] data puntatore a struttura #person contenente i dati anagrafici di una persona.
 * @return true se maschio, false altrimenti.
 *
 * @pre puntatore a struttura #person non NULL
 *
 */
bool is_male(const person* data);


/**
 * Controlla se il sesso di una persona e' femminile.
 *
 * Data una struttura #person, legge il campo person#sex e ritorna
 * true se 'F' oppure false altrimenti.
 * Viene richiamata (da un puntatore a funzione) in #list_to_file_females_MZ
 *
 * @param[in] data puntatore a struttura #person contenente i dati anagrafici di una persona.
 * @return true se donna, false altrimenti
 *
 * @pre puntatore a struttura #person non NULL
 *
 */
bool is_female(const person* data);


/**
 * Controlla se il cognome di una persona inizia con una lettera compresa tra A-L
 *
 * Data una struttura #person, legge la prima lettera del campo person#surname e ritorna
 * true se questa è compresa tra A-L, false altrimenti.
 * Viene richiamata (da un puntatore a funzione) in #list_to_file_males_AL
 *
 * @param[in] data puntatore a struttura #person contenente i dati anagrafici di una persona.
 * @return true se il cognome inizia con una lettera compresa tra A-L, false altrimenti
 *
 * @pre puntatore a struttura #person non NULL
 *
 */
bool is_surname_AL(const person* data);


/**
 * Controlla se il cognome della persona inizia con una lettera compresa tra M-Z
 *
 * Data una struttura #person, legge la prima lettera del campo person#surname e ritorna
 * true se questa è compresa tra M-Z, false altrimenti.
 * Viene richiamata (da un puntatore a funzione) in #list_to_file_females_MZ
 *
 * @param[in] data puntatore a struttura #person contenente i dati anagrafici di una persona.
 * @return true se il cognome inizia con una lettera compresa tra M-Z, false altrimenti
 *
 * @pre puntatore a struttura #person non NULL
 */
bool is_surname_MZ(const person* data);


/**
 * Filtra le persone presenti in una lista di persone in base ad una funzione di filtraggio.
 *
 * Data una lista di nodi del tipo #node la scorre eliminando (utilizzando gli opportuni metodi di list.h)
 * i nodi che non rispettano la condizione verificata dalla funzione di filtraggio.
 * Viene richiamata nelle funzioni che filtrano le persone, ovvero #list_to_file_males_AL, #list_to_file_females_MZ,
 * istanziando opportunamente il puntatore a funzione filter
 *
 * @param[in,out] people_list puntatore a #list contenente un numero di nodi pari alle persone lette da file
 * @param[in] filter puntatore a funzione del tipo #filter_fn
 *
 * @pre puntatore a lista di persone people_list non NULL
 * @pre puntatore a funzione filter non NULL
 *
 */
void filter_people(list* people_list, filter_fn filter);


/**
 * Genera il codice fiscale delle persone presenti nella lista
 *
 * Data una lista di nodi del tipo #node contenente i dati anagrafici delle persone, la scorre e genera il codice
 * fiscale di ognuno di questi a partire dai dati anagrafici letti.
 * Per ogni persona, si serve della funzione #read_birth_place_code per leggere il codice catastale del luogo di
 * nascita di un individuo. Questo e' poi passato direttamente alla funzione #cf_generator, come richiesto nelle
 * relative specifiche, per poter generare il codice fiscale.
 * Questa funzione viene utilizzata in #people_to_file_cf, #people_to_file_cf_males_AL #people_to_file_cf_females_MZ
 *
 * @param[in,out] people_list puntatore a #list contenente un numero di nodi pari alle persone lette da file
 * @param[in] places_file puntatore a stream in lettura collegato al file dei comuni con i codici catastali
 *
 * @pre puntatore a lista di persone people_list non NULL
 * @pre puntatore a stream places_file non NULL
 *
 */
void generate_cfs(list* people_list, FILE* places_file);

/**
 * Legge il codice catastale di un comune
 *
 * Dato un puntatore allo stream in lettura places_file associato al file dei codici catastali italiani (fornito dal docente)
 * e una stringa contenente il nome del comune birth_place, scorre lo stream fino a quando il nome del comune letto non coincide
 * con il nome del comune birth_place.
 * Se la stringa indicante il comune non viene trovata il puntatore al codice catastale viene impostato a NULL (quindi l'esecuzione si
 * interrompe a causa della post-condizione).
 *
 * Questa funzione viene utilizzata in #generate_cfs al fine di fornire direttamente il codice catastale alla funzione che genera il codice fiscale
 * Per l'implementazione si consiglia di utilizzare le funzioni della libreria standard string.h come strtok(),
 * strcmq() e la strcpy(); queste fanno uso e ritornano puntatori, pertanto utilizzare adeguatamente la malloc().
 * Ricordarsi inoltre che lo stream viene letto sequenzialmente; la lettura riprende da dove è stata interrotta all'ultimo accesso.
 *
 *
 * @param[in] places_file puntatore a stream in lettura collegato al file dei comuni con i codici catastali
 * @param[in] la stringa con il nome del comune di nascita
 * @return la stringa del codice catastale del comune di nascita
 *
 * @pre puntatore a stream places_file non NULL
 * @pre birth_place stringa non vuota
 *
 * @post il puntatore alla stringa del codice catastale ritornato non NULL
 * @post il codice catastale restituito deve essere una stringa di 4 caratteri
 *
 */
char* read_birth_place_code(FILE* places_file,const char* birth_place);

/**
 * Legge i dati anagrafici di una singola persona come blocco di informazioni (il codice fiscale non e' presente)
 *
 * Dato lo stream in lettura, legge cinque righe dello stream, ovvero i dati di una singola persona, e li utilizza
 * opportunamente per avvalorare i campi della struttura #person.
 * Si ricorda l'utilizzo della malloc() al fine di riservarsi in memoria uno spazio tale da conservare la struttura
 * creata anche dopo il termine dell'esecuzione della funzione.
 * Viene utilizzata in #people_file_to_list
 *
 * @param[in] people_file puntatore a stream in lettura collegato al file con i dati anagrafici delle persone (senza codice fiscale)
 * @return puntatore ad una struttura #person con i campi opportunamente avvalorati (il campo person#cf inizializzato a "" - stringa vuota)
 *
 * @pre puntatore a people_file non NULL
 * @post il puntatore restituito non e' NULL
 */
person* read_person(FILE* people_file);

/**
 * Legge i dati anagrafici delle persone presenti nel file di input.
 *
 * Utilizzando le funzioni della libreria list.h, crea una nuova lista vuota e aggiunge un nodo alla lista per ogni persona
 * acquisita tramite #read_person, fino a raggiungere EOF dello stream in lettura people_file.
 * Restituisce un puntatore ad una lista di nodi contenenti i dai anagrafici delle persone presenti nel
 * file, oppure NULL.
 * Viene utilizzata in #people_to_file_cf, #people_to_file_cf_males_AL e #people_to_file_cf_males_AL
 *
 * @see new_list()
 * @see new_node()
 * @see add_node()
 *
 * @param[in] people_file puntatore a stream in lettura collegato al file con i dati anagrafici delle persone (senza codice fiscale)
 * @return puntatore ad una struttura #list
 *
 * @pre puntatore allo stream people_file non NULL
 * @post puntatore alla lista creata non NULL
 *
 */
list* people_file_to_list(FILE* people_file);

/**
 * Stampa su file i dati anagrafici delle persone in lista
 *
 * Dato un puntatore ad una lista di tipo #list e uno stream in scrittura, partendo dal nodo testa della lista stampa
 * sullo stream il contenuto del nodo fino a quando la lista termina.
 * In particolare, ogni campo della struttura memorizzata nel nodo viene stampato su un singolo rigo (aggiungere il carattere "/n")
 * e non sono presenti righe vuote tra un nodo ed un altro
 * (il file di output e' come quello fornito in input con in piu' il rigo contenente il cf - per ogni persona).
 * Questa funzione è utilizzata anche in #list_to_file_males_AL, #list_to_file_females_MZ #people_to_file_cf
 *
 * @see head()
 * @see next()
 * @see content()
 *
 * @param[in] people_list puntatore a #list contenente un numero di nodi pari alle persone lette da file
 * @param[in] output_file puntatore a strem in scrittura associato ad un file
 *
 * @pre puntatore a people_list non NULL
 * @pre puntatore a output_file non NULL
 */
void list_to_file(list* people_list, FILE* output_file);


/**
 * Filtra una lista preservando individui di sesso maschile con cognome compreso tra A-L
 *
 * Dato un puntatore ad una lista di tipo #list di nodi, questa funzione utilizza la funzione #filter_people (istanziando
 * opportunamente il puntatore a funzione filter del tipo #filter_fn, ed infine, utilizza la funzione #list_to_file
 * per stampare sullo stream in scrittura output_file gli elementi rimanenti della lista (dopo il filtraggio).
 * Viene utilizzata in #people_to_file_cf_males_AL
 *
 * @see is_male()
 * @see is_surname_AL()
 *
 * @param[in] people_list puntatore a #list contenente un numero di nodi pari alle persone lette da file
 * @param[in] output_file puntatore a strem in scrittura associato ad un file
 *
 *
 * @pre puntatore a people_list non NULL
 * @pre puntatore a output_file non NULL
 */
void list_to_file_males_AL(list* people_list, FILE* output_file);


/**
 * Filtra una lista preservando individui di sesso femminile con cognome compreso tra M-Z
 *
 * Dato un puntatore ad una lista di tipo #list di nodi, questa funzione utilizza la funzione #filter_people (istanziando
 * opportunamente il puntatore a funzione filter del tipo #filter_fn, ed infine, utilizza la funzione #list_to_file
 * per stampare sullo stream in scrittura output_file gli elementi rimanenti della lista (dopo il filtraggio).
 * Viene utilizzata in #people_to_file_cf_females_MZ
 *
 * @see is_female()
 * @see is_surname_MZ()
 *
 * @param[in] people_list puntatore a #list contenente un numero di nodi pari alle persone lette da file
 * @param[in] output_file puntatore a strem in scrittura associato ad un file
 *
 * @pre puntatore a people_list non NULL
 * @pre puntatore a output_file non NULL
 */
void list_to_file_females_MZ(list* people_list, FILE* output_file);


/**
 * Legge i dati anagrafici di persone da un file e li riscrive in un altro file aggiungendovi il codice fiscale
 *
 * Dato un puntatore a stream in lettura contenente i dati anagrafici di una serie di persone (senza il cf), crea una lista
 * di individui sfruttando la funzione #people_file_to_list, genera il codice fiscale di ognuno di questi utilizzando la
 * funzione #generate_cfs (la quale necessita dello stream places_file, contenente i codici catastali dei comuni) ed infine
 * stampa la lista dei dati anagrafici (compreso il codice fiscale) sullo stream in scrittura output_file utilizzando la funzione #list_to_file
 * #list_to_file
 *
 * @param[in] people_file
 * @param[in] output_file
 * @param[in] places_file
 *
 * @pre il puntatore allo stream people_file non deve essere NULL
 * @pre il puntatore allo stream output_file non deve essere NULL
 * @pre il puntatore allo stream places_file non deve essere NULL
 *
 */
void people_to_file_cf(FILE* people_file, FILE* output_file, FILE* places_file);


/**
 * Legge i dati anagrafici di persone da un file, filtra i risultati e li riscrive in un altro file aggiungendovi il codice fiscale
 *
 * Come per la funzione #people_to_file_cf ma al posto di utilizzare #list_to_file, utilizza #list_to_file_males_AL al fine di ottenere
 * in output_file i soli individui di sesso maschile con cognome compreso fra A-L
 *
 * @param[in] people_file
 * @param[in] output_file
 * @param[in] places_file
 *
 * @pre il puntatore allo stream people_file non deve essere NULL
 * @pre il puntatore allo stream output_file non deve essere NULL
 * @pre il puntatore allo stream places_file non deve essere NULL
 *
 */
void people_to_file_cf_males_AL(FILE* people_file, FILE* output_file, FILE* places_file);

/**
 * Legge i dati anagrafici di persone da un file, filtra i risultati e li riscrive in un altro file aggiungendovi il codice fiscale
 *
 * Come per la funzione #people_to_file_cf ma al posto di utilizzare #list_to_file, utilizza #list_to_file_female_MZ al fine di ottenere
 * in output_file i soli individui di sesso femminile con cognome compreso fra M-Z
 *
 * @param[in] people_file
 * @param[in] output_file
 * @param[in] places_file
 *
 * @pre il puntatore allo stream people_list non deve essere NULL
 * @pre il puntatore allo stream output_file non deve essere NULL
 * @pre il puntatore allo stream places_file non deve essere NULL
 *
 */
void people_to_file_cf_females_MZ(FILE* people_file, FILE* output_file, FILE* places_file);


/**
 * Genera il path assoluto di filename
 *
 * Dato il puntatore alla stringa contenente il path assoluto di una directory di lavoro (es Win. C:\\path\\wdir\\)
 * (es. Linux /path/wdir/) la copia (necessario perche' puntatore) e concatena alla copia la stringa filename
 * contenente il nome del file. Ritorna il filepath assoluto di filename.
 * (es Win. C:\path\wdir\file.txt) (es. Linux /path/wdir/file.txt)
 *
 * @see strlen()
 * @see malloc()
 * @see strcopy()
 * @see strcat()
 *
 * @param[in] wd_path path assoluto della directory di lavoro in cui salvare i file di output
 * @param[in] filename nome del file di output
 * @return path assoluto del filename
 *
 * @pre wd_path deve terminare con il carattere separatore (\\ per Win e / per linux) da specificare in #OS_SEP
 *
 * @post la lunghezza del path ritornato deve essere somma delle lunghezze di wd_path e filename
 *
 */
char* outfile_path(char* wd_path, char* filename);


#endif /* CFUTILS_H_ */
