#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)

#define BUFFER_LENGTH (512)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1,
    ERROR_CODE_INVALID_FLAG,
    ERROR_CODE_INVALID_FORMAT,
    ERROR_CODE_ARGUMENT_TOO_LONG,
    ERROR_CODE_INVALID_RANGE
} error_code_t;

int translate(int argc, const char** argv);

void set_buffer(char* buffer, const char* input, error_code_t* err_no);

int combine_escape_letters(const char* ptr, error_code_t* error_number);

int get_range(const char* arr, const char* ptr, size_t arr_length, error_code_t* error_number, int* out_use_as_char, const char* range_end);

#endif /* TRANSLATE_H */


