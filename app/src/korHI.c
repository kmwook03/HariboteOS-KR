#include "../include/apilib.h"

void HariMain(void)
{
    static char s[30] = {'안', '녕', '하', '세', '요', 0x00};
    api_putstr0(s);
    api_end();
}
