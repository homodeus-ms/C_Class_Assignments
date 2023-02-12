#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "character_deserializer.h"

int main(void)
{
    character_v3_t test_v3;
    int version;

    version = get_character("test_v3.txt", &test_v3);
    assert(version == 3);
    assert(strcmp(test_v3.name, "v3_super_great_hyper_ultra_vibranium_superalloyed_") == 0);
    assert(test_v3.level == 55);
    assert(test_v3.health == 320);
    assert(test_v3.mana == 75);
    assert(test_v3.strength == 75);
    assert(test_v3.dexterity == 55);
    assert(test_v3.intelligence == 35);
    assert(test_v3.armour == 45);
    assert(test_v3.evasion == 30);
    assert(test_v3.leadership == 20);
    assert(test_v3.minion_count == 2);
    assert(test_v3.elemental_resistance.fire == 20);
    assert(test_v3.elemental_resistance.cold == 22);
    assert(test_v3.elemental_resistance.lightning == 15);

    assert(strcmp(test_v3.minions[0].name, "super_ultra_nuclear_blast_supersonic_missile_launc") == 0);
    assert(test_v3.minions[0].health == 50);
    assert(test_v3.minions[0].strength == 15);
    assert(test_v3.minions[0].defence == 5);

    assert(strcmp(test_v3.minions[1].name, "supernova_ultra_high_temperature_plasma_one-handed") == 0);
    assert(test_v3.minions[1].health == 45);
    assert(test_v3.minions[1].strength == 20);
    assert(test_v3.minions[1].defence == 4);


    printf("No Assert!\n");

    return 0;
}



