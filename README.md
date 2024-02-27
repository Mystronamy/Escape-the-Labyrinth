Trapped in a Labyrinth - How to Escape
You have been trapped in a labyrinth, and your only hope to escape is to cast the magic spell that will free you from its walls. To do so, you will need to explore the labyrinth to find three magical items:

The Spellbook (📕), which contains the spell that must be cast in order to escape.
The Potion (⚗), containing the arcane compounds that power the spell.
The Wand (⚚), which concentrates focus to make the spell work.
Once you have all three items, you can cast the spell and escape to safety. This is, of course, no ordinary maze. It’s a pointer maze.

For example, check out this 4×4 labyrinth:

Your starting position is marked with a smiley face, and the positions of the three items are marked with similarly cute emojis. In this example, the MazeCell you begin at has its north, south, east, and west pointers pointing at the MazeCell objects located one step in each of those directions from you. On the other hand, the MazeCell containing the book has its north, east, and west pointers set to nullptr, and only its south pointer would point somewhere (specifically, to the cell in the bottom-left corner). Each MazeCell has a variable named whatsHere that indicates what item, if any, is at that position. Empty cells will have whatsHere set to the empty string. The cells containing the Spellbook, Potion, or Wand will have those fields set to "Spellbook", "Potion", and "Wand", respectively, with that exact capitalization.

If you were to find yourself in this labyrinth, you could walk around a bit to find the items you need for casting the escape spell. There are many paths you can take; here’s three of them:

ESNWWNNEWSSESWWN
SWWNSEENWNNEWSSEES
WNNEWSSESWWNSEENES
 

Each path is represented as a sequence of letters (N for north, W for west, etc.) that, when followed from left to right, trace out the directions you’d follow. For example, the first sequence represents going east, then south (getting the Potion), then north, then west, etc. Trace though those paths and make sure you see how they pick up all three items. 

Tutorial for using gdb to navigate a pointer maze
Note: the following tutorial uses kYourNetID = "scotreck" .

Navigating a regular pointer maze involves running gdb on ExploreTheRegularLabyrinth.cpp. The makefile is set up to run this file for you. Try it first by typing: 

>> make build_reg
>> make run_reg


The program output should make it clear that you have NOT escaped the labyrinth. Now, run the executable under gdb:

>> gdb ExploreTheRegularLabyrinth.exe


Then, set a breakpoint at the line labeled in a comment in ExploreTheRegularLabyrinth.cpp (likely line 15) and run the program:

(gdb) b ExploreTheRegularLabyrinth.cpp:15
(gdb) r


The break occurs on the nearest line of code that is not blank, so you might actually see a different line number for the break. 

Next, let's explore the program in its current state by getting information about the local variables (sample output is also shown):

(gdb) i locals 
m = {_vptr.Maze = 0x55863f0afbf8 , grid = {_vptr.Grid = 0x55863f0afc18 +16>, 
    Rows = 0x55863ff96eb0, NumRows = 4}, numRows = 4, numCols = 4, kNumTwistyRooms = 12}
start = 0x55863ff970d0


Now, let's dereference the start pointer and print out the contents, which is the MazeCell where you have been dropped into the labyrinth:

(gdb) p *start
$1 = {whatsHere = "", north = 0x0, south = 0x55863ff97210, east = 0x0, west = 0x0}


What you see at this point depends on your personalized maze and the starting location within it. You may find yourself in a position where you can move in all four cardinal directions, or you may find that you can only move in some of the possible directions. The pointers in directions you can’t go are all equal to nullptr, which shows up as 0x0 in gdb.

The pointers that indicate directions you can go all have non-null memory addresses. You can navigate the maze further by choosing one of those directions to pursue. Proceeding from here is really up to you!  Here, the maze was explored a bit, and look, we found the spellbook!...

(gdb) p *(start->south)
$2 = {whatsHere = "", north = 0x55863ff970d0, south = 0x55863ff97350, east = 0x0, west = 0x0}
(gdb) p *(start->south->south)
$3 = {whatsHere = "", north = 0x55863ff97210, south = 0x0, east = 0x55863ff973a0, west = 0x0}
(gdb) p *(start->south->south->east)
$4 = {whatsHere = "", north = 0x55863ff97260, south = 0x55863ff974e0, east = 0x55863ff973f0, west = 0x55863ff97350}
(gdb) p *(start->south->south->east->north)
$5 = {whatsHere = "", north = 0x55863ff97120, south = 0x55863ff973a0, east = 0x0, west = 0x0}
(gdb) p *(start->south->south->east->north->north)
$6 = {whatsHere = "Spellbook", north = 0x0, south = 0x55863ff97260, east = 0x55863ff97170, west = 0x0}
