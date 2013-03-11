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
const char INVALID_OPTION_COMBINATION_ERR[100] = {
										"Combinaison d'option invalide\0"};

const char OPENING_ERR[100] = {"Erreur d'ouverture\0"};
const char INVALID_FILE_ERR[100] = {"Fichier invalide\0"};
const char FILE_NOT_FOUND_ERR[100] = {"Fichier absent de l'archive\0"};
const char STAT_FAILURE_ERR[100] = {"Echec de 'stat()' sur le fichier\0"};
const char TMP_FILE_OPENING_ERR[100] = {
							"Echec de la création du fichier temporaire\0"};
const char OVERRIDE_LIMIT_ERR[100] = {
			"[Erreur interne] La taille de sortie ne doit pas excéder la taille d'entrée\0"};