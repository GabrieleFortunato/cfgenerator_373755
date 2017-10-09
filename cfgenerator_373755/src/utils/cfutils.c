
#include "cfutils.h"

bool is_male(const person* data){
	assert(data != NULL);
	return (data->sex == 'M');
}

bool is_female(const person* data){
	assert(data != NULL);
	return (data->sex == 'F');
}

bool is_surname_AL(const person* data){
	assert(data != NULL);
	return (data->surname[0] >='A'&& data->surname[0]<='L');
}


bool is_surname_MZ(const person* data){
	assert(data != NULL);
	return (data->surname[0] >= 'M' && data->surname[0] <= 'Z');
}

void filter_people(list* people_list, filter_fn filter){
	assert(people_list != NULL);
	assert(filter != NULL);
	node* position = head(people_list);
	node* positiondue = head(people_list);
	do {
		if (filter(content(position)) == false) {
			positiondue = next(people_list, position);
			remove_node(people_list, position);
			position = positiondue;
		} else {
			position = next(people_list, position);
		}
	} while (position != NULL);
}

void generate_cfs(list* people_list, FILE* places_file){
	assert(people_list != NULL);
	assert(places_file != NULL);
	node* newnode = head(people_list);
	while(newnode != NULL){
		cf_generator((*content(newnode)).surname, (*content(newnode)).name, (*content(newnode)).birth_date, read_birth_place_code(places_file, (*content(newnode)).birth_place), (*content(newnode)).sex, (*content(newnode)).cf);
		newnode = next(people_list, newnode);
	}
}

char* read_birth_place_code(FILE* places_file,const char* birth_place){
	assert(places_file != NULL);
	assert(birth_place != '\0');
	char* new_pointer = (char*)malloc((MAX_BIRTH_PLACE + CODED_BIRTH_PLACE_LENGTH + 2)* sizeof(char));
	char* place = (char*)malloc((MAX_BIRTH_PLACE + 1)  * sizeof(char));
	char* coded = (char*)malloc((CODED_BIRTH_PLACE_LENGTH + 1) * sizeof(char));
	char* new_coded = (char*)malloc((CODED_BIRTH_PLACE_LENGTH + 1) * sizeof(char));
	while(fgets(new_pointer,MAX_BIRTH_PLACE + CODED_BIRTH_PLACE_LENGTH + 2 , places_file)!= NULL){
		place = strtok(new_pointer, ",");
		if(strcmp(birth_place, place) == 0){
			coded = strtok(NULL, ",");
			place[strlen(place) - 1] = '\0';
			strcpy(new_coded, coded);
			break;
		}
	}
	assert(coded != NULL);
	return new_coded;
}

list* people_file_to_list(FILE* people_file){
	assert(people_file != NULL);
	assert(people_file != NULL);
	list* lista = new_list();
	int c;
	while ((c = fgetc(people_file)) != EOF){
		ungetc(c, people_file);
		node* node_to_add = new_node(read_person(people_file));
		add_node(lista, tail(lista), node_to_add);
	}
	assert(lista != NULL);
	return lista;
}

void list_to_file(list* people_list, FILE* output_file){
	assert(people_list != NULL);
	assert(output_file != NULL);
	node* newnode = head(people_list);
	while(newnode != NULL){
		fputs((*content(newnode)).surname, output_file);
		fputs("\n", output_file);
		fputs((*content(newnode)).name, output_file);
		fputs("\n", output_file);
		fputs((*content(newnode)).birth_date, output_file);
		fputs("\n", output_file);
		fputs((*content(newnode)).birth_place, output_file);
		fputs("\n", output_file);
		fputc((*content(newnode)).sex, output_file);
		fputs("\n", output_file);
		fputs((*content(newnode)).cf, output_file);
		fputs("\n", output_file);
		newnode = next(people_list, newnode);
	}
}

void list_to_file_males_AL(list* people_list, FILE* output_file){
	assert(people_list != NULL);
	assert(output_file != NULL);
	filter_people(people_list, is_male);
	filter_people(people_list, is_surname_AL);
	list_to_file(people_list, output_file);
}

void list_to_file_females_MZ(list* people_list, FILE* output_file){
	assert(people_list != NULL);
	assert(output_file != NULL);
	filter_people(people_list, is_female);
	filter_people(people_list, is_surname_MZ);
	list_to_file(people_list, output_file);

}





void people_to_file_cf(FILE* people_file, FILE* output_file, FILE* places_file){


        assert(people_file != NULL);


        assert(output_file != NULL);


        assert(places_file != NULL);


        list* newlist = people_file_to_list(people_file);


        generate_cfs(newlist, places_file);


        list_to_file(newlist, output_file);
}

void people_to_file_cf_males_AL(FILE* people_file, FILE* output_file, FILE* places_file){
	assert(people_file != NULL);
	assert(output_file != NULL);
	assert(places_file != NULL);
	list* newlist = people_file_to_list(people_file);
	generate_cfs(newlist, places_file);
	list_to_file_males_AL(newlist, output_file);
}

void people_to_file_cf_females_MZ(FILE* people_file, FILE* output_file, FILE* places_file){
	assert(people_file != NULL);
	assert(output_file != NULL);
	assert(places_file != NULL);
	list* newlist = people_file_to_list(people_file);
	generate_cfs(newlist, places_file);
	list_to_file_females_MZ(newlist, output_file);
}

char* outfile_path(char* wd_path, char* filename){
	assert(wd_path[strlen(wd_path)-1] == OS_SEP);
	char* percorso = (char*)malloc(
			(strlen(wd_path) + strlen(filename) + 1) * sizeof(char)
	);
	strcpy(percorso, "");
	strcpy(percorso, wd_path);
	strcat(percorso, filename);
	assert(strlen(percorso) == strlen(wd_path) + strlen(filename));
	return percorso;
}
