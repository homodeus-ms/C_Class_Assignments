#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#define NAME_LENGTH (50)
#define BUFFER_LENGTH (1024)

typedef struct {
    char name[NAME_LENGTH + 1];
    char unused[1];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
} elemental_resistance_t;

typedef struct {
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    unsigned int minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[3];
    char name[NAME_LENGTH + 1];
    char unused[1];

} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);

char* skip_delims(char* ptr, char delim);

#endif /* CHARACTER_DESERIALIZER_H */

