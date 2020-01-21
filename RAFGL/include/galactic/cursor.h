#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

typedef struct _cursor_t {

    int last_lmb;
    int reshow_cursor;

} cursor_t;

/* initializes cursor */
cursor_t init_cursor();

#endif // CURSOR_H_INCLUDED
