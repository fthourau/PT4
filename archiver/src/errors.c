#include "../head/errors.h"

const char ARCHIVE_ARG_MISSING_ERR[100] = {"Argument manquant: <archive>\0"};
const char FILE_ARG_MISSING_ERR[100] = {"Argument manquant: <fichier(s)>\0"};
const char ALL_ARG_MISSING_ERR[100] = {
							"Arguments manquants: <archive> <fichier(s)>\0"};
const char WRONG_ARCHIVE_FORMAT_ERR[100] = {
  "Un nom d'archive suffixé par '.tar' est nécessaire après les options.\0"};
const char NO_ACTION_ERR[100] = {"Aucune action à effectuer ...\0"};
const char NO_ARGUMENT_ERR[100] = {
						"Aucun argument: 'tar -h' pour voir le manuel ...\0"};
const char UNKNOWN_OPTION_ERR[100] = {
				"Option(s) erronée(s): 'tar -h' pour voir le manuel ...\0"};