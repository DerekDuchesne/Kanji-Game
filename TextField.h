#include <alfont.h>
#include <allegro.h>
#include <iostream>
#include <string>
#include <stack>
#include <windows.h>
#include <winbase.h>
#include <winalleg.h>
#include "CloseHandler.h"


using namespace std;

//Represents a text window that the user can type into. Keypresses will be converted into hiragana.
class TextField
{
    private:
        string romajiInput;
        string hiraganaInput;
        int x, y, textColor, recWidth, recHeight;
        float pos;
        BITMAP* screen;
        BITMAP* currentBackground;
        BITMAP* temp;
        ALFONT_FONT* font;


    public:
        TextField(int x, int y, int textColor, BITMAP* screen, BITMAP* currentBackground, ALFONT_FONT* font);
        void getInput();
        void printIt(const char* romaji, const char* hiragana, int shiftR, int shiftL);
        string getRomaji();
};

TextField::TextField(int x, int y, int textColor, BITMAP* screen, BITMAP* currentBackground, ALFONT_FONT* font)
{
    this->x = x;
    this->y = y;
    pos = x;
    recHeight=35;
    recWidth=25;
    this->textColor = textColor;
    this->screen = screen;
    this->currentBackground = currentBackground;
    temp = create_bitmap(currentBackground->w, currentBackground->h);
    blit(currentBackground, temp, 0, 0, 0, 0, currentBackground->w, currentBackground->h);
    this->font = font;
}

//Kill me.
void TextField::getInput()
{
    int val, scancode=0, windowsPos=0;
    stack<int> stringShifts;
    stack<float> charShifts;
    BITMAP* buffer = create_bitmap(200, alfont_text_height(font));
    clear_to_color(buffer, makecol(255,0,255));
    while(!key[KEY_ENTER] || !key[KEY_ENTER_PAD])
    {
        rectfill(screen, pos, 265, pos+recWidth-1, 265, textColor);

        simulate_ukeypress(0x00DF, 0);
        val = ureadkey(&scancode);
        clear_keybuf();

        if(close_button_pressed)
        {
            return;
        }

        switch(val)
        {
            case 'a':
                printIt("a", "あ", 26, 0);
                stringShifts.push(1);
                charShifts.push(26);
                windowsPos++;
                break;
            case 'i':
                printIt("i", "い", 26, 0);
                stringShifts.push(1);
                charShifts.push(26);
                windowsPos++;
                break;
            case 'u':
                printIt("u", "う", 26, 0);
                stringShifts.push(1);
                charShifts.push(26);
                windowsPos++;
                break;
            case 'e':
                printIt("e", "え", 26, 0);
                stringShifts.push(1);
                charShifts.push(26);
                windowsPos++;
                break;
            case 'o':
                printIt("o", "お", 26, 0);
                stringShifts.push(1);
                charShifts.push(26);
                windowsPos++;
                break;
            case 'b':
                printIt("b", "b", 26, 0);
                //stringShifts.push(1);
                charShifts.push(26);
                val = ureadkey(&scancode);
                if(val == 'b')
                {
                    printIt("b", "っｂ", 48, 26);
                    stringShifts.push(2);
                    charShifts.push(21);
                    windowsPos++;
                    val = ureadkey(&scancode);
                    if(val == 'a')
                    {
                        printIt("a", "ば", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                        break;
                    }
                    else
                    {
                        if(val == 'i')
                        {
                            printIt("i", "び", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'u')
                            {
                                printIt("u", "ぶ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'e')
                                {
                                    printIt("e", "べ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'o')
                                    {
                                        printIt("o", "ぼ", 26, 26);
                                        stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                    }
                                    else
                                    {
                                        if(val == 'y')
                                        {
                                            printIt("y", "by", 26, 26);
                                            //stringShifts.push(2);
                                            charShifts.push(26);
                                            windowsPos++;
                                            val = ureadkey(&scancode);
                                            if(val == 'a')
                                            {
                                                printIt("a", "びゃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'i')
                                                {
                                                    printIt("i", "びぃ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'u')
                                                    {
                                                        printIt("u", "びゅ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'e')
                                                        {
                                                            printIt("e", "びぇ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                        else
                                                        {
                                                            if(val == 'o')
                                                            {
                                                                printIt("o", "びょ", 48, 26);
                                                                stringShifts.push(3);
                                                                charShifts.push(20.9);
                                                                windowsPos++;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(val == 'a')
                    {
                        printIt("a", "ば", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                        break;
                    }
                    else
                    {
                        if(val == 'i')
                        {
                            printIt("i", "び", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'u')
                            {
                                printIt("u", "ぶ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'e')
                                {
                                    printIt("e", "べ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'o')
                                    {
                                        printIt("o", "ぼ", 26, 26);
                                        stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                    }
                                    else
                                    {
                                        if(val == 'y')
                                        {
                                            printIt("y", "by", 26, 26);
                                            //stringShifts.push(2);
                                            charShifts.push(26);
                                            windowsPos++;
                                            val = ureadkey(&scancode);
                                            if(val == 'a')
                                            {
                                                printIt("a", "びゃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'i')
                                                {
                                                    printIt("i", "びぃ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'u')
                                                    {
                                                        printIt("u", "びゅ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'e')
                                                        {
                                                            printIt("e", "びぇ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                        else
                                                        {
                                                            if(val == 'o')
                                                            {
                                                                printIt("o", "びょ", 48, 26);
                                                                stringShifts.push(3);
                                                                charShifts.push(20.9);
                                                                windowsPos++;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 'h':
            printIt("h", "h", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'h')
            {
                printIt("h", "っh", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "は", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "ひ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ふ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "へ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ほ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "hy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "ひゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "ひぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "ひゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "ひぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "ひょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "は", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "ひ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ふ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "へ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ほ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "hy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "ひゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "ひぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "ひゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "ひぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "ひょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'p':
            printIt("p", "p", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'p')
            {
                printIt("p", "っp", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "`ぱ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "ぴ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ぷ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "ぺ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ぽ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "py", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "ぴゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "ぴぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "ぴゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "ぴぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "ぴょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "ぱ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "ぴ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ぷ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "ぺ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ぽ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "py", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "ぴゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "ぴぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "ぴゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "ぴぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "ぴょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'k':
            printIt("k", "k", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'k')
            {
                printIt("k", "っk", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "か", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "き", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "く", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "け", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "こ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "ky", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "きゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "きぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "きゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "きぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "きょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "か", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "き", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "く", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "け", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "こ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "ky", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "きゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "きぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "きゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "きぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "きょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'g':
            printIt("g", "g", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'g')
            {
                printIt("g", "っg", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "が", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "ぎ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ぐ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "げ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ご", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "gy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "ぎゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "ぎぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "ぎゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "ぎぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "ぎょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "が", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "ぎ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ぐ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "げ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ご", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "gy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "ぎゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "ぎぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "ぎゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "ぎぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "ぎょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 's':
            printIt("s", "s", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 's')
            {
                printIt("s", "っs", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "さ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("hi", "し", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "す", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "せ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "そ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'h')
                                    {
                                        printIt("h", "sh", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "しゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "し", 26, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "しゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "しぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "しょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "さ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("hi", "し", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "す", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "せ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "そ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'h')
                                    {
                                        printIt("h", "sh", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "しゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "し", 26, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "しゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "しぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "しょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'z':
            printIt("z", "z", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'z')
            {
                printIt("z", "っz", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "ざ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("ji", "じ", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ず", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "ぜ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ぞ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "zy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "じゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "じぃ", 26, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "じゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "じぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "じょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "ざ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("ji", "じ", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ず", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "ぜ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ぞ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "zy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "じゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "じぃ", 26, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "じゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "じぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "じょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'j':
            printIt("j", "j", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'j')
            {
                printIt("j", "っj", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "じゃ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "じ", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "じゅ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "じぇ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "じょ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("j", "jy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "じゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "じぃ", 26, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "じゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "じぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "じょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "じゃ", 48, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "じ", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "じゅ", 48, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "じぇ", 48, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "じょ", 48, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("j", "jy", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "じゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "じぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "じゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "じぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "じょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 't':
            printIt("t", "t", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 't')
            {
                printIt("t", "っt", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "た", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 's')
                    {
                        printIt("s", "ts", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                        val = ureadkey(&scancode);
                        if(val == 'u')
                        {
                            printIt("u", "つ", 26, 26);
                            stringShifts.push(3);
                            charShifts.push(26);
                        }
                    }
                    else
                    {
                        if(val == 'e')
                        {
                            printIt("e", "て", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'o')
                            {
                                printIt("o", "と", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "た", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 's')
                    {
                        printIt("s", "ts", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                        val = ureadkey(&scancode);
                        if(val == 'u')
                        {
                            printIt("u", "つ", 26, 48);
                            stringShifts.push(3);
                            charShifts.push(26);
                        }
                    }
                    else
                    {
                        if(val == 'e')
                        {
                            printIt("e", "て", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'o')
                            {
                                printIt("o", "と", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                        }
                    }
                }
            }
            break;
            case 'c':
            printIt("c", "c", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'c')
            {
                printIt("c", "っc", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'h')
                {
                    printIt("h", "ch", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    val = ureadkey(&scancode);
                    if(val == 'a')
                    {
                        printIt("a", "ちゃ", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'i')
                        {
                            printIt("i", "ち", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'u')
                            {
                                printIt("u", "ちゅ", 48, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ちょ", 48, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'h')
                {
                    printIt("h", "ch", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    val = ureadkey(&scancode);
                    if(val == 'a')
                    {
                        printIt("a", "ちゃ", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'i')
                        {
                            printIt("i", "ち", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'u')
                            {
                                printIt("u", "ちゅ", 48, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ちょ", 48, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'e')
                                    {
                                        printIt("e", "ちぇ", 48, 26);
                                        stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'd':
            printIt("d", "d", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'd')
            {
                printIt("d", "っd", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "だ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'u')
                    {
                        printIt("u", "づ", 26, 26);
                        stringShifts.push(3);
                        charShifts.push(26);
                    }
                    else
                    {
                        if(val == 'e')
                        {
                            printIt("e", "で", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'o')
                            {
                                printIt("o", "ど", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "だ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'u')
                    {
                        printIt("u", "づ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                    }
                    else
                    {
                        if(val == 'e')
                        {
                            printIt("e", "で", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'o')
                            {
                                printIt("o", "ど", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                        }
                    }
                }
            }
            break;
            case 'f':
            printIt("f", "f", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'f')
            {
                printIt("f", "っf", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'y')
                {
                    printIt("y", "fy", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    val = ureadkey(&scancode);
                    if(val == 'a')
                    {
                        printIt("a", "ふゃ", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                        break;
                    }
                }
                else
                {
                    if(val == 'a')
                    {
                        printIt("a", "ふぁ", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                    }
                    else
                    {
                        if(val == 'i')
                        {
                            printIt("i", "ふぃ", 48, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                        }
                        else
                        {
                            if(val == 'u')
                            {
                                printIt("u", "ふ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                            }
                            else
                            {
                                if(val == 'e')
                                {
                                    printIt("e", "ふぇ", 48, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                }
                                else
                                {
                                    if(val == 'o')
                                    {
                                        printIt("o", "ふぉ", 48, 26);
                                        stringShifts.push(2);
                                        charShifts.push(26);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'y')
                {
                    printIt("y", "fy", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    val = ureadkey(&scancode);
                    if(val == 'a')
                    {
                        printIt("a", "ふゃ", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                        break;
                    }
                }
                else
                {
                    if(val == 'a')
                    {
                        printIt("a", "ふぁ", 48, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                    }
                    else
                    {
                        if(val == 'i')
                        {
                            printIt("i", "ふぃ", 48, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                        }
                        else
                        {
                            if(val == 'u')
                            {
                                printIt("u", "ふ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                            }
                            else
                            {
                                if(val == 'e')
                                {
                                    printIt("e", "ふぇ", 48, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                }
                                else
                                {
                                    if(val == 'o')
                                    {
                                        printIt("o", "ふぉ", 48, 26);
                                        stringShifts.push(2);
                                        charShifts.push(26);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'r':
            printIt("r", "r", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'r')
            {
                printIt("r", "っr", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "ら", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "り", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "る", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "れ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ろ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "ry", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "りゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "りぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "りゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "りぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "りょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "ら", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "り", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "る", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "れ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "ろ", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "ry", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "りゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "りぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "りゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "りぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "りょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'm':
            printIt("m", "m", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'm')
            {
                printIt("m", "っm", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "ま", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "み", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "む", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "め", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "も", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "my", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "みゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "みぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                                else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "みゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "みぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "みょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "ま", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "み", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "む", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "め", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "も", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "my", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "みゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "みぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "みゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "みぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "みょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'n':
            printIt("n", "n", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'n')
            {
                printIt("", "ん", 26, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "な", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'i')
                    {
                        printIt("i", "に", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'u')
                        {
                            printIt("u", "ぬ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                        else
                        {
                            if(val == 'e')
                            {
                                printIt("e", "ね", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                            else
                            {
                                if(val == 'o')
                                {
                                    printIt("o", "の", 26, 26);
                                    stringShifts.push(2);
                                    charShifts.push(26);
                                    windowsPos++;
                                }
                                else
                                {
                                    if(val == 'y')
                                    {
                                        printIt("y", "ny", 26, 26);
                                        //stringShifts.push(2);
                                        charShifts.push(26);
                                        windowsPos++;
                                        val = ureadkey(&scancode);
                                        if(val == 'a')
                                        {
                                            printIt("a", "にゃ", 48, 26);
                                            stringShifts.push(3);
                                            charShifts.push(20.9);
                                            windowsPos++;
                                        }
                                        else
                                        {
                                            if(val == 'i')
                                            {
                                                printIt("i", "にぃ", 48, 26);
                                                stringShifts.push(3);
                                                charShifts.push(20.9);
                                                windowsPos++;
                                            }
                                            else
                                            {
                                                if(val == 'u')
                                                {
                                                    printIt("u", "にゅ", 48, 26);
                                                    stringShifts.push(3);
                                                    charShifts.push(20.9);
                                                    windowsPos++;
                                                }
                                                else
                                                {
                                                    if(val == 'e')
                                                    {
                                                        printIt("e", "にぇ", 48, 26);
                                                        stringShifts.push(3);
                                                        charShifts.push(20.9);
                                                        windowsPos++;
                                                    }
                                                    else
                                                    {
                                                        if(val == 'o')
                                                        {
                                                            printIt("o", "にょ", 48, 26);
                                                            stringShifts.push(3);
                                                            charShifts.push(20.9);
                                                            windowsPos++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
            case 'w':
            printIt("w", "w", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'w')
            {
                printIt("w", "ww", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "っわ", 48, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "わ", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'o')
                    {
                        printIt("o", "を", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                }
            }
            break;
            case 'y':
            printIt("y", "y", 26, 0);
            //stringShifts.push(1);
            charShifts.push(26);
            val = ureadkey(&scancode);
            if(val == 'y')
            {
                printIt("y", "っy", 48, 26);
                stringShifts.push(2);
                charShifts.push(21);
                windowsPos++;
                val = ureadkey(&scancode);
                if(val == 'a')
                {
                    printIt("a", "や", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'u')
                    {
                        printIt("u", "ゆ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                    else
                    {
                        if(val == 'o')
                        {
                            printIt("o", "よ", 26, 26);
                            stringShifts.push(2);
                            charShifts.push(26);
                            windowsPos++;
                        }
                    }
                }
            }
            else
            {
                if(val == 'a')
                {
                    printIt("a", "や", 26, 26);
                    stringShifts.push(2);
                    charShifts.push(26);
                    windowsPos++;
                    break;
                }
                else
                {
                    if(val == 'u')
                    {
                        printIt("u", "ゆ", 26, 26);
                        stringShifts.push(2);
                        charShifts.push(26);
                        windowsPos++;
                    }
                        else
                        {
                            if(val == 'o')
                            {
                                printIt("o", "よ", 26, 26);
                                stringShifts.push(2);
                                charShifts.push(26);
                                windowsPos++;
                            }
                        }
                }
            }
            break;
            case 8:
                romajiInput = "";
                masked_blit(temp, screen, 0, 0, 0, 0, screen->w, screen->h);
                pos = x;
                //Incomplete code that makes hitting backspace only remove one character.
                /**if(windowsPos > 0)
                {
                    windowsPos--;
                    pos-=charShifts.top();
                    charShifts.pop();
                    masked_blit(temp, screen, pos, y, pos, y, recWidth, recHeight);
                    if(romajiInput.size()!=0)
                    {
                        if(stringShifts.top() == 3 && romajiInput.substr(romajiInput.size()-3, romajiInput.size()).compare("shi") != 0)
                        {
                            if(romajiInput.substr(romajiInput.size()-3, romajiInput.size()-1).compare("sh") == 0)
                            {
                                romajiInput = romajiInput.substr(0, romajiInput.size()-2) + "hi";
                                stringShifts.pop();
                                stringShifts.push(3);
                            }
                            else
                            {
                                romajiInput = romajiInput.substr(0, romajiInput.size()-2) + "i";
                                stringShifts.pop();
                                stringShifts.push(2);
                            }
                        }
                        else
                        {
                            romajiInput = romajiInput.substr(0, romajiInput.size()-stringShifts.top());
                            stringShifts.pop();
                        }
                    }
                }**/
                break;

            case 13:
                return;
            case 27:
                return;
            case 32:
                return;
        }
        cout << romajiInput << endl;
    }
}
void TextField::printIt(const char* romaji, const char* hiragana, int shiftR, int shiftL)
{
    if(pos < 580)
    {
        romajiInput+=romaji;
        pos-=shiftL;
        masked_blit(temp, screen, pos, y, pos, y, recWidth, recHeight);
        alfont_textout(screen, font, hiragana, pos, y, textColor);
        pos+=shiftR;
    }
}

//used to check the user's input in romaji.
string TextField::getRomaji()
{
    return romajiInput;
}
