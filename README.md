C codebase for personal use

editor next steps:
-fix issue where draw_topbar/draw_text will draw more than the size of the terminal
-update draw_text() function 
-update read_input() function to :
    -write the input text to the screen
    -write the input text to the data set, which at this moment will also make it write to the screen

-create a write buffer for performance
-update draw_screen to only write changes 