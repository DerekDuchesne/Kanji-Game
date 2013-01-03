#include <alfont.h>
#include <allegro.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <winalleg.h>
#include <dirent.h>
#include <stdio.h>
#include <deque>
#include <iomanip>
#include <locale>
#include <sstream>
#include "TextField.h"
#include "CloseHandler.h"
#define ID_EDIT 1

using namespace std;


//========================
//Poorly Written functions
//========================
void setup();
void generateList();
void load_images();
void load_music();
void play();
void cleanup();
void switchBackground();
void switchMusic();
void drawTitleScreen(ALFONT_FONT* font, BITMAP* logo);
void drawSelectionScreen(ALFONT_FONT* font, BITMAP* cursor, int cursorPosition);
int drawReadingScreen(BITMAP* sprite, BITMAP* window, BITMAP* textbox, ALFONT_FONT* font, int max, int xcor, string secret);
void drawReadingExplanationScreen(BITMAP* sprite, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int xcor);
int drawWritingScreen(BITMAP* sprite2, BITMAP* window, BITMAP* textbox, ALFONT_FONT* font, int max, int xcor, string secret);
void drawWritingExplanationScreen(BITMAP* sprite2, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int xcor);
void drawCompleteReadingScreen(BITMAP* sprite, BITMAP* window, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int max, int xcor, string secret);
void drawCompleteWritingScreen(BITMAP* sprite, BITMAP* window, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int max, int xcor, string secret);
void fade_in(BITMAP* bmp, int x, int y, int speed);
void fade_in_with(BITMAP* bmp, BITMAP* extra, int x, int y, int ex, int ey, int speed);
void scrollText(ALFONT_FONT* font, const char* message, int x, int y, int color);
bool scrollTextCursor(ALFONT_FONT* font, BITMAP* textCursor, BITMAP* textBox, const char* message, int x, int y, int color);
void flashText(ALFONT_FONT* font, const char* message, BITMAP* background, int x, int y, int color);
void close_button_handler();

//=====================
//Poorly-made variables
//=====================
int wordTotal = 0;
//volatile int close_button_pressed = FALSE;
vector<string> imageFiles;
vector<string> musicFiles;
vector<string> kanji;
vector<string> pronunciation;
vector<string> meaning;
vector<string> hiragana;
deque<string> backgrounds;
deque<string> music;
deque<string>  kanjiDeque;
deque<string> pronunciationDeque;
deque<string> meaningDeque;
deque<string> hiraganaDeque;
BITMAP* currentBackground;
SAMPLE* currentMusic;

int main()
{
    setup();
    if(!close_button_pressed)
    play();
    cleanup();
    return 0;
}
END_OF_MAIN()

//initiliazes Allegro and loads backgrounds and music files, storing them in randomized order.
void setup()
{
    //sets up Allegro to be compatible with Unicode
    set_uformat(U_UTF8);
    allegro_init();
    //allows the close button to appear and be usuable.
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);
    //initialize alfont, Allegro's font addon.
    alfont_init();
    //installs mouse, keyboard, and sound functions for Allegro
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_volume(255, 255);
    //sets up all the graphics stuff.
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0);
    //lets the mouse be shown onscreen.
    show_os_cursor(MOUSE_CURSOR_ALLEGRO);
    //makes the music still play when the window is inactive (it would be INCREDIBLY
    //annoying without this because the music would just repeat the same note when inactive).
    set_display_switch_mode(SWITCH_BACKGROUND);

    //loads the font for the loading screen.
    ALFONT_FONT* font = alfont_load_font("sazanami-gothic.ttf");
    alfont_set_font_size(font, 30);
    alfont_textout(screen, font, "Loadering...", 0, 0, makecol(255, 255, 255));
    alfont_destroy_font(font);
    //gets a list of the background filenames.
    load_images();
    //gets a list of the music filenames.
    load_music();
    //the random index that each of the four vocabulary lists are randomized with. there's only one
    //so that pronunciation matches with the kanji, which matches with the hiragana, etc.
    int randomIndex;
    //needed for randomization
    srand ( time(NULL) );

    //the loop that starts loading image files.
    while(!imageFiles.empty() && !close_button_pressed)
    {
        //generates a random number.
        randomIndex = rand() % imageFiles.size();
        //loads the background with the given filename into backgrounds and deletes it from imageFiles.
        backgrounds.push_front("Images/Backgrounds/" + imageFiles[randomIndex]);
        imageFiles.erase(imageFiles.begin()+randomIndex);
    }
    //while there are more music files.
    while(!musicFiles.empty() && !close_button_pressed)
    {
        //generates a valid random number.
        randomIndex = rand() % musicFiles.size();
        //loads the music with the given filename into music and deletes it from musicFiles.
        music.push_front("Music/" + musicFiles[randomIndex]);
        musicFiles.erase(musicFiles.begin()+randomIndex);
    }
    //handles the parsing, randomization, and queueing of the vocabulary text files..
    generateList();
}

//opens the kanji.txt, prounciation.txt, meaning.txt, and hiragana.txt files, puts them each
//in their own vectors, and then puts them each in deques in random order. this is called whenever
//each mode ends or the player returns to the main menu.
void generateList()
{
    //makes sure the list is empty before trying to generate a new one.
    while(!kanjiDeque.empty())
    {
        kanjiDeque.pop_front();
    }
    while(!pronunciationDeque.empty())
    {
        pronunciationDeque.pop_front();
    }
    while(!meaningDeque.empty())
    {
        meaningDeque.pop_front();
    }
    while(!hiraganaDeque.empty())
    {
        hiraganaDeque.pop_front();
    }
    //the list is now empty.
    wordTotal = 0;
    //the single random index number that allows each of the text files to correspond correctly
    int randomIndex;
    //Needed for randomization
    srand ( time(NULL) );
    //opens input streams for all of the text files.
    ifstream kanjiList;
    kanjiList.open("Text/kanji.txt");
    ifstream pronunciationList;
    pronunciationList.open("Text/pronunciation.txt");
    ifstream meaningList;
    meaningList.open("Text/meaning.txt");
    ifstream hiraganaList;
    hiraganaList.open("Text/hiragana.txt");
    //while each list still has words, take out each a line at a time and put it in a vector.
    while(kanjiList.good() && !close_button_pressed)
    {
        string line;
        getline(kanjiList, line);
        kanji.push_back(line);
        //all the lists should have the same amount, so the wordTotal is only calculated from
        //the kanji text file.
        wordTotal++;
    }
    kanjiList.close();
    while(pronunciationList.good() && !close_button_pressed)
    {
        string line;
        getline(pronunciationList, line);
        pronunciation.push_back(line);
    }
    pronunciationList.close();
    while(meaningList.good() && !close_button_pressed)
    {
        string line;
        getline(meaningList, line);
        meaning.push_back(line);
    }
    meaningList.close();
    while(hiraganaList.good() && !close_button_pressed)
    {
        string line;
        getline(hiraganaList, line);
        hiragana.push_back(line);
    }
    hiraganaList.close();
    //this is the part where all of the words get randomized and put into deques.
    while(!kanji.empty() && !close_button_pressed)
    {
        //Generate a valid random number.
        randomIndex = rand() % kanji.size();
        //Load the music with the given filename into music and delete it from musicFiles.
        kanjiDeque.push_front(kanji[randomIndex]);
        kanji.erase(kanji.begin()+randomIndex);
        pronunciationDeque.push_front(pronunciation[randomIndex]);
        pronunciation.erase(pronunciation.begin()+randomIndex);
        meaningDeque.push_front(meaning[randomIndex]);
        meaning.erase(meaning.begin()+randomIndex);
        hiraganaDeque.push_front(hiragana[randomIndex]);
        hiragana.erase(hiragana.begin()+randomIndex);
    }
}

//get a list of background filenames. only the filenames are needed because the only time the
//actual images are loaded is the moment they need to be displayed.
void load_images()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir("./Images/Backgrounds");
    while ((ent = readdir (dir)) != NULL && !close_button_pressed)
    {
        if(strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0)
        {
            imageFiles.push_back(ent->d_name);
        }
    }
    closedir (dir);
}

//gets a list of music filenames.
void load_music()
{
    DIR *dir2;
    struct dirent *ent2;
    dir2 = opendir ("./Music");
    while ((ent2 = readdir (dir2)) != NULL && !close_button_pressed)
    {
        if(strcmp(ent2->d_name,".") != 0 && strcmp(ent2->d_name,"..") != 0)
        {
            musicFiles.push_back(ent2->d_name);
        }
    }
    closedir (dir2);
}

//actually runs the game.
void play()
{
    //initializes the starting background and music.
    currentBackground = load_bitmap(backgrounds.front().c_str(),NULL);
    currentMusic = load_sample(music.front().c_str());
    //loads the title logo and character silhouettes
    BITMAP* title = load_bitmap("Images/Kanji_Title.bmp", NULL);
    BITMAP* degozarusil = load_bitmap("Images/Characters/DegozaruSil.bmp", NULL);
    BITMAP* cakesil = load_bitmap("Images/Characters/KekihimeSil.bmp", NULL);
    //loads the text font.
    ALFONT_FONT* font = alfont_load_font("sazanami-gothic.ttf");
    alfont_set_font_size(font, 30);
    //plays the music for the title screen.
    play_sample(currentMusic, 255, 155, 1000, 1);
    //make the title appear and do the scrolling text animation.
    drawTitleScreen(font, title);
    //loads the title sound effect.
    SAMPLE* titleSound = load_sample("Sounds/FF7CursorBack.wav");
    //keeps track of how many times the background has changed. at 50, the words from the installed vocab list will appear on screen
    //in random places.
    int backgroundCounter = 0;
    const char* startText = "何でもいいキーを押してください";
    //keeps looping to see if any key is being pressed to get past the title screen.
    int x = 0;
    int y = 0;
    int choice = 0;
    while(!keypressed() && !close_button_pressed)
    {
        alfont_set_font_size(font, 30);
        //changes the current background and places the old one in the back of the deque.
        backgrounds.push_back(backgrounds.front());
        backgrounds.pop_front();
        destroy_bitmap(currentBackground);
        currentBackground = load_bitmap(backgrounds.front().c_str(), NULL);
        //fades in the new background.
        fade_in_with(currentBackground, title, 0, 0, 30, 20, 40);
        //flashes the starting text.
        flashText(font, startText, currentBackground, 150, 310, makecol(255, 255, 255));
        //checks to see when 50 backgrounds have been displayed.
        if(backgroundCounter == 50)
        {
            alfont_set_font_size(font, 15);
            //puts 20 copies off the same vocabulary word in random places on screen. because.
            for(int i = 0; i < 20; i++)
            {
                x = rand() % 450 + 50;
                y = rand() % 400  + 20;
                alfont_textout(screen, font, kanjiDeque.front().c_str(), x, y, makecol(100, 255, 100));
            }
            choice = rand() % 2;
            if(choice == 0)
            {
                fade_in(degozarusil, x, 290, 10);
            }
            else
            {
                fade_in(cakesil, x, 310, 10);
            }
            //moves on to the next vocab word.
            kanjiDeque.push_back(kanjiDeque.front());
            kanjiDeque.pop_front();
            pronunciationDeque.push_back(pronunciationDeque.front());
            pronunciationDeque.pop_front();
            hiraganaDeque.push_back(hiraganaDeque.front());
            hiraganaDeque.pop_front();
            meaningDeque.push_back(meaningDeque.front());
            meaningDeque.pop_front();
        }
        //doesn't bother with the counter once it's reached 50.
        if(backgroundCounter != 50)
        {
            backgroundCounter++;
        }
        rest(60);
    }
    destroy_bitmap(degozarusil);
    destroy_bitmap(cakesil);
    //checks if the close button is pressed again.
    if(!close_button_pressed)
    {
        play_sample(titleSound, 255, 155, 1000, 0);
    }
    //frees the title logo's memory and the title sound.
    destroy_bitmap(title);
    //switches the music but not the background.
    switchMusic();
    //the default cursor position on screen.
    int cursorPosition = 40;
    //load the cursor and cursor move sounds.
    BITMAP* cursor = load_bitmap("Images/Cursor.bmp", NULL);
    SAMPLE* cursorMove = load_sample("Sounds/FF7CursorMove.wav");
    bool previous = true;
    while(previous == true && !close_button_pressed)
    {
        //this is here to generate a new list whenever the player returns to the selection screen.
        generateList();
        if(!close_button_pressed)
        {
            drawSelectionScreen(font, cursor, cursorPosition);
        }
        //gotta clear the key buffer to make sure that if the player pressed Enter, that it won't hold that input for long enough to overshoot
        //the selection menu.
        clear_keybuf();
        //checks if the user hit enter to progress to the two main modes of the game.
        while(!key[KEY_ENTER] && !key[KEY_ENTER_PAD] && !close_button_pressed)
        {
            //if the user hit the up key.
            if(key[KEY_UP])
            {
                //play the sound sample.
                play_sample(cursorMove, 255, 155, 1000, 0);
                rest(200);
                //move the cursor position (it'll stay in the same spot if it was already at 40).
                cursorPosition = 40;
                //reapply the background to the screen so that the cursor appears to have moved.
                blit(currentBackground, screen, 150, 90, 150, 90, cursor->w, cursor->h);
                //put the cursor at its new location.
                masked_blit(cursor, screen, 0, 0, 150, cursorPosition, cursor->w, cursor->h);
            }
            else
            {
                //same thing as if the user hit the up key except the cursor's location will be different.
                if(key[KEY_DOWN])
                {
                    play_sample(cursorMove, 255, 155, 1000, 0);
                    rest(200);
                    cursorPosition = 90;
                    blit(currentBackground, screen, 150, 40, 150, 40, cursor->w, cursor->h);
                    masked_blit(cursor, screen, 0, 0, 150, cursorPosition, cursor->w, cursor->h);
                }
            }
        }
        //loads the graphics shared between both the reading and writing modes.
        BITMAP* window = load_bitmap("Images/Window1.bmp", NULL);
        BITMAP* textbox = load_bitmap("Images/Textbox.bmp", NULL);
        BITMAP* textCursor = load_bitmap("Images/TextCursor.bmp", NULL);
        //keeps track of the max combo for each session.
        int maxCombo;
        //switches the background and music again.
        switchBackground();
        switchMusic();

        int xcor = 0;
        string secret = "";
        if(cursorPosition == 40 && !close_button_pressed)
        {
            BITMAP* sprite;
            if(maxCombo >= 100 && maxCombo < 150)
            {
                sprite = load_bitmap("Images/Characters/Degozaru.bmp", NULL);
                xcor = 450;
                secret = "degozaru";
            }
            else
            {
                if(maxCombo >= 150)
                {
                    sprite = load_bitmap("Images/Characters/Kekihime.bmp", NULL);
                    xcor = 380;
                    secret = "kekihime";
                }
                else
                {
                    sprite = load_bitmap("Images/Characters/Neco_Arc_Chaos.bmp", NULL);
                    xcor = 450;
                }
            }
            //reading practice
            drawReadingExplanationScreen(sprite, textCursor, textbox, font, xcor);
            maxCombo = 0;
            if(!close_button_pressed)
            {
                maxCombo = drawReadingScreen(sprite, window, textbox, font, maxCombo, xcor, secret);
            }
            if(maxCombo != -1 && !close_button_pressed)
            {
                drawCompleteReadingScreen(sprite, window, textCursor, textbox, font, maxCombo, xcor, secret);
            }
            previous = true;
            destroy_bitmap(sprite);
        }
        //writing practice
        else
        {
            if(cursorPosition == 90 && !close_button_pressed)
            {
                BITMAP* sprite2;
               if(maxCombo >= 100 && maxCombo < 150)
                {
                    sprite2 = load_bitmap("Images/Characters/Degozaru.bmp", NULL);
                    xcor = 450;
                    secret = "degozaru";
                }
                else
                {
                    if(maxCombo >= 150)
                    {
                        sprite2 = load_bitmap("Images/Characters/Kekihime.bmp", NULL);
                        xcor = 380;
                        secret = "kekihime";
                    }
                    else
                    {
                        sprite2 = load_bitmap("Images/Characters/Kohaku.bmp", NULL);
                        xcor = 450;
                    }
                }
                drawWritingExplanationScreen(sprite2, textCursor, textbox, font, xcor);
                maxCombo = 0;
                if(!close_button_pressed)
                {
                   maxCombo = drawWritingScreen(sprite2, window, textbox, font, maxCombo, xcor, secret);
                }
                if(maxCombo != -1 && !close_button_pressed)
                {
                    drawCompleteWritingScreen(sprite2, window, textCursor, textbox, font, maxCombo, xcor, secret);
                }
                previous = true;
                destroy_bitmap(sprite2);
            }
        }
        destroy_bitmap(textCursor);
        destroy_bitmap(window);
        destroy_bitmap(textbox);
    }
    destroy_sample(cursorMove);
    destroy_bitmap(cursor);
    alfont_destroy_font(font);
    destroy_sample(titleSound);
}

//deletes all pointers and prevent memory leaks (theoretically -_-).
void cleanup()
{
    for(int i = 0; i < (int)backgrounds.size(); i++)
    {
        backgrounds.pop_front();
    }
    for(int i = 0; i < (int)music.size(); i++)
    {
        music.pop_front();
    }
    destroy_bitmap(currentBackground);
    destroy_sample(currentMusic);
}

void switchBackground()
{
    backgrounds.push_back(backgrounds.front());
    backgrounds.pop_front();
    destroy_bitmap(currentBackground);
    currentBackground = load_bitmap(backgrounds.front().c_str(), NULL);
    blit(currentBackground, screen, 0, 0, 0, 0, currentBackground->w, currentBackground->h);
}

void switchMusic()
{
    stop_sample(currentMusic);
    destroy_sample(currentMusic);
    music.push_back(music.front());
    music.pop_front();
    currentMusic = load_sample(music.front().c_str());
    play_sample(currentMusic, 255, 155, 1000, 1);
}

//fades in the given bmp onto the given background at the given coordinates and at the given speed.
void fade_in(BITMAP* bmp, int x, int y, int speed)
{
    for (int i = 0; i < 256; i+=speed)
    {
        set_trans_blender(0,0,0,i);
        draw_trans_sprite(screen, bmp, x, y);
    }
}

//does the same thing as fade_in, except there is a third bmp included.
void fade_in_with(BITMAP* bmp, BITMAP* extra, int x, int y, int ex, int ey, int speed)
{
    for (int i = 0; i < 256; i+=speed)
    {
        set_trans_blender(0,0,0,i);
        draw_trans_sprite(screen, bmp, x, y);
        masked_blit(extra, screen, 0, 0, ex, ey, extra->w, extra -> h);
    }
}

//displays the title logo, background, and handles the scrolling animation on the start text.
void drawTitleScreen(ALFONT_FONT* font, BITMAP* logo)
{
    //Blits the current background onto the screen.
    blit(currentBackground, screen, 0,0,0,0, currentBackground->w, currentBackground->h);
    //fades in the title logo to the screen.
    fade_in(logo, 30, 20, 10);
    //scrolls the starting text.
    const char* startText = "何でもいいキーを押してください";
    scrollText(font, startText, 150, 310, makecol(255, 255, 255));
}

//draws the selection screen with the cursor at the given psoition.
void drawSelectionScreen(ALFONT_FONT* font, BITMAP* cursor, int cursorPosition)
{
    alfont_set_font_size(font, 30);
    blit(currentBackground, screen, 0,0,0,0, currentBackground->w, currentBackground->h);
    masked_blit(cursor, screen, 0, 0, 150, cursorPosition, cursor->w, cursor->h);
    alfont_textout(screen, font, "読む練習", 40, 40, makecol(255, 255, 255));
    alfont_textout(screen, font, "書く練習", 40, 90, makecol(255, 255, 255));
}

//explains the rules of the reading practice game.
void drawReadingExplanationScreen(BITMAP* sprite, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int xcor)
{
    //loads a clean current background again that doesn't have the other graphics still attached to it.
    masked_blit(sprite, screen, 0, 0, xcor, 280, sprite->w, sprite->h);
    alfont_textout(screen, font, "「スペースでスキップできます」", 140, 90, makecol(255, 255, 255));
    //displays all the dialogue for the reading explanation screen.
    if(scrollTextCursor(font, textCursor, textbox, "読む練習ゲームへようこそ！", 38, 320, makecol(0, 0, 0)))
    {
        if(scrollTextCursor(font, textCursor, textbox, "このモードは漢字の読み方の練習ためです。", 38, 320, makecol(0, 0, 0)))
        {
            if(scrollTextCursor(font, textCursor, textbox, "ゲームのもくてきは単語リストを空にすることです。", 38, 320, makecol(0,0,0)))
            {
                if(scrollTextCursor(font, textCursor, textbox, "それをするにはファストトライで正しく読みます。ファストトライならその単語は消えます。", 38, 320, makecol(0,0,0)))
                {
                    if(scrollTextCursor(font, textCursor, textbox, "単語は出て、あなたはひらがなで読み方をタイプしてエンターキーを押す。 正しいかどうかプログラムはチェックします。", 38, 320, makecol(0,0,0)))
                    {
                        if(scrollTextCursor(font, textCursor, textbox, "答えは正しいなら、次の単語は出て、コンボ(BEATS)は上る。間違いなら、コンボはゼロに変わります。", 38, 320, makecol(0, 0, 0)))
                        {
                            if(scrollTextCursor(font, textCursor, textbox, "30BEATSまで行けるならイメージと音楽は変わります。", 38, 320, makecol(0,0,0)))
                            {
                                if(scrollTextCursor(font, textCursor, textbox, "単語も、イメージも、音楽も、ぜんぶランダムです。", 38, 320, makecol(0, 0, 0)))
                                {
                                    if(scrollTextCursor(font, textCursor, textbox, "漢字が読めないならスペスーキーで読み方と意味が見えます。でも、これを使えばコンボはゼロに変わってその単語は消えません！", 38, 320, makecol(0, 0,0)))
                                    {
                                        if(scrollTextCursor(font, textCursor, textbox, "さて、じゅんびがいいならゲームを始めましょうか？", 38, 320, makecol(0, 0, 0)))
                                        {

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

/**int silence_g_key(int key, int *scancode)
      {
         if (key == 'a') {
             scancode = 0;
             return ureadkey();
            simulate_ukeypress(ureadkey(&scancode), 0);
         }
         return key;
      } END_OF_FUNCTION(silence_g_key)**/


//does the whole reading practice game.
int drawReadingScreen(BITMAP* sprite, BITMAP* window, BITMAP* textbox, ALFONT_FONT* font, int maxCombo, int xcor, string secret)
{
    //clears the keybuf again so that the 'Enter' confirmations from the instrunctions don't accidentally trigger a wrong answer.
    clear_keybuf();
    //keyboard_ucallback = silence_g_key;
    //loads all the sound effects.
    SAMPLE* correctAnswer = load_sample("Sounds/FF7SaveLoad.wav");
    SAMPLE* wrongAnswer = load_sample("Sounds/FF7CursorError.wav");
    SAMPLE* fiftyRight = load_sample("Sounds/GeeseHowardTooEasy.wav");
    //the current combo.
    int combo = 0;
    //the number of words that were eliminated on the first try.
    int correctNum = 0;
    //a string for displaying the combos.
    string beats;
    //determines if the answer was correct or not.
    bool correct = false;
    //the input string that the user will type the word pronunciations in.
    //char inputString[256] = "ここでテキストを入れるのことができます";
    string inputString;
    //the construnction of the dialogue box for user input.
    //Allegro's built-in dialog box was not used.
    /**DIALOG input[] =
    {
        {
            d_edit_proc, 50, 250, 450, 1, makecol(255, 255, 255), makecol(0, 0, 0), 0, 0, 60, 0, inputString,  NULL, NULL
        },
        {
            NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL
        }
    };
    DIALOG_PLAYER* dPlayer;**/
    //different text variables for dialogue, each displayed on a different line.
    const char* text1 = "";
    const char* text2 = "";
    const char* text3 = "";
    const char* text4 = "";

    if(secret.compare("degozaru") == 0)
    {
        text1 = "拙者はデゴザルでござる！";
        text2 = "おはようでござる！？";
        text3 = "";
        text4 = "";
    }
    else
    {
        if(secret.compare("kekihime") == 0)
        {
            text1 = "私をケーキ姫と呼んでいい。";
            text2 = "よろしくね。";
            text3 = "";
            text4 = "";
        }
        else
        {
            text1 = "しんぱいしにゃい。君にゃらできる気がする。";
            text2 = "うん、たぶん。";
            text3 = "";
            text4 = "";
        }
    }
    stringstream sstr;
    string str;
    //tells whether or not to play the wrongAnswer sound effect. this wouldn't play in the case of the user hitting 'Space' to check to see
    //what the pronunciation is.
    bool dontplay = false;
    //determines if the correctNum variable should go up or not.
    bool firstTry = true;
    set_trans_blender(0,0,0,180);
    while(!close_button_pressed)
    {
        sstr.str("");
        sstr.clear();
        sstr << correctNum << "/" << wordTotal;
        str = "ステイタス: " + sstr.str();
        text3 = str.c_str();
        dontplay = false;
        blit(currentBackground, screen, 0, 0, 0, 0, currentBackground->w, currentBackground->h);
        alfont_set_font_size(font, 20);
        alfont_textout(screen, font, "ESCでメインメニュに戻れます", 270, 20, makecol(255, 255, 255));
        masked_blit(sprite, screen, 0, 0, xcor, 280, sprite->w, sprite->h);
        masked_blit(textbox, screen, 0, 0, 20, 310, textbox->w, textbox->h);
        draw_trans_sprite(screen, window, 30, 60);
        draw_trans_sprite(screen, window, 30, 200);
        alfont_set_font_size(font, 38);
        beats = static_cast<ostringstream*>( &(ostringstream() << combo) )->str();
        beats = "BEATS: " + beats;
        alfont_textout(screen, font, beats.c_str(), 109, 19, makecol(255, 255, 255));
        alfont_textout(screen, font, beats.c_str(), 110, 20, makecol(0, 0, 0));
        scrollText(font, kanjiDeque.front().c_str(), 50, 90, makecol(255, 255, 255));
        alfont_set_font_size(font, 25);
        scrollText(font, text1, 32, 320, makecol(0, 0, 0));
        scrollText(font, text2, 32, 355, makecol(0, 0, 0));
        scrollText(font, text3, 32, 390, makecol(24, 131, 56));
        scrollText(font, text4, 32, 420, makecol(24, 131, 56));
        alfont_set_font_size(font, 30);
        //int val, scancode, pos=40;
        while(!key[KEY_ENTER] && !key[KEY_ENTER_PAD] && !key[KEY_SPACE] && !key[KEY_ESC] && !close_button_pressed)
        {
            //More Allegro dialog unused stuff
            //if(key[KEY_TAB])
            //{
              //  dPlayer = init_dialog(input, 0);
               // update_dialog(dPlayer);
                //shutdown_dialog(dPlayer);
            //}
            //else
            //{
                TextField field(40, 235, makecol(255, 255, 255), screen, screen, font);
                field.getInput();
                inputString = field.getRomaji();
                //Testing.
                cout << "This is the input string: " << inputString << endl;
            //}

        }
        if(key[KEY_ESC])
        {
            destroy_sample(correctAnswer);
            destroy_sample(wrongAnswer);
            destroy_sample(fiftyRight);
            switchBackground();
            switchMusic();
            return -1;
        }
        if(key[KEY_SPACE])
        {
            text1 = pronunciationDeque.front().c_str();
            text2 = meaningDeque.front().c_str();
            dontplay = true;
            firstTry = false;
        }
        else
        {
            text4 = "";
        }
        if(((string)inputString).compare(pronunciationDeque.front()) == 0)
        {
            if(combo % 50 == 0 && combo!= 500 && combo!= 0)
            {
                play_sample(fiftyRight, 255, 155, 1000, 0);
            }
            else
            {
                play_sample(correctAnswer, 255, 155, 1000, 0);
                if(combo % 30 == 0 && combo != 0)
                {
                    switchBackground();
                    switchMusic();
                    masked_blit(sprite, screen, 0, 0, xcor, 280, sprite->w, sprite->h);
                    masked_blit(textbox, screen, 0, 0, 20, 310, textbox->w, textbox->h);
                }
            }
            correct = true;
        }
        if(correct)
        {
            if(secret.compare("degozaru") == 0)
            {
                text1 = "お見事でござった！ そちはわざを";
                text2 = "みがいているそうでござる！";
            }
            else
            {
                if(secret.compare("kekihime") == 0)
                {
                    text1 = "ほーほ～。ケーキーの本の力が";
                    text2 = "もう分かったか？";
                }
                else
                {
                    text1 = "よし、もんだいにゃし。バーテン！でっかい";
                    text2 = "魚をください！うん、これでいい。";
                }
            }
            combo++;
            if(maxCombo <= combo)
            {
                maxCombo = combo;
            }
            if(kanjiDeque.size() == 1)
            {
                return maxCombo;
            }
            if(!firstTry)
            {
                kanjiDeque.push_back(kanjiDeque.front());
            }
            kanjiDeque.pop_front();
            if(!firstTry)
            {
                pronunciationDeque.push_back(pronunciationDeque.front());
            }
            pronunciationDeque.pop_front();
            if(!firstTry)
            {
                hiraganaDeque.push_back(hiraganaDeque.front());
            }
            hiraganaDeque.pop_front();
            if(!firstTry)
            {
                meaningDeque.push_back(meaningDeque.front());
            }
            meaningDeque.pop_front();
            if(firstTry)
            {
                correctNum++;
            }
            firstTry = true;
        }
        else
        {
            firstTry = false;
            if(dontplay == false)
            {
                play_sample(wrongAnswer, 255, 155, 1000, 0);
                if(secret.compare("degozaru") == 0)
                {
                    text1 = "御用でござる！このデゴザルはそちに";
                    text2 = "その言葉についてもう一度聞かせてもらうよ！";
                }
                else
                {
                    if(secret.compare("kekihime") == 0)
                    {
                        text1 = "え？もしかして、おなかついている？";
                        text2 = "それなら．．．．．．．．．．．．ケーキ？";
                    }
                    else
                    {
                        text1 = "にゃに？！まちがった？その音は電子レンジ";
                        text2 = "みたいだね。嫌いだ。";
                    }
                }
            }
            combo = 0;
        }
        correct = false;
        //strcpy(inputString, "");
    }
    destroy_sample(correctAnswer);
    destroy_sample(wrongAnswer);
    destroy_sample(fiftyRight);
    return false;
}

void drawWritingExplanationScreen(BITMAP* sprite2, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int xcor)
{
    masked_blit(sprite2, screen, 0, 0, xcor, 280, sprite2->w, sprite2->h);
    alfont_textout(screen, font, "「スペースでスキップできます」", 140, 90, makecol(255, 255, 255));
    if(scrollTextCursor(font, textCursor, textbox, "書く練習ゲームへようこそ！", 38, 320, makecol(0, 0, 0)))
    {
        if(scrollTextCursor(font, textCursor, textbox, "このモードは漢字の書き方の練習ためです。", 38, 320, makecol(0, 0, 0)))
        {
            if(scrollTextCursor(font, textCursor, textbox, "ゲームのもくてきは単語リストを空にすることです。", 36, 320, makecol(0, 0, 0)))
            {
                if(scrollTextCursor(font, textCursor, textbox, "それをするにはファストトライで正しく書きます。ファストトライならその単語は消えます。", 36, 320, makecol(0,0,0)))
                {
                    if(scrollTextCursor(font, textCursor, textbox, "単語はひらがなと英語で出て、あなたは自分で書いて練習します。", 38, 320, makecol(0,0,0)))
                    {
                        if(scrollTextCursor(font, textCursor, textbox, "ざんねんながら、正しいか間違いか決めるのはあなただけです。", 38, 320, makecol(0, 0, 0)))
                        {
                            if(scrollTextCursor(font, textCursor, textbox, "プログラムでそんなことができませんが、あなたはOキーとXキーで自分をグレードできます。", 38, 320, makecol(0,0,0)))
                            {
                                if(scrollTextCursor(font, textCursor, textbox, "覚えて書けたらOキーで次の漢字は出ます。間違ったら、Xキーを押して同じ漢字はのこります。", 38, 320, makecol(0,0,0)))
                                {
                                    if(scrollTextCursor(font, textCursor, textbox, "漢字が覚えないなら、かくにんするにはスペースキーを押します。", 38, 320, makecol(0, 0, 0)))
                                    {
                                        if(scrollTextCursor(font, textCursor, textbox, "答えは正しいなら、次の単語は出て、コンボ(BEATS)は上る。間違いなら、コンボはゼロに変わります。", 38, 320, makecol(0, 0,0)))
                                        {
                                            if(scrollTextCursor(font, textCursor, textbox, "30BEATSまで行けるならイメージと音楽は変わります。", 38, 320, makecol(0, 0, 0)))
                                            {
                                                if(scrollTextCursor(font, textCursor, textbox, "さて、じゅうんびがいいならゲームを始めましょうか？", 38, 320, makecol(0,0,0)))
                                                {

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
}

int drawWritingScreen(BITMAP* sprite2, BITMAP* window, BITMAP* textbox, ALFONT_FONT* font, int maxCombo, int xcor, string secret)
{
    int correctNum = 0;
    set_trans_blender(0,0,0,180);
    const char* text1 = "";
    const char* text2 = "";
    const char* text3 = "";
    const char* text4 = "";

    if(secret.compare("degozaru") == 0)
    {
        text1 = "拙者はデゴザルでござる！";
        text2 = "おはようでござる！？";
        text3 = "";
        text4 = "";
    }
    else
    {
        if(secret.compare("kekihime") == 0)
        {
            text1 = "私をケーキ姫と呼んでいい。";
            text2 = "よろしくね。";
            text3 = "";
            text4 = "";
        }
        else
        {
            text1 = "やっとｷﾀ━(ﾟ∀ﾟ)━！！";
            text2 = "４６４９。";
            text3 = "";
            text4 = "";
        }
    }
    stringstream sstr;
    string str;
    int combo = 0;
    string beats;
    bool firstTry = true;
    while(!close_button_pressed)
    {
        sstr.str("");
        sstr.clear();
        sstr << correctNum << "/" << wordTotal;
        str = "ステイタス: " + sstr.str();
        text3 = str.c_str();
        blit(currentBackground, screen, 0, 0, 0, 0, currentBackground->w, currentBackground->h);
        alfont_set_font_size(font, 20);
        alfont_textout(screen, font, "ESCでメインメニュに戻れます", 270, 20, makecol(255, 255, 255));
        masked_blit(sprite2, screen, 0, 0, xcor, 280, sprite2->w, sprite2->h);
        masked_blit(textbox, screen, 0, 0, 10, 310, textbox->w, textbox->h);
        draw_trans_sprite(screen, window, 30, 60);
        draw_trans_sprite(screen, window, 30, 200);
        alfont_set_font_size(font, 38);
        beats = static_cast<ostringstream*>( &(ostringstream() << combo) )->str();
        beats = "BEATS: " + beats;
        alfont_textout(screen, font, beats.c_str(), 109, 19, makecol(255, 255, 255));
        alfont_textout(screen, font, beats.c_str(), 110, 20, makecol(0, 0, 0));
        scrollText(font, hiraganaDeque.front().c_str(), 50, 90, makecol(255, 255, 255));
        scrollText(font, meaningDeque.front().c_str(), 50, 230, makecol(255, 255, 255));
        alfont_set_font_size(font, 25);
        scrollText(font, text1, 30, 320, makecol(0, 0, 0));
        scrollText(font, text2, 30, 355, makecol(0, 0, 0));
        scrollText(font, text3, 30, 390, makecol(24, 131, 56));
        scrollText(font, text4, 30, 420, makecol(24, 131, 56));
        alfont_set_font_size(font, 38);
        while(!close_button_pressed && !key[KEY_O] && !key[KEY_X] && !key[KEY_ESC])
        {
            alfont_textout(screen, font, hiraganaDeque.front().c_str(), 50, 90, makecol(255, 255, 255));
            while(key[KEY_SPACE])
            {
                alfont_textout(screen, font, kanjiDeque.front().c_str(), 50, 90, makecol(255,255,255));
                draw_trans_sprite(screen, window, 30, 60);
            }
                draw_trans_sprite(screen, window, 30, 60);
        }
        if(key[KEY_ESC])
        {
            switchBackground();
            switchMusic();
            return -1;
        }
        else
        {
            if(key[KEY_X])
            {
                combo = 0;
                firstTry = false;
            }
            else
            {
                combo++;
                if(maxCombo <= combo)
                {
                    maxCombo = combo;
                }
                if(combo % 30 == 0)
                {
                    switchBackground();
                    switchMusic();
                    masked_blit(sprite2, screen, 0, 0, xcor, 280, sprite2->w, sprite2->h);
                    masked_blit(textbox, screen, 0, 0, 20, 310, textbox->w, textbox->h);
                }
                if(kanjiDeque.size() == 1)
                {
                    return maxCombo;
                }
                if(!firstTry)
                {
                    kanjiDeque.push_back(kanjiDeque.front());
                }
                kanjiDeque.pop_front();
                if(!firstTry)
                {
                    pronunciationDeque.push_back(pronunciationDeque.front());
                }
                pronunciationDeque.pop_front();
                if(!firstTry)
                {
                    hiraganaDeque.push_back(hiraganaDeque.front());
                }
                hiraganaDeque.pop_front();
                if(!firstTry)
                {
                    meaningDeque.push_back(meaningDeque.front());
                }
                meaningDeque.pop_front();
                if(secret.compare("degozaru") == 0)
                {
                    text1 = "続きまんねん！でござる！";
                    text2 = "";
                    text3 = "";
                    text4 = "";
                }
                else
                {
                    if(secret.compare("kekihime") == 0)
                    {
                        text1 = "こんなふうにがんばったら．．．「け」と";
                        text2 = "始まる物を上げるよ！そうそう、ケープ！";
                        text3 = "";
                        text4 = "";
                    }
                    else
                    {
                        text1 = "次！これもがんばって！";
                        text2 = "ヽ(*・ω・)ﾉ";
                        text3 = "";
                        text4 = "";
                    }
                }
                if(firstTry)
                {
                    correctNum++;
                }
                firstTry = true;
            }
        }
    }
    return false;
}

//Draws the reading game's result screen.
void drawCompleteReadingScreen(BITMAP* sprite, BITMAP* window, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int maxCombo, int xcor, string secret)
{
    switchBackground();
    stop_sample(currentMusic);
    SAMPLE* resultMusic = load_sample("Sounds/MegamanLegendsResult.wav");
    SAMPLE* necoResult = load_sample("Sounds/NecoArcChaosResult.wav");
    play_sample(resultMusic, 100, 155, 1000, 1);
    play_sample(necoResult, 255, 155, 1000, 0);
    const char* text;
    stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr << maxCombo;
    string str = "ベストコンボ: " + sstr.str();
    text = str.c_str();
    blit(currentBackground, screen, 0, 0, 0, 0, currentBackground->w, currentBackground->h);
    alfont_set_font_size(font, 20);
    masked_blit(sprite, screen, 0, 0, xcor, 280, sprite->w, sprite->h);
    masked_blit(textbox, screen, 0, 0, 20, 310, textbox->w, textbox->h);
    draw_trans_sprite(screen, window, 30, 60);
    draw_trans_sprite(screen, window, 30, 200);
    alfont_set_font_size(font, 38);
    scrollText(font, "終了！", 50, 90, makecol(255, 255, 255));
    scrollText(font, text, 50, 230, makecol(255, 255, 255));
    alfont_set_font_size(font, 25);
    if(secret.compare("degozaru") == 0)
    {
        scrollTextCursor(font, textCursor, textbox, "一体何者なんでござる！？こんなに上手な人がいるのか知らなかったんでござる！拙者にそちの能力を見せてかたじけない。デゴザルアウト！", 38, 320, makecol(0, 0, 0));
    }
    else
    {
        if(secret.compare("kekihime") == 0)
        {
            scrollTextCursor(font, textCursor, textbox, "楽しかったよこれは！やっぱりいい日本語の学生には、ガッツと友情と、そしてケーキだわね！", 38, 320, makecol(0, 0, 0));
        }
        else
        {
            scrollTextCursor(font, textCursor, textbox, "我輩からの忠告は以下の三つ。一つ、ヘンな新聞読むな。一つ、アレが調理したニボシ食うな。そして最後の一つ、いいから家を出ろ。", 38, 320, makecol(0, 0, 0));
        }
    }
    stop_sample(resultMusic);
    destroy_sample(resultMusic);
    destroy_sample(necoResult);
    switchBackground();
    switchMusic();
    rest(100);
}

//Show's the writing game's results screen.
void drawCompleteWritingScreen(BITMAP* sprite, BITMAP* window, BITMAP* textCursor, BITMAP* textbox, ALFONT_FONT* font, int maxCombo, int xcor, string secret)
{
    switchBackground();
    stop_sample(currentMusic);
    SAMPLE* resultMusic = load_sample("Sounds/MegamanLegendsResult.wav");
    SAMPLE* kohakuResult = load_sample("Sounds/KohakuResult.wav");
    play_sample(resultMusic, 100, 155, 1000, 1);
    play_sample(kohakuResult, 255, 155, 1000, 0);
    const char* text;
    stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr << maxCombo;
    string str = "ベストコンボ: " + sstr.str();
    text = str.c_str();
    blit(currentBackground, screen, 0, 0, 0, 0, currentBackground->w, currentBackground->h);
    alfont_set_font_size(font, 20);
    masked_blit(sprite, screen, 0, 0, xcor, 280, sprite->w, sprite->h);
    masked_blit(textbox, screen, 0, 0, 20, 310, textbox->w, textbox->h);
    draw_trans_sprite(screen, window, 30, 60);
    draw_trans_sprite(screen, window, 30, 200);
    alfont_set_font_size(font, 38);
    scrollText(font, "終了！", 50, 90, makecol(255, 255, 255));
    scrollText(font, text, 50, 230, makecol(255, 255, 255));
    alfont_set_font_size(font, 25);
    if(secret.compare("degozaru") == 0)
    {
        scrollTextCursor(font, textCursor, textbox, "一体何者なんでござる！？こんなに上手な人がいるのか知らなかった！拙者にそちの能力を見せてかたじけない。デゴザルアウト！", 38, 320, makecol(0, 0, 0));
    }
    else
    {
        if(secret.compare("kekihime") == 0)
        {
            scrollTextCursor(font, textCursor, textbox, "楽しかったよこれは！やっぱりいい日本語の学生には、ガッツと友情と、そしてケーキだわね！", 38, 320, makecol(0, 0, 0));
        }
        else
        {
            scrollTextCursor(font, textCursor, textbox, "(((o(*ﾟ▽ﾟ*)o)))　たまにナツゲーするものいいものね、翡翠ちゃん！", 38, 320, makecol(0, 0, 0));
        }
    }
    stop_sample(resultMusic);
    destroy_sample(resultMusic);
    destroy_sample(kohakuResult);
    switchBackground();
    switchMusic();
    rest(100);
}

//Scrolls the given message at the given location.
void scrollText(ALFONT_FONT* font, const char* message, int x, int y, int color)
{
    //Make a buffer, textout onto it, and then slowly blit it to make the text appear to scroll.
    BITMAP* buffer = create_bitmap(alfont_text_length(font, message), alfont_text_height(font));
    clear_to_color(buffer, makecol(255,0,255));
    alfont_textout(buffer, font, message, 0, 0, color);
    for(int i = 0; i <= buffer->w+30; i = i + 15)
    {
        masked_blit(buffer, screen, 0, 0, x, y, i, buffer->h);
        rest(4);
    }
    destroy_bitmap(buffer);
}

//Scrolls text with a moving cursor at the end, visual novel-style.
bool scrollTextCursor(ALFONT_FONT* font, BITMAP* textCursor, BITMAP* textbox, const char* message, int x, int y, int color)
{
    alfont_set_font_size(font, 22);
    BITMAP* buffer= create_bitmap(alfont_text_length(font, message), alfont_text_height(font));
    clear_to_color(buffer, makecol(255, 0, 255));
    alfont_textout(buffer, font, message, 0, 0, color);
    int end = 0;
    int startingPoint = 0;
    int boxWidth = 0;
    masked_blit(textbox, screen, 0, 0, 20, 310, textbox->w, textbox->h);
    for(int i = 0; i <= buffer->w; i = i + 3)
    {
        if(key[KEY_SPACE] || close_button_pressed)
        {
            destroy_bitmap(buffer);
            return false;
        }
        if(boxWidth >= textbox->w-60)
        {
            y += 30;
            startingPoint = i-2;
            end = 0;
            boxWidth = 0;
        }
        masked_blit(buffer, screen, startingPoint, 0, x, y, end+3, buffer->h);
        rest(20);
        boxWidth += 3;
        end += 3;
    }
    BITMAP* filler = create_bitmap(textCursor->w, textCursor->h);
    clear_to_color(filler, makecol(255, 255, 255));
    y = y + 5;
    masked_blit(textCursor, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
    while(!key[KEY_ENTER] && !key[KEY_ENTER_PAD] && !close_button_pressed)
    {
        int maxHeight = y - 3;
        int minHeight = y + 3;
        while(y > maxHeight && !key[KEY_ENTER] && !key[KEY_ENTER_PAD] && !close_button_pressed)
        {
            if(key[KEY_SPACE])
            {
                destroy_bitmap(buffer);
                destroy_bitmap(filler);
                return false;
            }
            blit(filler, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
            masked_blit(textCursor, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
            rest(40);
            blit(filler, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
            y--;
        }
        while( y < minHeight && !key[KEY_ENTER] && !key[KEY_ENTER_PAD] && !close_button_pressed)
        {
            if(key[KEY_SPACE])
            {
                destroy_bitmap(buffer);
                destroy_bitmap(filler);
                return false;
            }
            blit(filler, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
            masked_blit(textCursor, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
            rest(40);
            blit(filler, screen, 0, 0, x+end, y, textCursor->w, textCursor->h);
            y++;
        }
        y = y - 3;
    }
    destroy_bitmap(buffer);
    destroy_bitmap(filler);
    return true;
}

void flashText(ALFONT_FONT* font, const char* message, BITMAP* background, int x, int y, int color)
{
    BITMAP* buffer = create_bitmap(alfont_text_length(font, message), alfont_text_height(font));
    clear_to_color(buffer, makecol(255,0,255));
    alfont_textout(buffer, font, message, 0, 0, color);
    blit(background, screen, x, y, x, y, buffer->w, buffer->h);
    masked_blit(buffer,screen, 0, 0, x, y, buffer->w, buffer->h);
    destroy_bitmap(buffer);
}
