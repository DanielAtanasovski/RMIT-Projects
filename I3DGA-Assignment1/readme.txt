Implemented Level 1, 2, 3, 4

no bonus :(

Uses provided template, should just open in visual studio and run.

Notes:
- Asteroids will keep spawning every 5 secs by default to a maximum of 5 asteroids per wave; meaning if the player somehow survives,
the asteroids can keep trying to enter the arena, but will bounce out and can cause the game to slowdown with many asteroids as it looks for safe 
locations to spawn new waves.

- On that note, asteroids will only collide with the walls of the arena upon fully entering the arena, meaning that asteroids can still knock out
partially entered asteroids.

- All entities will be destroyed as it exits past the spawn range of asteroids, this includes bullets and even asteroids that have a velocity
that takes them away from the arena.

- There is an intentional input delay between player death and input to restart, as it is found that the player can have a key held down before
entering the end screen, skip the end screen and restart the game almost instantly.

- I've tried to keep the project to a high quality where possible, but the 'Game' class can be seen as a bit bloated. I've done this intentionally
to try to keep the project as simple as possible, keeping one class, 'Game', as the middleman. Keeping the project simple was a priority over
making the project over-engineered with long sub-class hierachies and a web of interconnections that can seem overly confusing for a simple concept.

- Asteroids have text to represent health, which can be disabled by commenting out the two lines in the draw function of the 'Asteroid' class


known issues: 
- The game stops updating asteroids on game end... still struggling to understand why that is...

- Explosions explode in seemingly random positions.

Controls:

'W' - Move in the direction the player is facing
'A' - Rotate Anti-Clockwise
'D' - Rotate Clockwise
'SPACE_BAR' or Left Mouse Button - Shoot



Provided Template README:

* Source files are in src folder.
* Visual studio solution is in vs folder.
* External libraries needed to compile OpenGL programs using visual studio are in libs.
* When creating new source files using visual studio, you should make sure they go in the src folder.
* Compiled executables are placed in this folder.
* Don't delete freeglut.dll, it's needed.
* Compile 64 bit versions only, as freeglut.dll is a 64 bit dll.