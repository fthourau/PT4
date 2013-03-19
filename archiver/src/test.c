#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../head/test.h"

#define SPLITLINE_D printf("==============================================\n")
#define SPLITLINE_S printf("----------------------------------------------\n")
#define CR printf("\n")

#define FAILURE printf("ECHEC\n")
#define SUCCESS printf("OK\n")
#define UNEXPECTED_ERROR fprintf(stderr, "Erreur inattendue !\n")

int nb_error = 0;

void test() {
	SPLITLINE_D;
	printf("\tLANCEMENT DES TESTS\n");
	SPLITLINE_D;

	CR;
	SPLITLINE_S;
	printf("\tTESTS CREATE\n");
	test_create();
	SPLITLINE_S;

	CR;
	SPLITLINE_S;
	printf("\tTESTS EXTRACT\n");
	test_extract();
	SPLITLINE_S;

	CR;
	SPLITLINE_S;
	printf("\tTESTS ADD\n");
	test_add();
	SPLITLINE_S;

	CR;
	SPLITLINE_S;
	printf("\tTESTS DELETE\n");
	test_delete();
	SPLITLINE_S;

	CR;
	SPLITLINE_S;
	printf("\tTESTS ARCHIVEHANDLING\n");
	test_archivehandling();
	SPLITLINE_S;

	CR;
	SPLITLINE_S;
	printf("\tTESTS FILEHANDLING\n");
	test_filehandling();
	SPLITLINE_S;

	SPLITLINE_D;
	printf("\tFIN DES TESTS\n");
	if(nb_error == 0)
		printf("Aucune erreur n'est survenue durant les tests.\n");
	else if(nb_error == 1)
		printf("%d erreur est survenue durant les tests.\n", nb_error);
	else
		printf("%d erreurs sont survenues durant les tests.\n", nb_error);

	SPLITLINE_D;

	exit(EXIT_SUCCESS);
}

void test_create() {
	char* files[] = { "./test/create.test", 
					  "./test/file1.correct", 
					  "./test/file2.correct" };

	first_argument_position = 0;
	MAKE_ARCHIVE_FLAG = true;

	create_archive_from_files(3, files);

	FILE* a = fopen("./test/create.test", "r");
	FILE* c = fopen("./test/create.correct", "r");

	if(a != NULL && c != NULL) {
		char* buf1 = malloc(12288);
		char* buf2 = malloc(12288);

		fread(buf1, 12288, 1, a);
		fread(buf2, 12288, 1, c);

		if(strcmp(buf1, buf2) == 0)
			SUCCESS;
		else {
			FAILURE;
			nb_error++;
		}

		fclose(a);
		fclose(c);

		system("rm ./test/create.test");

		free(buf1);
		free(buf2);
	}
	else
		UNEXPECTED_ERROR;
}

void test_extract() {
	first_argument_position = 0;

	extract_files_from_archive("./test/extract.test");

	FILE* t1 = fopen("./file1.test", "r");
	FILE* t2 = fopen("./file2.test", "r");

	FILE* c1 = fopen("./test/file1.correct", "r");
	FILE* c2 = fopen("./test/file2.correct", "r");

	if(t1 != NULL && t2 != NULL) {
		if(c1 != NULL && c2 != NULL) {
			fseek(t1, 0, SEEK_END);
			fseek(t2, 0, SEEK_END);
			fseek(c1, 0, SEEK_END);
			fseek(c2, 0, SEEK_END);

			if(ftell(t1) == ftell(c1) && ftell(t2) == ftell(c2))
				SUCCESS;
			else {
				FAILURE;
				nb_error++;
			}

			fclose(c1);
			fclose(c2);

			system("rm file1.test file2.test");
		}
		else
			UNEXPECTED_ERROR;
		
		fclose(t1);
		fclose(t2);
	}
	else {
		FAILURE;
		nb_error++;
	}
}

void test_add() {
	char* create_f[] = { "./test/add.test", "./test/file1.correct" };
	char* add_f[] = { "./test/add.test", "./test/file2.correct" };

	first_argument_position = 0;
	MAKE_ARCHIVE_FLAG = true;

	create_archive_from_files(2, create_f);
	add_files_to_archive(2, add_f);

	FILE* a = fopen("./test/add.test", "r");
	FILE* c = fopen("./test/add.correct", "r");

	if(a != NULL && c != NULL) {
		char* buf1 = malloc(12288);
		char* buf2 = malloc(12288);

		fread(buf1, 12288, 1, a);
		fread(buf2, 12288, 1, c);

		if(strcmp(buf1, buf2) == 0)
			SUCCESS;
		else {
			FAILURE;
			nb_error++;
		}

		fclose(a);
		fclose(c);

		system("rm ./test/add.test");

		free(buf1);
		free(buf2);
	}
	else
		UNEXPECTED_ERROR;
}

void test_delete() {
	char* files[] = { "./test/delete.test", "file2.correct" };
	first_argument_position = 0;

	delete_files_from_archive(2, files);

	FILE* a = fopen("./test/delete.test", "r");
	FILE* c = fopen("./test/delete.correct", "r");

	if(a != NULL && c != NULL) {
		char* buf1 = malloc(4608);
		char* buf2 = malloc(4608);

		fread(buf1, 4608, 1, a);
		fread(buf2, 4608, 1, c);

		if(strcmp(buf1, buf2) == 0 && ( ftell(a) == ftell(c) ))
			SUCCESS;
		else {
			FAILURE;
			nb_error++;
		}

		fclose(a);
		fclose(c);

		system("cp ./test/create.correct ./test/delete.test");

		free(buf1);
		free(buf2);
	}
	else
		UNEXPECTED_ERROR;
}

void test_archivehandling() {
	FILE* a = fopen("./test/create.correct", "r+");

	if(a != NULL) {
		char* filename = "file1.correct";
		char* prefix = "\0";

		if(file_is_present(filename, prefix, a) != -1)
			SUCCESS;
		else {
			FAILURE;
			nb_error++;
		}

		fseek(a, 0, SEEK_SET);

		if(number_of_file_in_archive(a) == 2)
			SUCCESS;
		else {
			FAILURE;
			nb_error++;
		}
	}
	else
		UNEXPECTED_ERROR;
}

void test_filehandling() {
	char* fullpath = "/dir/other/test/file.current";
	char* filename = malloc(100);
	char* prefix = malloc(155);

	memset(filename, 0, 100);
	memset(prefix, 0, 155);

	get_prefix_and_name(fullpath, filename, prefix);

	if(	strcmp(prefix, "/dir/other/test/") == 0 && 
		strcmp(filename, "file.current") == 0)
		SUCCESS;
	else {
		FAILURE;
		nb_error++;
	}
}