
# The Resilience of Mankind
### Comp3016 - 30% - Submission

The Milky Way has been devoured by a swarm-like horde of hive-minded creatures, known as the Gruk. A father of an advanced species, tells the heroic story of human commanders who put their lives on the line to prevent the swarm from spreading. Unfortunately, the human race was eradicated, but their stubbornness and long resistance paved the stepping stones for seven once-rivalled species to form the galactic federation. Thanks to the humans, the federation had enough time to build up a large enough military might to contain the Gruk horde once and for all. 

Playout the fight for survival the commanders experienced as they prevented any Gruk from escaping their boarders. Could you have survived?

### How to Play
Download the Repository, open x64 -> Debug and run "CW1.exe". Or alternatively if you have already got the build folder, simply run the "CW1.exe" from within the folder.

#### Controls:
- WASD - Moves your ship.
- Left Shift - Boost, allows your ship to go faster.
- Mouse - Your ship will aim towards the mouse cursor.
- Mouse Left Click - Fires a bullet from your ship.
- Spacebar - [Ui Only], progresses through menu's

### USP
In "The Resilience of Mankind" you experience the events being told through many different character's perspectives. You fly a spaceship, avoid enemy fire and strategically time your shots to be victorious. 
The game plays like an arcade machine, challenging the player to reach further and further every time they play. Although at first, the game is challenging, you will quickly learn and master the uniquely satisfying mechanics. 

### Links
- [Github Repository](https://github.com/Jack-Eatock/Comp3016_CW1)
- [Video Demonstration](https://www.youtube.com/watch?v=j0AH8hSmwb4&ab_channel=JackEatock)

### UML Design Diagram
The project was designed so that each object in the game was an "Entity". Every "Entity" could have various "Components". For example you may have an Entity for a Car. This car would then have a component for taking input from a keyboard, a component for moving the car and a component for visually displaying the car. This allows for the code to be much more organised and helps with flexibility. We can switch out an entities components whenever we please to add or remove functionality at runtime. Similar to how many game engines function, such as the Untiy Engine or Unreal Engine. Here is a UML Diagram to show this concept:

<img src="/MarkDownImages/EntityComponentDiagram.drawio.png"  style="height:282px; width:621px;"/>

The game has a main “Game.cpp” file that manages the core functionality of the application. It first initiates all required libraries, such as SDL2. If successful it will then load all the required assets, textures, fonts and data from text files. Once everything is set up it will once per frame iterate over all components on all entities in the game, running their update and draw function. The components then react accordingly, creating an interactive experience.
If we wanted to add further functionality to the project it would be very easy. We can simply either tweak the current components or create new ones that fit our needs.

Here are some UML diagrams breaking down parts of the game’s logic.


#### Enemy Ship Statemachine

<img src="/MarkDownImages/EnemyShip.drawio.png"  style="height:148px; width:601x;"/>

#### Wave Game Loop Statemachine

<img src="/MarkDownImages/WaveGameLoop.drawio.png"  style="height:179px; width:631x;"/>

### Exception handling and test cases
The project was designed so that each object in the game was an "Entity". Every "Entity" could have various "Components". For example you may have an Entity for a Car. This car would then have a component for taking input from a keyboard, a component for moving the car and a component for visually displaying the car. This allows for the code to be much more organised and helps with flexibility. We can switch out an entities components whenever we please to add or remove functionality at runtime. Similar to how many game engines function, such as the Unity Engine [See reference here](https://unity.com/ecs) or Unreal Engine. Here is a UML Diagram to show this concept:

### Tools used:
- Aseprite - Was used to draw the pixel art used in the game.
- Visual Studio 2022 for Windows 10 - Was used to develop the project.
- x64 - The project is built for x64.

### References
This project was developed  using C++   with the following libraries
- SDL2 - Rendering the game.
- SDL2_Image - Rendering images such as png.
- SDL2_ttf - Rendering text.

