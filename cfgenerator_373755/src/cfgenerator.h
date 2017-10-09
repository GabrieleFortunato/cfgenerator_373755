/**
 * @file cfgenerator.h
 *
 * Interfaccia della libreria cfgenerator.
 *
 *
 */

#ifndef CFGENERATOR_000000_SRC_CFGENERATOR_H_
#define CFGENERATOR_000000_SRC_CFGENERATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define EOS '\0'

#define MIN_SURNAME_LENGTH 2
#define MIN_NAME_LENGTH 2
#define DATE_ORG_LENGTH 10
#define LETTERS 26

#define MIN_CONSONANT 3

#define CODED_SRN_LENGTH 3
#define CODED_NAME_LENGTH 3
#define CODED_DATE_LENGTH 5
#define CODED_BIRTH_PLACE_LENGTH 4

#define FEMALE_DAYS_OFFSET 40
#define DATE_DIGITS 2
#define DAY_INDEX 0
#define MONTH_INDEX 3
#define YEAR_INDEX 8

#define MIN_BIRTH_DAY 1
#define MAX_BIRTH_DAY 31
#define MIN_BIRTH_MONTH 1
#define MAX_BIRTH_MONTH 12
#define MIN_BIRTH_YEAR 1900
#define MAX_BIRTH_YEAR 2015
#define YEAR_ORG_INDEX 6
#define YEAR_ORG_LENGTH 4
#define CODED_YEAR_INDEX 0
#define CODED_MONTH_INDEX 2
#define CODED_DAY_INDEX 3

#define TEST_CF_LENGTH 16



/**
 * Codifica il cognome nel formato per codice fiscale.
 *
 * @param org_surname Nome.
 * @param coded_surname Stringa da 3 caratteri che conterra' la codifica.
 *
 * @pre surname puo' contenere solo caratteri maiuscoli, spazi, apici.
 * @pre surname deve essere formato da almeno due caratteri.
 * @pre coded_surname deve essere una stringa di 3 caratteri
 *
 * @post coded_surname deve contenere 3 lettere maiuscole.
 */
void surname2code(const char org_surname[], char coded_surname[]);

/**
 * Codifica il nome nel formato per codice fiscale.
 *
 * @param name Nome.
 * @param coded_name Stringa da 3 caratteri che conterra' la codifica.
 *
 * @pre name puo' contenere solo caratteri maiuscoli, spazi, apici.
 * @pre name deve essere formato da almeno due caratteri.
 * @pre coded_name deve essere una stringa di 3 caratteri
 *
 * @post coded_name deve contenere 3 lettere maiuscole.
 */
void name2code(const char name[], char coded_name[]);

/**
 * Codifica la data di nascita nel formato per codice fiscale.
 *
 * @param date Data di nascita nel formato GG/MM/AAAA.
 * @param sex Sesso.
 * @param coded_date Stringa di 5 caratteri che conterra' la codifica.
 *
 * @pre date puo' contenere solo numeri e 2 caratteri separatori '/'
 * @pre date deve essere fornita nel formato GG/MM/AAAA con 0 < GG <= 31 ; 0 < MM <= 12; 1900 < AAAA <= 2015
 * @pre sex puo' essere 'M' o 'F'
 * @pre coded_date deve poter contenere una striga di 5 caratteri (piu' il carattere terminatore)
 *
 * @post coded_date deve essere una stringa di 5 caratteri
 * @post deve esser composta da (in ordine): 2 cifre, 1 lettera, 2 cifre
 *
 */
void date2code(const char date[], const char sex, char coded_date[]);

/**
 * Calcola il codice di controllo di un codice fiscale (l'ultimo carattere).
 *
 * @param coded_surname Cognome codificato (stringa da 3 caratteri).
 * @param coded_name Nome codificato (stringa da 3 caratteri).
 * @param coded_date Data di nascita codificata (stringa da 5 caratteri).
 * @param coded_birth_place Codice catastale del luogo di nascita (striga da 4 caratteri).
 * @return Carattere di controllo.
 *
 * @pre coded_surname deve essere una stringa di 3 caratteri maiuscoli.
 * @pre coded_name deve essere una stringa di 3 caratteri maiuscoli.
 * @pre coded_date deve essere una stringa di 5 caratteri (2 numeri, 1 lettera, 2 numeri)
 * @pre birth_place_code deve essere una stringa di 4 caratteri (1 lettera, 3 numeri)
 *
 * @post il carattere di controllo deve essere una lettera maiuscola.
 *
 */
char cf_ctrl_code(const char coded_surname[], const char coded_name[],
		const char coded_date[], const char coded_birth_place[]);

/**
 * Calcola il codice fiscale di una persona.
 *
 * @param surname Cognome.
 * @param name Nome.
 * @param date Data di nascita.
 * @param birth_place_code Codice catastale del luogo di nascita.
 * @param sex Sesso.
 * @param cf Codice fiscale (inizializzato a stringa vuota "").
 *
 * @pre surname puo' contenere solo caratteri maiuscoli, spazi, apici.
 * @pre surname deve essere formato da almeno due caratteri.
 *
 * @pre name puo' contenere solo caratteri maiuscoli, spazi, apici.
 * @pre name deve essere formato da almeno due caratteri.
 *
 * @pre date puo' contenere solo numeri e 2 caratteri separatori '/'
 * @pre date deve essere fornita nel formato GG/MM/AAAA con 0 < GG <= 31 ; 0 < MM <= 12; 1900 < AAAA <= 2015
 * @pre birth_place_code codice catastale del luogo di nascita composto da una lettera e tre cifre
 * @pre sex puo' essere 'M' o 'F'
 * @pre cf deve poter almeno contenere una stringa di 16 caratteri (piu' il carattere terminatore)
 *
 * @post cf deve essere una stringa composta da (in ordine): 6 lettere, 2 numeri, 1 lettera, 2 numeri, 1 lettera, 3 numeri, 1 lettera
 *
 */
void cf_generator(const char surname[], const char name[], const char date[],
		const char birth_place_code[], const char sex, char cf[]);

#endif /* CFGENERATOR_000000_SRC_CFGENERATOR_H_ */
