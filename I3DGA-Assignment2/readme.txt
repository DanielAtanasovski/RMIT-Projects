DANIEL ATANASOVSKI s3658474

* Source files are in src folder.
* Visual studio solution is in vs folder.
* External libraries needed to compile OpenGL programs using visual studio are in libs.
* Don't delete freeglut.dll, it's needed.
* Compile 64 bit versions only, as freeglut.dll is a 64 bit dll.

Attempted:

Arena : Medium
Spaceship : Medium
Asteroids Model : Easy
Asteroids Movement : Easy
Lighting : Medium
Bullets & Shooting : Easy
Camera & Ship : Medium

Controls:

WASD - Movement Along Axis
Mouse (Horizontal) - Yaw Rotation
Mouse (Vertical) - Pitch Rotation
'Z' - Pull Camera closer to Spaceship
'X' - Push Camera away from Spaceship

Spaceship is modified model such that it was easier to modify properties on different shapes using tinyobjloader. 
Materials are seperated for the body and window of the spaceship.


Bugs / rant:
Spaceship is textured despite it being incorrectly mapped (but maybe it looks cooler like this?)

Asteroids and bullets will not be destroyed no matter how hard I try to try EVEN THOUGH IT DELETES AFTER A CERTAIN RANGE FROM THE ARENA.
No matter how many debug statements I put, I can't for the life of me find a flaw or issue in the logic regarding how i'm trying to destroy these objects.
Workaround is to just turn off your monitor and pretend all the bullets and asteroids are destroyed as they collide. /rant

and don't even get me started on how long it took just to get the camera to rotate...

Credits:
SHIP Model and Texture by "chrisonciuconcepts", Sourced From:
https://sketchfab.com/3d-models/low-poly-space-ship-587941c9c11742c6b82dfb99e7b210b9
