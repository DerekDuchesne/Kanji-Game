*ノート: This program can only be run on Windows.

========
Overview
========
This is a game with customizeable backgrounds and music designed to help you practice reading and writing kanji. It is designed more for 
review than firsthand learning, so it may be to your benefit to go through the lessons of your kanji book first before using the game to 
practice. This game comes with preloaded lessons for each of the individual Kanji Look & Learn chapters as well as some more 
comprehensive lists (and some silly extras ^^) but it also contains a subprogram that allows you to create your own lists. Below are the 
instructions on how to operate the program.

==========
How to play    
==========
To start the game, all you need to do is simply click on the exe with the 漢 icon. There are a few things
you can do outside of the main game as well. In the 'Resources' folder is a list of vocabulary 
lessons. To choose a vocabulary lesson, go into the resources folder, double-click on the lesson you want, and copy 
everything in that folder (the hiragana.txt, kanji.txt, meaning.txt, and 
pronunciation.txt files). After you copy the text files, paste them into the 'Text' folder. It's okay to overwrite the existing text files that
are already in the text folder. Every time the game starts, it looks in the text folder for which list of vocab to use.

=========================
Adding backgrounds to the game
=========================
You can add your own backgrounds by pasting any .bmp (it must be .bmp) file into the 'Backgrounds' folder
under 'Images.' The recommended size is 640 X 480, since that's how big the windowed
game is.

=========================
Adding music to the game
=========================
You can add your own music by going into the 'Music' folder and putting in any
.wav (it must be .wav) file in. If the music stops playing after a few button presses, try to shorten the length
of the song. I recommend using this website http://audio.online-convert.com/convert-to-wav to convert your mp3s to
wav files.

**ノート: All of the backgrounds and music are picked at random at the start and are then looped in the order they were selected. You can
mix and match any that you would like by simply removing the ones you don't want from that folder.

==========================
Adding vocabulary to the game
==========================
New vocabulary is added with the TangoMaker.exe program. Below is the procedure of how to add vocab:

1) Go into the 'Text' folder and either put nothing in (if you want to start a list from scratch)
or put in existing hiragana.txt, kanji.txt, meaning.txt, and pronunciation.txt files that you would like to add words to.
2) Open up the hiragana.txt and kanji.txt text files (not the meaning and pronunciation ones) in NotePad and go to 'Save As' and then 
change the encoding to 'ANSI'. If you had nothing in the 'Text' folder to start with, don't worry about this step.
3) Run TangoMaker and add your vocab.
4) Open up the hiragana.txt and kanji.txt text files again and change the encoding to 'UTF-8' using the same method you did with
'ANSI'. Basically, whenever the game starts these text files need to be in UTF-8 format
but whenever you're writing to the files with TangoMaker, these text files need to be in ANSI.

================
In-game instructions
================
All the in-game instructions are in Japanese. Here's the English translation if needed:

Title screen:
"Push any key"

Selection screen:
Top option - "Reading practice"
Bottom option - "Writing practice"

Reading game instructions:
Top text: "Skip with Space"

Text box:
"Welcome to the reading game!"
"This mode is used for practicing the reading of different kanji."
"The goal of the game is to empty the vocab list."
"To do that, you have to read the word correcty on the first try. If it is on the first try, then that word will disappear from the list. If you get
the word wrong once and then retype it correctly, that word will be reshuffled into the list."
"The vocabulary appears and you type the reading (pronunciation) of the word in hiragana and hit Enter. The program then checks if it's right or wrong."
"If your answer was right, the next word will appear and your combo (BEATS) will go up. If you're wrong, your combo will be reset to zero."
"If you can reach 30 BEATS, the image and music will change."
"The vocabulary, the images, and the music are all random."
"If you can't read the word, you can tap the Space bar to see the reading and the meaning of the word in English. If you use this though, your combo will 
be set to 0."
"Now then, if you're ready, shall we start?"

Reading game:
Top right text: "Return to the main menu with ESC."

Writing game instructions:
Top text: "Skip with space"

Text box:
"Welcome to the writing game!"
"This mode is used for practicing writing kanji."
"The goal of the game is to empty the vocab list."
"To do that, you have to write the word correctly on the first try. If it is on the first try, that vocab word will disappear from the list. If you get
the word wrong once, it will be reshuffled back into the list."
"Vocabulary will appear with both the hiragana and English meaning of the word and you practice writing the kanji of that word on your own
(with a pad of paper or something)."
"Unfortunately, you're the only one who can determine if this is right or wrong."
"This program can't do that, but you can use the O and X keys to grade yourself."
"If you could remember and correctly write the word, then hit the O key to make the next kanji appear. If you were wrong, then hit the X key 
and the same kanji will remain."
"If you don't remember the kanji, hold the Space bar to check if you were right."
"If your answer is right, the next vocab will appear and your combo (BEATS) will go up. If you're wrong, the combo will be reset to zero. 
"If you can make it to 30 BEATS, the image and music will change."
"Now then, if you're ready, shall we begin?"

Writing game:
Top right text: "Return to the main menu with ESC."

==========
Known bugs
==========
1) The game will crash if:
- There are no backgrounds in the 'Backgrounds' folder under 'Images'.
- There is no music in the 'Music' folder.
- File types other than .bmps are in the 'Backgrounds' folder or file types other than .wavs are in the 'Music' folder.
- One or more of the text files (hiragana.txt, kanji.txt, meaning.txt, pronunciation.txt) are missing in the 'Text' folder.

2) If you are in the middle of typing a hiragana character such as か, once you type 'k', you cannot exit the program with the close button until
you either finish the character or backspace to get rid of what you were typing. This can be avoided simply by clearing the textbox before
hitting the close button on the game window.

3) Having to switch to ANSI and UTF-8 for the text files when adding new vocabulary lists.

4) Some songs might have their sound cut out after pressing a few keys. This only occurs when that particular song is playing.

***ノート: All of the images, sounds, and music that come with the game were not made by me and belong to their respective owners, 
including artwork from fellow Japanese student Amit Singh.

If you find any other errors or have any questions or suggestions, please email me at duchesd1@tcnj.edu. This is a work in progress and 
I plan on fixing these errors as well as adding new features. 

がんばってね！
