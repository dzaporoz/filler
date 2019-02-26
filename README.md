# Filler. School_42 project
The subject is to create a BOT program to compete against other BOT's on the Filler board. The principle is simple: two players take on each other on a board, and take turns placing the piece that the master of the game (supplied in the
form of a Ruby executable) gives them, earning points. The game stops as soon as a piece can no longer be placed.

## Algotythm
After receiving the figure, my program checks all available places for its location. It chooses the location at which the distance to the enemy as much as possible reduced. After contact with the enemy's field, the figures are placed close to his positions, surrounding him.

## Usage
1. run **make** to compile my bot (dzaporoz.filler) and vizualisation program.
2. execute command: ./resources/filler_vm -f resources/maps/map00 -p1 ./dzaporoz.filler -p2 resources/players/abanlin.filler

... where:

* recources/maps/map00 is map file;
* -p1 ./dzaporoz.filler is my program;
* -p2 ./resources/players/abanlin.filler is player writened by another person;

You can choose another map file (map01, map02) and you can find more bot's in 'players' folder. Also, you can change players order by swaping flags -p1/-p2.

## Visualization
Also I wrote a simple visualization program. It doesn`t use any graphic library, only unicode pseudographics.

Just put the VM's output via pipe:

./resources/filler_vm -f resources/maps/map00 -p1 ./dzaporoz.filler -p2 resources/players/abanlin.filler | ./vizualizator 
