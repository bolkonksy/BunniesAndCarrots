# BunniesAndCarrots
Its a 2-player 2D game created in SDL for Windows. 

<a href="url"><img src="https://raw.githubusercontent.com/bolkonksy/BunniesAndCarrots/master/BunniesAndCarrotsSample.gif" align="center" height="540" width="720" border="black"></a> </b>

#### Dependencies 
- Visual studio

## How to Run it
1. Open *FirstGameSDL.sln* and compile the whole project
2. Copy Textures folder from *FirstGameSDL/Textures* to *Release* (or *Debug*) folder in project solution folder
3. Put all dll files from *DLL* folder in *Release* (or *Debug*) folder in project solution folder
- Optional: Edit *configuration.h* to change certain game options, such as player speed, etc.

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
- Avoid roses while trying to collect as many as possible carrots (Collecting carrots increases enemy speed, which makes him harder to avoid roses)
- In case you get poisoned, catch the enemy player to win the game. Or lose, if poison time hits zero.

---

## About 
 I made this game back in 2014 as a seminar project for a collage course Object-Oriented programming. I could do much simpler project for the seminar, but I wanted to make something fun and by the way learn how videogames are made. My friend drew all the textures.
 
#### How I did it?
 Mostly using <a href="http://lazyfoo.net/SDL_tutorials/">LazyFoo</a> SDL tutorials for understanding how SDL library works. Then I found a helpful <a href="http://staniks.github.io/">Staniks</a> game tutorial where he implemented a small coin game.
 The game is not really optimized and the code is kinda messy. It's not that bad, but it certainly lacks comments. It was one of my first projects, so sorry for that, if anyone ever finds this source code somewhat useful.
 
---

### Forgotten bugs
- Wrong speed (higher than expected), when moving diagonally
