#ifndef ERRORS_H
#define ERRORS_H

// Error messages about command and arguments
extern const char ARCHIVE_ARG_MISSING_ERR[100];
extern const char FILE_ARG_MISSING_ERR[100];
extern const char ALL_ARG_MISSING_ERR[100];
extern const char WRONG_ARCHIVE_FORMAT_ERR[100];
extern const char NO_ACTION_ERR[100];
extern const char NO_ARGUMENT_ERR[100];
extern const char UNKNOWN_OPTION_ERR[100];
extern const char INVALID_OPTION_COMBINATION_ERR[100];

// Error messages about files
extern const char OPENING_ERR[100];
extern const char INVALID_FILE_ERR[100];
extern const char FILE_NOT_FOUND_ERR[100];
extern const char STAT_FAILURE_ERR[100];
extern const char TMP_FILE_OPENING_ERR[100];

// Error messages about extraction
extern const char OVERRIDE_LIMIT_ERR[100];

// Error messages about update
extern const char UPDATE_ERR[100];

#endif