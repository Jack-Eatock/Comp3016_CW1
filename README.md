
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

### Links
- [Github Repository](https://github.com/Jack-Eatock/Comp3016_CW1)
- [Video Demonstration](https://github.com/Jack-Eatock/Comp3016_CW1)

### UML Design Diagram
The project was designed so that each object in the game was an "Entity". Every "Entity" could have various "Components". For example you may have an Entity for a Car. This car would then have a component for taking input from a keyboard, a component for moving the car and a component for visually displaying the car. This allows for the code to be much more organised and helps with flexibility. We can switch out an entities components whenever we please to add or remove functionality at runtime. Similar to how many game engines function, such as the Untiy Engine or Unreal Engine. Here is a UML Diagram to show this concept:

<img src="/MarkDownImages/EntityComponentDiagram.drawio.png"  style="height:282px; width:621px;"/>

### Exception handling and test cases
The project was designed so that each object in the game was an "Entity". Every "Entity" could have various "Components". For example you may have an Entity for a Car. This car would then have a component for taking input from a keyboard, a component for moving the car and a component for visually displaying the car. This allows for the code to be much more organised and helps with flexibility. We can switch out an entities components whenever we please to add or remove functionality at runtime. Similar to how many game engines function, such as the Untiy Engine or Unreal Engine. Here is a UML Diagram to show this concept:

### Tools used:
- Aseprite - Was used to draw the pixel art used in the game.
- Visual Studio 2022 for Windows 10 - Was used to develop the project.
- x64 - The project is built for x64.

### References
This project was developed  using C++   with the following libraries
- SDL2 - Rendering the game.
- SDL2_Image - Rendering images such as png.
- SDL2_ttf - Rendering text.

