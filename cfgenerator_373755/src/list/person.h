/**
 * @file person.h
 * @author LabInf
 * @date 30 Mag 15
 *
 * File contenente la definizione del tipo di dato #person e della struttura #person_struct
 *
 */

#ifndef PERSON_H_
#define PERSON_H_

/** Massimo numero di caratteri del cognome */
#define MAX_SURNAME 30

/** Massimo numero di caratteri del nome */
#define MAX_NAME 20

/** Numero di caratteri della data */
#define BIRTH_DATE_LEN 15

/** Massimo numero di caratteri del luogo di nascita */
#define MAX_BIRTH_PLACE 40

/** Numero di caratteri del codice fiscale */
#define CF_LEN 17


/**
 * Tipo di dato struttura persona.
 *
 * Questa struttura permette di memorizzare le informazioni inerenti una persona,
 * necessarie per la generazione del sui codice fiscale.
 */
typedef struct person_struct{
	char surname[MAX_SURNAME];			/**< Stringa contenente il cognome. */
	char name[MAX_NAME];				/**< Stringa contenente il nome. */
	char birth_date[BIRTH_DATE_LEN];	/**< Stringa contenente la data di nascita. */
	char birth_place[MAX_BIRTH_PLACE];	/**< Stringa contenente il luogo di nascita. */
	char sex;							/**< Carattere che indica il sesso. */
	char cf[CF_LEN];					/**< Stringa contenente il codice fiscale. */
}person;

#endif /* PERSON_H_ */
