#ifndef CLOSEHANDLER_H_INCLUDED
#define CLOSEHANDLER_H_INCLUDED
#include <allegro.h>

volatile int close_button_pressed = FALSE;

void close_button_handler(void)
{
    close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)



#endif // CLOSEHANDLER_H_INCLUDED
