/**
 * @file list.h
 * @author LabInf
 * @date 13/mag/2015
 *
 * Libreria per la creazione e gestione di liste.
 *
 * La libreria mette a disposizione le funzioni per la creazione, la scansione,
 * l'aggiunta ed eliminazione di nodi, e la distruzione delle liste. Il contenuto
 * dei nodi delle liste e' specificato dal topo #list_type. Occorre modificare
 * questo tipo per avere liste del tipo specificato. La libreria NON gestisce
 * i contenuti, che sono a carico dell'utente della libreria.
 *
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include "person.h"

/**
 * Contenuto nei nodi della lista. Per default il contenuto della lista e' un
 * puntatore a carattere, utile per stringhe.
 */
typedef person* list_type;

/**
 * Una lista. Una lista e' un oggetto astratto costituito da una sequenza di nodi.
 */
typedef struct list_struct list;

/**
 * Un nodo. Un nodo contiene un contenuto e le informazioni di connessione con gli
 * altri elementi della lista cui appartiene.
 */
typedef struct node node;

/**
 * Costruisce una lista vuota. Una lista vuota ha lunghezza 0, non ha testa, ne' coda.
 * Le liste costruite devono essere distrutte con la funzione #delete. Se la funzione
 * restitusce NULL, allora la lista non puo' essere creata.
 * @return una nuova lista vuota
 */
list* new_list(void);

/**
 * Costruisce un nuovo nodo. Un nodo appena costruito non appartiene ad alcuna lista, ma
 * contiene il contenuto specificato. Esso non puo' essere utilizzato, fintantoche'
 * non viene inserito in una lista. I nodi inseriti in una lista sono distrutti dalla
 * funzione #delete_list. Per distruggere un nodo non in lista, usare la funzione
 * #delete_node. Se la funzione restituisce NULL, allora il nodo
 * non puo' essere creato.
 * @param content il contenuto del nodo
 * @return un puntatore al nodo costruito.
 */
node* new_node(list_type content);

/**
 * Restituisce il contenuto di un nodo.
 * @pre Il nodo non puo' essere NULL.
 * @param n il nodo da cui estrarre il contenuto
 * @return il contenuto estratto dal nodo.
 */
list_type content(node* n);

/**
 * Restituisce la testa della lista. La testa della lista e' il primo nodo della
 * sequenza che costituisce la lista. Se la lista e' vuota, la funzione restituisce NULL.
 * @pre l non puo' essere NULL
 * @param l la lista da cui estrarre la testa.
 * @return la testa della lista.
 */
node* head(const list* l);

/**
 * Restituisce la coda della lista. La coda della lista e' l'ultimo elemento
 * della sequenza che costituisce la lista. Se la lista e' vuota, la funzione
 * restituisce NULL.
 * @pre l non puo' essere NULL.
 * @param l la lista da cui estrarre la coda
 * @return la coda della lista.
 */
node* tail(const list* l);

/**
 * Restituisce l'elemento successivo al nodo specificato della lista. Se il nodo
 * e' in coda alla lista, restituisce NULL.
 * @pre l non puo' essere NULL
 * @pre il nodo deve appartenere alla lista.
 * @param l la lista cui appartiene il nodo.
 * @param n il nodo da cui ricavare il successore
 * @return il successore del nodo n nella lista l.
 */
node* next(const list* l, node* n);

/**
 * Restituisce l'elemento precedente al nodo specificato della lista. Se il nodo
 * e' in testa alla lista, restituisce NULL.
 * @pre l non puo' essere NULL
 * @pre il nodo deve appartenere alla lista.
 * @param l la lista cui appartiene il nodo.
 * @param n il nodo da cui ricavare il predecessore
 * @return il predecessore del nodo n nella lista l.
 */
node* prev(const list* l, node* n);

/**
 * Restituisce la lunghezza della lista. La lunghezza di una lista e' il numero
 * di nodi appartenenti alla lista.
 * @pre l non puo' essere NULL
 * @param l la lista da cui ricavare la lunghezza
 * @return la lunghezza della lista.
 */
int length(const list* l);

/**
 * Aggiunge un nodo alla lista. La procedura aggiunge un nodo nella lista dopo il
 * nodo specificato node_before. Per esempio, se la lista e' costituita dalla sequenza
 * di nodi (A,B,C) e node_before e' A, allora a seguito dell'aggiunta del nodo D la
 * lista sara' trasformata in (A,D,B,C). Se node_before e' NULL, per convenzione
 * l'inserimento del nodo avviene in testa alla lista.
 * @pre l non puo' essere NULL
 * @pre node_to_add non deve essere NULL
 * @param l la lista a cui aggiungere un nodo
 * @param node_before il nodo dopo il quale sara' aggiunto il nodo
 * @param node_to_add il nodo da aggiungere alla lista
 */
void add_node(list* l, node* node_before, node* node_to_add);

/**
 * Rimuove un nodo dalla lista. La procedura NON distrugge il nodo eliminato.
 * @pre l non deve essere NULL
 * @pre il nodo da rimuovere deve appartenere alla lista
 * @param l la lista contenente il nodo da rimuovere
 * @param node_to_remove il nodo da rimuovere.
 */
void remove_node(list* l, node* node_to_remove);

/**
 * Distrugge un nodo. Il nodo deve essere preventivamente rimosso dalla lista
 * cui apparteneva, utilizzando la funzione #remove.
 * @pre n non deve essere null
 * @param n il nodo da distruggere
 */
void delete_node(node* n);

/**
 * Distrugge la lista. La distruzione della lista comporta la distruzione
 * di tutti i nodi che la costituiscono.
 * @pre l non deve essere null
 * @param l la lista da distruggere
 */
void delete_list(list* l);

/**
 * Cerca un nodo della lista sulla base del contenuto. La funzione ricerca un
 * nodo della lista che contenga il contenuto specificato da content. La funzione
 * restituisce il primo nodo trovato con il contenuto specificato, oppure NULL
 * se nessun nodo possiede il contenuto specificato.
 * @pre l non deve essere NULL
 * @param l la lista su cui effettuare la ricerca
 * @param content il contenuto da ricercare
 * @return il nodo che contiene il contenuto ricercato oppure NULL
 */
node* lookfor(const list* l, list_type content);

#endif /* LIST_H_ */
