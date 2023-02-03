#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "receipter.h"

#define MENU_LENGTH (25)
#define MESSAGE_MAX_LENGTH (75)
#define RECEIPT_MAX_WIDTH (50)

static size_t s_order_no = 0;
static size_t s_item_count = 0;
static char s_menus[300];
static char* s_pos_menus = s_menus;
static double s_prices[11];
static double* s_pos_prices = s_prices;
static double s_tip = 0;
static char s_message[MESSAGE_MAX_LENGTH + 1];

int add_item(const char* name, double price)
{
    size_t num_written;    

    if (s_item_count >= 10) {
        return FALSE;
    }
    
    num_written = strlen(name);
    
    strncpy(s_pos_menus, name, 25);
    s_pos_menus += num_written;
    *s_pos_menus++ = ',';
    *s_pos_menus = '\0';

    *s_pos_prices++ = price;
    
    s_item_count++;

    return TRUE;
}

void set_tip(double tip)
{
    s_tip = tip;
}

void set_message(const char* message)
{
    s_message[0] = '\0';
    strncpy(s_message, message, MESSAGE_MAX_LENGTH);
    s_message[MESSAGE_MAX_LENGTH] = '\0';
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* stream;
    const char* RESTAURANT_NAME = "Charles' Seafood";
    const char* TAX_REPORT_NO = "Tax#-51234";
    struct tm* t;
    char TIME_INFO[20];
    char* menu_name_token;
    double menu_price;
    double sub_total = 0;
    double tax;

    if (s_item_count == 0) {
        initialize_statics();
        return FALSE;
    }

    t = gmtime(&timestamp);
    sprintf(TIME_INFO, "%04d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t ->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    stream = fopen(filename, "w");

    fprintf(stream, "%-s\n", RESTAURANT_NAME);
    fprintf(stream, "--------------------------------------------------\n");
    fprintf(stream, "%-45s", TIME_INFO);
    fprintf(stream, "%05d\n", s_order_no);
    fprintf(stream, "--------------------------------------------------\n");

    menu_name_token = strtok(s_menus, ",");
    s_pos_prices = s_prices;

    while (menu_name_token != NULL) {
        fprintf(stream, "%33s", menu_name_token);
        menu_price = *s_pos_prices++;
        fprintf(stream, "%17.2f\n", menu_price);
        menu_name_token = strtok(NULL, ",");
    }
    
    fprintf(stream, "\n");
     
    while (s_item_count-- > 0) {
        sub_total += *--s_pos_prices;
    }         

    fprintf(stream, "%33s%17.2f\n", "Subtotal", sub_total);
    if (s_tip != 0) {
        fprintf(stream, "%33s%17.2f\n", "Tip", s_tip);
    }

    tax = roundf((sub_total * 0.05) * 100) / 100;
    
    fprintf(stream, "%33s%17.2f\n", "Tax", tax);
    fprintf(stream, "%33s%17.2f\n", "Total", sub_total + s_tip + tax);
    fprintf(stream, "\n");
    
    if (s_message[0] != '\0') {
        char c;
        char* pos_s_message = s_message;

        while (*pos_s_message != '\0') {
            if (pos_s_message == s_message + 50) {
                fputc('\n', stream);
            }
            c = *pos_s_message;
            fputc(c, stream);
            pos_s_message++;
        }
        fprintf(stream, "\n");
    }
    
    fprintf(stream, "==================================================\n");
    fprintf(stream, "%50s", TAX_REPORT_NO);

    fclose(stream);

    s_order_no++;
    
    initialize_statics();

    return TRUE;
}

void initialize_statics(void)
{
    s_item_count = 0;
    s_pos_menus = s_menus;
    s_pos_prices = s_prices;
    s_tip = 0;
    s_message[0] = '\0';
}










