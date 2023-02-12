#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>

#include "character_deserializer.h"

int get_character(const char* filename, character_v3_t* out_character)
{
    char buffer[NAME_LENGTH + 1];
    char name_input[NAME_LENGTH + 1];
    char buffer_values[512];
    char buffer_minion_values[512];

    FILE* stream;

    int c;
    unsigned int value;
    size_t ver;
    char* values_ptr = buffer_values;
    char* minion_ptr = buffer_minion_values;
    char* buffer_ptr = buffer;
    
    size_t fread_count;
    char* minion_ptr_end;
    char* out_v3 = (char*)out_character;
    size_t written_minion_count = 0;
    size_t letter_count = 0;
    
    stream = fopen(filename, "r");
    if (stream == NULL) {
        return -1;
    }

    c = fgetc(stream);
    while (c != EOF && (c >= 'a' && c <= 'z')) {
        c = fgetc(stream);
    }

    fseek(stream, 0, SEEK_SET);

    if (c == ':') {
        ver = 1;
        goto ver1;
    } else if (c == ',') {
        ver = 2;
        goto ver2;
    } else {
        ver = 3;
        goto ver3;
    }

ver1:
    
    c = fgetc(stream);
    while (c != EOF) {
        if (c == ',') {
            c = fgetc(stream);
        }
        while (c != ':') {
            *buffer_ptr++ = c;
            c = fgetc(stream);
        }
        *buffer_ptr = '\0';

        if (fscanf(stream, "%d", &value) == 1) {
            switch (*buffer) {
            case 'l':
                out_character->level = value;
                break;
            case 's':
                out_character->strength = value;
                break;
            case 'd':
                if (*(buffer + 2) == 'x') {
                    out_character->dexterity = value;
                } else {
                    out_character->armour = value;
                }
                break;
            case 'h':
                out_character->health = value;
                break;
            case 'm':
                out_character->mana = value;
                break;
            case 'i':
                if (*(buffer + 1) == 'd') {
                    sprintf(name_input, "player_%d", value);
                    strncpy(out_character->name, name_input, NAME_LENGTH);
                    out_character->name[NAME_LENGTH] = '\0';
                } else {
                    out_character->intelligence = value;
                }
                break;
            default:
                break;
            }
        }

        buffer_ptr = buffer;
        c = fgetc(stream);
    }
    
    out_character->evasion = out_character->dexterity / 2;
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    out_character->elemental_resistance.fire = (out_character->armour / 4) / 3;
    out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
    out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;

    goto close;


ver2:
    if (fgets(buffer_values, 512, stream) == NULL) {
        return -2;
    }
    if (fgets(buffer_values, 512, stream) == NULL) {
        return -3;
    }

    while (*values_ptr != ',') {
        letter_count++;
        if (letter_count <= 50) {
            *buffer_ptr++ = *values_ptr++;
        } else {
            break;
        }
    }
    *buffer_ptr = '\0';
    
    strcpy(out_character->name, buffer);

    while (*values_ptr++ != ',') {
    }

    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->level = value;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->strength = value;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->dexterity = value;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->intelligence = value;
        values_ptr = skip_delims(values_ptr, ',');
    }     
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->armour = value;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->evasion = value;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->elemental_resistance.fire = value / 3;
        out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
        out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->health = value;
        values_ptr = skip_delims(values_ptr, ',');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->mana = value;
    } 
    
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;

    goto close;

ver3:

    if (fgets(buffer_values, 512, stream) == NULL) {
        return -4;
    }
    if (fgets(buffer_values, 512, stream) == NULL) {
        return -5;
    }

    fread_count = fread(buffer_minion_values, 1, 512, stream);

    while (*values_ptr != ' ') {
        letter_count++;
        if (letter_count <= 50) {
            *buffer_ptr++ = *values_ptr++;
        } else {
            break;
        }
    }
    *buffer_ptr = '\0';

    strcpy(out_character->name, buffer);

    values_ptr = skip_delims(values_ptr, '|');

    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->level = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->health = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->mana = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->strength = value;
        values_ptr = skip_delims(values_ptr, '|');
    }     
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->dexterity = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->intelligence = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->armour = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->evasion = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->elemental_resistance.fire = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->elemental_resistance.cold = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->elemental_resistance.lightning = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->leadership = value;
        values_ptr = skip_delims(values_ptr, '|');
    }
    if (sscanf(values_ptr, "%d", &value) == 1) {
        out_character->minion_count = value;
        if (value == 0) {
            goto close;
        }
    }

    minion_ptr_end = minion_ptr + fread_count;
    out_v3 += 52;

    while (*minion_ptr++ != '\n') {
    }

    while (minion_ptr <= minion_ptr_end) {

        letter_count = 0;

        while (*minion_ptr != ' ') {
            letter_count++;
            if (letter_count <= 50) {
                *out_v3++ = *minion_ptr++;
            } else {
                break;
            }
        }
        *out_v3 = '\0';

        minion_ptr = skip_delims(minion_ptr, '|');

        out_v3 = (char*)out_character + 52 + (sizeof(out_character->minions[0].name) * (written_minion_count + 1)) + (sizeof(out_character->minions[0].unused) * (written_minion_count + 1)) + ((sizeof(unsigned int) * 3 * written_minion_count));
    
        while (*minion_ptr != '\n') {
            if (*minion_ptr == ' ' || *minion_ptr == '|') {
                minion_ptr++;
                continue;
            } else {
                unsigned int d;
                char* d_ptr = (char*)&d;
                size_t i;
                if (sscanf(minion_ptr, "%d", &d) == 0) {
                    return -6;
                }
                for (i = 0; i < 4; ++i) {
                    *out_v3++ = *d_ptr++;
                } 
                minion_ptr = skip_delims(minion_ptr, '|');
            }
        }
        minion_ptr++;

        written_minion_count++;
        if (written_minion_count == out_character->minion_count) {
            break;
        }
    }
        

close:
    fclose(stream);

    return ver;
}

char* skip_delims(char* ptr, char delim)
{
    while (*ptr == ' ') {
        ptr++;
    }
    while (*ptr != '\0' && *ptr++ != delim) {
        if (*ptr == '\n') {
            return ptr;
        }
    }
    while (*ptr == ' ') {
        ptr++;
    }
    
    return ptr;
}




        


