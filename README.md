# BunniesAndCarrots
a 2-player 2D game created in SDL for Windows. 

<a href="url"><img src="https://raw.githubusercontent.com/bolkonksy/BunniesAndCarrots/master/BunniesAndCarrotsSample.gif" align="center" height="540" width="720" border="black"></a>

## How to Run

You need to have Visual Studio installed.

1. Open *FirstGameSDL.sln* in Visual Studio and compile the project
2. Copy the *Textures* folder from *FirstGameSDL/Textures* to *Release* (or *Debug*) folder in project solution folder
3. Put all dll files from *DLL* folder in *Release* (or *Debug*) folder in project solution folder

- Optional: Edit *configuration.h* to change certain game options, such as player speed, etc.

---

## How to play
  - Player 1 controls: Arrow keys
  - Player 2 controls: WASD keys

| Entity        | Effects                        |
| ------------- | ------------------------------ |
| Rose          | Lose game                      |
| Carrot        | Score 1 Point                  |
|               | Increase enemy speed           |
| Green flower  | Get poisoned                   |
| Blue flower   | Reduce player speed            |
|               | Increase life left from poison |
| Pink flower   | Invert player controls for 2s  |
|               | Invert enemy controls for 4s   |
| Yellow flower | Lose 3 Point                   |
|               | Increase player speed greatly  |
|`Poison effect`| Lose game in Poison time (10s) |

### How to win?
- Avoid roses while trying to collect as many as possible carrots (Collecting carrots increases enemy speed, which makes it harder for them to avoid roses)
- In case you get poisoned, catch the enemy player to win the game. Or lose, if poison time hits zero.

---

## About 
 I made this game back in 2014 as a seminar project for a college course Object-Oriented Programming. I could have done a much simpler project for the seminar, but I wanted to make something fun and also learn how video games are made. A friend of mine drew all the textures.
 
### How did I do it?
I've mostly used <a href="http://lazyfoo.net/SDL_tutorials/">LazyFoo</a> SDL tutorials to understand how SDL library works. Later I found a helpful <a href="http://staniks.github.io/">Staniks</a> game tutorial where he implements a small coin game.

The game is not very optimized and the code is kinda messy. I also certainly lacks comments. It was one of my first projects, but I've learned much from it and I will strive to improve in the future.
 
---

### Forgotten bugs
 - In-game score points don't have an effect on victory (scoring system never fully implemented)
 - ~~Incorrect (higher) speed when moving diagonally~~ FIXED (seen in gif) 

---

##### Special thanks to:
 - <a href="http://sol-myr.deviantart.com/">Mirna</a> - The famous graphic designer. Did some coding also.
 - <a href="https://github.com/athnix/">athnix</a> - My dear helpful fix bugger and tester. Bad gaming skills tho. (specially at CS:GO... jk.)
 - <a href="https://github.com/sklavko/">sklavko</a> - Tester with some crazy gaming abilities.

