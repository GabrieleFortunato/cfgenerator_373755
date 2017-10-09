/*
 * cf_generator.c
 *
 *  Created on: May 11, 2015
 *      Author: marco
 */

#include "cfgenerator.h"





static bool has_valid_chars(const char text[])
{
	bool answer = true;
	for (int i = 0; text[i] != EOS; i++) {
		char c = text[i];
		if (!(isupper(c) || isspace(c) || ispunct(c))) {
			answer = false;
			break;
		}
	}
	return answer;
}


static bool is_uppercase(const char code[])
{
	bool answer = true;

	for (int i=0; code[i] != EOS; i++){
		if (!(isupper(code[i]))){
			answer = false;
			break;
		}
	}
	return answer;
}


static bool has_numbers_and_2separators(const char str[])
{
	bool answer = true;
	int sep_counter = 0;
	for (int i=0; str[i] != EOS; i++){
		if (str[i] == '/'){
			sep_counter += 1;
		}
		if (!((isdigit(str[i])) || (str[i] == '/')) && (sep_counter > 2)){
			answer = false;
			break;
		}
	}
	return answer;
}


static bool is_correct_format_date(const char str[])
{
	bool answer = true;

	char day_c[DATE_DIGITS];
	char month_c[DATE_DIGITS];
	char year_c[DATE_DIGITS+DATE_DIGITS];

	for (int i=0; str[i] != EOS; i++){
		if (i < MONTH_INDEX-1){
			day_c[i] = str[i];
		} else if ((i >= MONTH_INDEX) && (i >= YEAR_INDEX-1)){
			month_c[i] = str[i];
		} else if (i >= YEAR_INDEX){
			year_c[i] = str[i];
		}
	}

	int day_i = atoi(day_c);
	int month_i = atoi(month_c);
	int year_i = atoi(year_c);

	if (!(day_i > 1 || day_i < 31)){
		answer = false;
	} else if (!(month_i > 1 || month_i < 12)){
		answer = false;
	} else if (!(year_i > 1900 || year_i < 2015)){
		answer = false;
	}

	return answer;
}


static bool has_correct_format_datecode(const char str[])
{
	bool answer = true;

	for (int i=0; str[i] != EOS; i++){
		if ((i < CODED_MONTH_INDEX) || (i >= CODED_DAY_INDEX )){
			if (!(isdigit(str[i]))){
				answer = false;
				break;
			}
		} else if (i == CODED_MONTH_INDEX) {
			if (!(isalpha(str[i]))){
				answer = false;
				break;
			}
		}
	}

	return answer;
}


static bool has_correct_format_birth_place_code(const char str[])
{
	bool answer = true;

	for (int i=0; str[i] != EOS; i++){
		if (i == 0){
			if (!(isalpha(str[i]))){
				answer = false;
				break;
			}
		} else if (i > 0) {
			if (!(isdigit(str[i]))){
				answer = false;
				break;
			}
		}
	}
	return answer;
}


static void init_array(char a[], int l) {
	memset(a,EOS,l);
}


static int compactify(const char org_str[], char comp_str[])
{
	int j = 0;
	for (int i = 0; org_str[i] != EOS; i++) {
		if (isalpha(org_str[i])) {
			comp_str[j] = org_str[i];
			j++;
		}
	}
	comp_str[j] = EOS;
	return j;
}


static bool is_vowel(const char ch)
{
	bool answer = false;

	switch (ch) {
	case 'A':
		answer = true;
		break;
	case 'E':
		answer = true;
		break;
	case 'I':
		answer = true;
		break;
	case 'O':
		answer = true;
		break;
	case 'U':
		answer = true;
		break;
	}
	return answer;
}


static int get_consonants(const char str[], char consonants[])
{
	int num_consonants = 0;
	int j = 0;
	for (int i = 0; str[i] != EOS; i++) {
		bool vowel = is_vowel(str[i]);
		if (!vowel) {
			consonants[j] = str[i];
			num_consonants++;
			j++;
		}
	}
	return num_consonants;
}


static int get_vowels(const char str[], char vowels[])
{
	int num_vowels = 0;
	int j = 0;

	for (int i = 0; str[i] != EOS; i++) {
		bool vowel = is_vowel(str[i]);
		if (vowel) {
			vowels[j] = str[i];
			num_vowels++;
			j++;
		}
	}
	return num_vowels;
}


static void add_3_chars_name(const char str[], char code[])
{
	int j = 0;
	for (int i = 0; i < 4; i++) {		// takes the first 4 chars: 1st, 3rd, 4th
		if (i != 1) {
			code[j] = str[i];
			j++;
		}
	}
}


static void add_3_chars(const char str[], char code[])
{
	for (int i = 0; i < 3; i++) {
		code[i] = str[i];
	}
}


static int add_2_chars(const char str[], char code[], int from)
{
	for (int i = 0; i < 2; i++) {
		code[from] = str[i];
		from++;
	}
	return from;
}


static int add_1_char(const char str[], char code[], int from)
{
	code[from] = str[0];
	from++;
	return from;
}

static void add_special_char(char code[], int from)
{
	code[from] = 'X';
}


static void code_year(const char date[], char coded_date[])
{

	for (int i = 0; i < DATE_DIGITS; i++) {
		coded_date[CODED_YEAR_INDEX + i] = date[i + YEAR_INDEX];
	}
}

static void code_month(const char date[], char coded_date[])
{
	const char m_code[] = { 'A', 'B', 'C', 'D', 'E', 'H', 'L', 'M', 'P', 'R', 'S', 'T' };

	char month[2];
	for (int i = 0; i < DATE_DIGITS; i++) {
		month[i] = date[i + MONTH_INDEX];
	}

	int month_int = atoi(month);
	coded_date[CODED_MONTH_INDEX] = m_code[month_int - 1];
}

static void code_day(const char date[], char sex, char coded_date[])
{
	if (sex == 'M') {
		for (int i = 0; i < DATE_DIGITS; i++) {
			coded_date[CODED_DAY_INDEX + i] = date[i + DAY_INDEX];
		}
	} else if (sex == 'F') {
		char day[DATE_DIGITS];
		for (int i = 0; i < DATE_DIGITS; i++) {
			day[i] = date[i + DAY_INDEX];
		}
		day[DATE_DIGITS] = EOS;
		int val_day = atoi(day);
		val_day += FEMALE_DAYS_OFFSET;
		sprintf(day, "%d", val_day);

		for (int i = 0; i < DATE_DIGITS; i++) {
			coded_date[i + CODED_DAY_INDEX] = day[i];
		}
	}

}


static int odd_char2code(char cf_code)
{
	int code;

	switch (cf_code) {
	case '0':
		code = 1;
		break;
	case '1':
		code = 0;
		break;
	case '2':
		code = 5;
		break;
	case '3':
		code = 7;
		break;
	case '4':
		code = 9;
		break;
	case '5':
		code = 13;
		break;
	case '6':
		code = 15;
		break;
	case '7':
		code = 17;
		break;
	case '8':
		code = 19;
		break;
	case '9':
		code = 21;
		break;
	case 'A':
		code = 1;
		break;
	case 'B':
		code = 0;
		break;
	case 'C':
		code = 5;
		break;
	case 'D':
		code = 7;
		break;
	case 'E':
		code = 9;
		break;
	case 'F':
		code = 13;
		break;
	case 'G':
		code = 15;
		break;
	case 'H':
		code = 17;
		break;
	case 'I':
		code = 19;
		break;
	case 'J':
		code = 21;
		break;
	case 'K':
		code = 2;
		break;
	case 'L':
		code = 4;
		break;
	case 'M':
		code = 18;
		break;
	case 'N':
		code = 20;
		break;
	case 'O':
		code = 11;
		break;
	case 'P':
		code = 3;
		break;
	case 'Q':
		code = 6;
		break;
	case 'R':
		code = 8;
		break;
	case 'S':
		code = 12;
		break;
	case 'T':
		code = 14;
		break;
	case 'U':
		code = 16;
		break;
	case 'V':
		code = 10;
		break;
	case 'W':
		code = 22;
		break;
	case 'X':
		code = 25;
		break;
	case 'Y':
		code = 24;
		break;
	case 'Z':
		code = 23;
		break;
	}

	return code;
}

static int even_char2code(char cf_code)
{
	int code;

	switch (cf_code) {
	case '0':
		code = 0;
		break;
	case '1':
		code = 1;
		break;
	case '2':
		code = 2;
		break;
	case '3':
		code = 3;
		break;
	case '4':
		code = 4;
		break;
	case '5':
		code = 5;
		break;
	case '6':
		code = 6;
		break;
	case '7':
		code = 7;
		break;
	case '8':
		code = 8;
		break;
	case '9':
		code = 9;
		break;
	case 'A':
		code = 0;
		break;
	case 'B':
		code = 1;
		break;
	case 'C':
		code = 2;
		break;
	case 'D':
		code = 3;
		break;
	case 'E':
		code = 4;
		break;
	case 'F':
		code = 5;
		break;
	case 'G':
		code = 6;
		break;
	case 'H':
		code = 7;
		break;
	case 'I':
		code = 8;
		break;
	case 'J':
		code = 9;
		break;
	case 'K':
		code = 10;
		break;
	case 'L':
		code = 11;
		break;
	case 'M':
		code = 12;
		break;
	case 'N':
		code = 13;
		break;
	case 'O':
		code = 14;
		break;
	case 'P':
		code = 15;
		break;
	case 'Q':
		code = 16;
		break;
	case 'R':
		code = 17;
		break;
	case 'S':
		code = 18;
		break;
	case 'T':
		code = 19;
		break;
	case 'U':
		code = 20;
		break;
	case 'V':
		code = 21;
		break;
	case 'W':
		code = 22;
		break;
	case 'X':
		code = 23;
		break;
	case 'Y':
		code = 24;
		break;
	case 'Z':
		code = 25;
		break;
	}

	return code;
}


static char reminder2code(int value)
{
	const char code[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
			'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z' };

	return code[value];
}

void surname2code(const char org_surname[], char coded_surname[])
{
	int original_length = strlen(org_surname);

	assert(original_length >= MIN_SURNAME_LENGTH);
	assert(has_valid_chars(org_surname));

	char compacted_surname[original_length+1];          // '\0'
	init_array(compacted_surname, original_length+1);
	int compacted_length = compactify(org_surname, compacted_surname);

	char consonants[compacted_length];
	char vowels[compacted_length];

	init_array(consonants, compacted_length);
	int num_consonants = get_consonants(compacted_surname, consonants);

	init_array(vowels, compacted_length);
	int num_vowels = get_vowels(compacted_surname, vowels);

	int placeholder = 0;
	if (num_consonants > MIN_SURNAME_LENGTH) {
		add_3_chars(consonants, coded_surname);
	} else if ((num_consonants == MIN_SURNAME_LENGTH) && (num_vowels >= 1)) {
		placeholder = add_2_chars(consonants, coded_surname, placeholder);
		placeholder = add_1_char(vowels, coded_surname, placeholder);
	} else if ((num_consonants == 1) && (num_vowels >= MIN_SURNAME_LENGTH)) {
		placeholder = add_1_char(consonants, coded_surname, placeholder);
		placeholder = add_2_chars(vowels, coded_surname, placeholder);
	} else {
		placeholder = add_1_char(consonants, coded_surname, placeholder);
		placeholder = add_1_char(vowels, coded_surname, placeholder);
		add_special_char(coded_surname, placeholder);
	}

	coded_surname[CODED_SRN_LENGTH] = EOS;		// append '\0' at the end of code

	assert(strlen(coded_surname) == CODED_SRN_LENGTH);
	assert(is_uppercase(coded_surname));
}


void name2code(const char org_name[], char coded_name[])
{
	const int original_length = strlen(org_name);

	assert(original_length > MIN_NAME_LENGTH);
	assert(has_valid_chars(org_name));

	char compacted_name[original_length+1];          // '\0'
	init_array(compacted_name, original_length+1);
	int compacted_length = compactify(org_name, compacted_name);

	char consonants[compacted_length];
	char vowels[compacted_length];

	init_array(consonants, compacted_length);
	int num_consonants = get_consonants(compacted_name, consonants);

	init_array(vowels, compacted_length);
	int num_vowels = get_vowels(compacted_name, vowels);

	int placeholder = 0;
	if (num_consonants > MIN_CONSONANT) {
		add_3_chars_name(consonants, coded_name);
	} else if (num_consonants == MIN_CONSONANT) {
		add_3_chars(consonants, coded_name);
	} else if ((num_consonants == MIN_NAME_LENGTH) && (num_vowels >= 1)) {
		placeholder = add_2_chars(consonants, coded_name, placeholder);
		placeholder = add_1_char(vowels, coded_name, placeholder);
	} else if ((num_consonants == 1) && (num_vowels >= MIN_NAME_LENGTH)) {
		placeholder = add_1_char(consonants, coded_name, placeholder);
		placeholder = add_2_chars(vowels, coded_name, placeholder);
	} else {
		placeholder = add_1_char(consonants, coded_name, placeholder);
		placeholder = add_1_char(vowels, coded_name, placeholder);
		add_special_char(coded_name, placeholder);
	}

	coded_name[CODED_NAME_LENGTH] = EOS;		// append '\0' at the end of code

	assert(strlen(coded_name) == CODED_NAME_LENGTH);
	assert(is_uppercase(coded_name));
}


void date2code(const char date[], const char sex, char coded_date[])
{
	assert(has_numbers_and_2separators(date));
	assert(is_correct_format_date(date));
	assert((sex == 'M') || (sex == 'F'));

	code_year(date, coded_date);
	code_month(date, coded_date);
	code_day(date, sex, coded_date);

	coded_date[CODED_DATE_LENGTH] = EOS;		// append '\0' at the end of code

	assert(strlen(coded_date) == CODED_DATE_LENGTH);
	assert(has_correct_format_datecode(coded_date));
}


char cf_ctrl_code(const char coded_surname[], const char coded_name[],
					const char coded_date[], const char birth_place_code[])
{
	assert(strlen(coded_surname) == CODED_SRN_LENGTH);
	assert(is_uppercase(coded_surname));

	assert(strlen(coded_name) == CODED_NAME_LENGTH);
	assert(is_uppercase(coded_name));

	assert(strlen(coded_date) == CODED_DATE_LENGTH);
	assert(has_correct_format_datecode(coded_date));

	assert(strlen(birth_place_code) == CODED_BIRTH_PLACE_LENGTH);
	assert(has_correct_format_birth_place_code(birth_place_code));

	char ctrl_code;
	char cf_code[TEST_CF_LENGTH] = "";
	strcat(cf_code, coded_surname);
	strcat(cf_code, coded_name);
	strcat(cf_code, coded_date);
	strcat(cf_code, birth_place_code);

	int code;
	int sum = 0;
	for (int i = 0; i < TEST_CF_LENGTH - 1; i++) {
		if (((i + 1) % 2) == 0) {	// even numbers
			code = even_char2code(cf_code[i]);
		} else if (((i + 1) % 2) != 0) { // odd numbers
			code = odd_char2code(cf_code[i]);
		}
		sum += code;
	}

	int reminder = sum % LETTERS;
	ctrl_code = reminder2code(reminder);

	assert((isupper(ctrl_code)) && (isalpha(ctrl_code)));

	return ctrl_code;
}


void cf_generator(const char surname[], const char name[], const char date[],
		const char birth_place_code[], const char sex, char cf[])
{
	int srn_length = strlen(surname);
	int name_length = strlen(name);
	int date_length = strlen(date);

	assert(srn_length >= MIN_SURNAME_LENGTH);
	assert(has_valid_chars(surname));

	assert(name_length >= MIN_NAME_LENGTH);
	assert(has_valid_chars(name));

	assert(date_length == DATE_ORG_LENGTH);
	assert(has_numbers_and_2separators(date));
	assert(is_correct_format_date(date));

	assert((sex == 'M') || (sex == 'F'));

	//assert(strlen(cf) == CF_LENGTH);

	char srn_code[CODED_SRN_LENGTH+1];
	surname2code(surname, srn_code);

	char name_code[CODED_NAME_LENGTH+1];
	name2code(name, name_code);

	char date_code[CODED_DATE_LENGTH+1];
	date2code(date, sex, date_code);

	char ctrl_code = cf_ctrl_code(srn_code, name_code, date_code, birth_place_code);

	init_array(cf,TEST_CF_LENGTH+1);

	strcat(cf, srn_code);
	strcat(cf, name_code);
	strcat(cf, date_code);
	strcat(cf, birth_place_code);
	cf[TEST_CF_LENGTH - 1] = ctrl_code;
	cf[TEST_CF_LENGTH] = EOS;		// append '\0' at the end of code
}

