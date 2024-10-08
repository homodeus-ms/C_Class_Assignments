#ifndef RECEIPTER_H
#define RECEIPTER_H

#include <time.h>

#define TRUE (1)
#define FALSE (0)

int add_item(const char* name, double price);

void set_tip(double tip);

void set_message(const char* message);

int print_receipt(const char* filename, time_t timestamp);

void initialize_statics(void);

#endif /* RECEIPTER_H */


