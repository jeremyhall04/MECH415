
Game v1 "So much different" - December 15th, 2020 
	
	Jeremy
Done:
-literally so much
- I changed the bullets from vectors to pointer arrays 
- created an player.update() to update player & reduce main() size
- player & enemy collisions with bullets 
- moved stuff around


TODO:
* Implement networking
* Bullet Manager
* Levels
* Menu

_____________________________________________________________________________

Game v1 "Player Collision + Functionning Healthbars" - November 10th, 2020
	
	Jeremy
Done:
-Fixed the disappearing healthbars on collision (they now show correct health)
-Player now collides with enemy bullets
	Does not die tho
-Started a Menu design

TODO:
*Menus
*Player death

_____________________________________________________________________________
Game v1 "Variable enemies added + bullet timer & collisions + damage" - Oct 18th, 2020
	
	Jeremy
Done:
-Bullet timer complete
-Health bars added
-Bullet Damage implemented

TODO:
*Fix bullet damage
	*Make bullets disappear after contact

	Jeremy Oct 20th, 2020
Done:
-Bullet damage fixed 
-Bullets disappear after collision

TODO:
*Arena Style fighting, waves of enemies to be cleared
*Different types of enemies
	*Enemy movement & shooting
	*Snake :)
*Implement WAVEs
*Create starting menu
*Map creation? Decide if different maps are needed 
**ENEMY CLASS W/ RESPECTIVE CHARACTERTICS
**REFACTOR GAME OBJECT CLASS TO CREATE DIFFERENT OBJECTS
ex.
	GameObject: 
	x, y, hitbox
	/	\
  
_____________________________________________________________________________

Game v1 "GAMEOBJECTS, src cleanup, Header.h" - Oct 13th, 2020. 
	
	Jeremy
Done:
-Cleaned up files into folders, created "Header.h" linking all header files
-Created Hitbox boxes 
	To be determined if collision detection is done via external libraries
-Enemy class added

TODO:
*Item To Do

	Jeremy Oct. 14th, 2020
-Created GameObject class, maybe to replace multiple classes.
	Encompasses all other classes (player, enemies, bullets & possibly map/tiles)
	Reduces the total number of different classes, most of which have the same mechanics
	Allows for an easier implementation of collision detection


_____________________________________________________________________________
Game v1. "Mouse-aimed shooting implemented, src file added" - Oct 13th, 2020.

	Jeremy - Oct. 11th, 2020.
-Moved all files (.cpp & .h) to "src" file
-Created folders for files & sorted by group
ex.
GAME
->src
  ->Player
    ->Player.cpp
    ->Player.h
-"textures" file added

TODO:
*Implement mouse-aimed shooting
*Map Design: Tilemap implementation
*Start Pixel Art
*Begin creating Network packets

	Jeremy - Oct. 13th 2020.
-moved Map & Player data to heap (dynamically allocate memory) to reduce local stack size in main()
	Reduce stack size form 104292bytes to 2424bytes
-rearange class headers (public:, then private:)

-Implemented mouse-aimed shooting
_____________________________________________________________________________

Game v1. "1st Commit" - October 5th, 2020

	Jeremy - Oct. 5th, 2020.
-Created Game class w/ main
-Created Player class
-First commit created, github repository created.

_____________________________________________________________________________

Game vX.X "Commit Title" - Date 
	
	Name - Date
Done:
-Item done

TODO:
*Item To Do

_____________________________________________________________________________
