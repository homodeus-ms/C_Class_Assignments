#include <stdio.h>
#include <string.h>

#include "translate.h"

int translate(int argc, const char** argv)
{
    int c;
    
    char buffer1[BUFFER_LENGTH];
    char buffer2[BUFFER_LENGTH];

    int length1;
    int length2;
    int argv_index1 = 1;
    int argv_index2 = 2;
    
    error_code_t err_no = 0;

    char* buffer1_p;
    
    if (argc < 3 || argc > 4) {
        err_no = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
        return err_no;
    } else if (argc == 4 && strcmp(argv[1], "-i") != 0) {
        err_no = ERROR_CODE_INVALID_FLAG;
        return err_no;
    } else if (argc == 4) {
        argv_index1++;
        argv_index2++;
    }

    length1 = strlen(argv[argv_index1]);
    length2 = strlen(argv[argv_index2]);

    if (length1 > BUFFER_LENGTH - 1 || length2 > BUFFER_LENGTH - 1) {
        err_no = ERROR_CODE_ARGUMENT_TOO_LONG;
        return err_no;
    }

    buffer1_p = buffer1;

    set_buffer(buffer1, argv[argv_index1], &err_no);
    set_buffer(buffer2, argv[argv_index2], &err_no);

    if (err_no != 0) {
        return err_no;
    }

    c = getchar();

    while (c != EOF) {
        int temp_c = c;

        while (*buffer1_p != '\0') {
            size_t offset;
            if (argc == 4 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                int insensitive_c = *buffer1_p ^ 0x20;
                if (c == *buffer1_p || c == insensitive_c) {
                    offset = buffer1_p - buffer1;
                    temp_c = offset < length2 ? buffer2[offset] : buffer2[length2 - 1];
                }
            } else {
                if (c == *buffer1_p) {
                    offset = buffer1_p - buffer1;
                    temp_c = offset < length2 ? buffer2[offset] : buffer2[length2 - 1];
                }
            }
            buffer1_p++;
        }

        c = temp_c;
        putchar(c);

        c = getchar();
        buffer1_p = buffer1;
    }
 
    return 0;
}

void set_buffer(char* buffer, const char* input, error_code_t* err_no)
{
    char* buffer_p = buffer;
    const char* input_p = input;
    int c;
    error_code_t error_number;

    int out_use_as_char = 0;
    size_t input_length;
    const char* range_end = NULL;
    
    while (*input_p != '\0') {
        error_number = 0;
        c = *input_p;
        
        if (c == '\\') {
            c = combine_escape_letters(input_p, &error_number);

            if (error_number == 3) {
                *err_no = error_number;
                return;
            } else {
                *buffer_p = c;
                input_p++;
            }
        } else if (c == '-') {
            int range;
            input_length = strlen(input);
            
            range = get_range(input, input_p, input_length, &error_number, &out_use_as_char, range_end);

            if (range == -1 && out_use_as_char == 1) {
                *buffer_p = c;
            } else if (error_number >= 4) {
                *err_no = error_number;
                return;
            } else {
                size_t i;
                char start_value = *(input_p - 1);

                for (i = 0; i < range; ++i) {
                    *buffer_p++ = ++start_value;
                }
                range_end = input_p + 1;
                input_p += 2;
                continue;
            }
        } else {
            *buffer_p = c;
        }

        buffer_p++;
        input_p++;
    }

    *buffer_p = '\0';
}

int combine_escape_letters(const char* ptr, error_code_t* error_number)
{
    switch (*(ptr + 1)) {
    case '\\':
        return '\\';
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 'f':
        return '\f';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    case '\'':
        return '\'';
    case '\"':
        return '\"';
    
    default:
        *error_number = ERROR_CODE_INVALID_FORMAT;
        return -1;
    }
}

int get_range(const char* arr, const char* ptr, size_t arr_length, error_code_t* error_number, int* out_use_as_char, const char* range_end)
{

    if (ptr == arr || ptr == arr + arr_length) {
        *out_use_as_char = 1;
        return -1;
    }
    if (range_end != NULL && range_end == ptr - 1) {
        *out_use_as_char = 1;
        return -1;
    }
       
    if (*(ptr - 1) > *(ptr + 1)) {
        *error_number = ERROR_CODE_INVALID_RANGE;
        return -1;
    }
    if (arr_length + (*(ptr + 1) - *(ptr - 1)) > BUFFER_LENGTH) {
        *error_number = ERROR_CODE_ARGUMENT_TOO_LONG;
        return 0xffff;
    } else {
        return *(ptr + 1) - *(ptr - 1);
    }
}



            
            
            

         






    


