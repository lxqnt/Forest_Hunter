## Forest Hunter: Ray Casting in C

Continuing my dive into the world of computer graphics, Forest Hunter is a first person maze game that implements a 3d dimensional feel using ray casting methods. As a basis for the project, I looked at the original Wolfenstein 3D game from the 80's and implemented several elements of that game. 

The project was written in C and uses two additioanl libraries - miniLibx and libft. MiniLibx provides tools to do simple graphics tasks in macOS, such as window creation and pixel placement. Libft is a collection of self written standard library functions. 

## Installation

* Clone the repository
* To compile, run 'make' from the command line within the project folder. See Makefile for more commands that can be run. 
* To play the game, open the file foresthunter from the command line. Pass in the 'maps' for the level you would like to play - as seen below. Maps are located in the maps folder. Up to three maps can be added at one time. 

```
./foresthunter maps/map1 maps/map2 maps/map3
```

## Movement

* Movement is handled by the arrow keys. 
* Pressing 'm' will display a level map on the command line. The '@' symbol indicates your position. 
* Finding the 'golden city' will exit the level and the game. 
* q , esc, or the x on the screen will exit the game. 

## Screen Shots

### Home Screen 

Homescreen launches the game music and allows level selection. 

![foresthunter1](https://user-images.githubusercontent.com/15381642/46112329-3486a400-c19f-11e8-9d07-d1aa75ea4a68.png)

### Gameplay 

Image showcasing the 3d gameplay view. Different levels will have different textures. 

![foresthunter3](https://user-images.githubusercontent.com/15381642/46113614-f93aa400-c1a3-11e8-9e5a-f7ab0d7cdc00.png)

![foresthunter2](https://user-images.githubusercontent.com/15381642/46112350-449e8380-c19f-11e8-9993-a0737dc906b3.png)

## Implemented elements

### Raycasting and DDA line algorithm 

The 3d experiece was implemented following ray casting principles. Ray casting, in my simplified explanation, is used to calculate the distance from a point (the players position) to the limites of the map. This distance is used to calculate the relative height of a wall to the players position. The generated wall then gives the 3 dimensional position. 

Unlike more advanced techniques, such as ray tracing, ray casting only measures ray distance to points on the primary x axis, not all points in the visual sphere. This creates the lack of texture or flat feel of the walls in a ray casting game, but also means there are fewer calculations needed to render the screen.  

The illusion of depth on the walls are then created by implmenting wall textures. Instead of having the walls a single color, an image is rendered on the wall. 

To calculate the distance between the player and the nearest wall, I used a DDA line algorithm. Each level map and wall is set up as a coordingate grid, and so the DDA algorithm, which utilizes the coordinate grid allowed for greated distance calculation efficiency.

### Multiple levels and structuring data modularly 

A key implementation goal was to create a modular data storage to allow for multiple level maps. There is still work to be done to allow for the player to move from one level to the next, but the data structure set up does allow for this.

At the beginning of gameplay, a struct is instantiated that stores the file names that were passed in from the command line. When a level is specificed by the user, the file name is then opened and the map is read into an int array. The initial file names continue to be stored during the life of the program, which would allow for a new level to be specified with a few additional functions. 

### Additional elements incorporated 

* key hooks
* wall textures
* game play elements
* music
* different color ways and textures for levels 

### Things to improve and add 

* seamless movement
    * Player movement is currently hampered by the key stroke implementation. To smoothen the experience I would have the screen image rerender at a timed pace, instead of having the keystrokes trigger rerendering.  
* lighting
    * The feeling of depth could be improved by adding a gradient dimming effect for the areas that are further from view from the player. 
* improve textures
    * Some of the current images used for textures dont seamlessly meld together on long walls. Simpler, non graphic images could improve this issue. 

