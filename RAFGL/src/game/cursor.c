#include <galactic/cursor.h>

cursor_t init_cursor() {

    cursor_t cursor;
    cursor.last_lmb = 0;
    cursor.reshow_cursor = 0;
    
    return cursor;
}