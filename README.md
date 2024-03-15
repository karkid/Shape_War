# Shape_War
It is the game build on Entity Component System paradigm.

## Player
- The player is represented by a shape which is defined in the config file.
- The player must spawn in the center of the screen at the beginning of the game and after it dies (collides with an enemy)
- The player moves by a speed read from the config file in these directions:
    |Action|Key|
    |:---:|:---:|
    |Up|`W`|
    |Left|`A`|
    |Right|`S`|
    |Down|`D`|
- The player is confined to move only witin the bounds of the window.
- The player will shoot a bullet toeard the mouse pointer when the left mouse button is clicked. The speed, size, and lifespab of the bullets are read from the config file.

## Special ability
- When the right mouse button is clicked. The user can use the special ability.

## Enemy(s) 
- Enemies must not overlap the sides of the screen at the time of spawn.
- Enemies shapes have random number of vertices, between a given minimum and maximum number, which is specified in the config file.
- Enemy shape radius will be specified in the configuration file.
- Enemies will be given a random color upon spawning.
- Enemies will be given a random speed upon spawning, between a minimum and maximum value specified in the config file.
- When an enemy reaches the edge of the window, it should bounce off in the opposite direction at the same speed.
- When (large) enemies collide with a bullet or player, they are destroyed, and N small enemies spawn in its place, where N is the number of vertices of the original enemy. Each small enemy must have the same number of vertices and color of the original enemy. These small entities travel outward at angles at a fixed intervals equal to (360/ vertices).

## Score
- Each time an enemy spawns, it is given a score component of N*100, where N is the number of vertices it has. Small enemies get double this value.
- If a player bullet kills an enemy, the game score is increased by the score component of the enemy killed.
- The score should be displayed with the font specified by the config file in the top-left corner of the screen.

## Drawing
- In the render system, all entities should be given a slow rotation, which makes the game look a little nicer.
- Any Entity with a lifespan is currently alive, it should have its Color alpha channel set to a ratio depending on how long it has left to live. For example, if an Entity has a 100 frame life span, and it has been alive for 50 frames, its alpha value should be set to 0.5 * 255. The alpha should go from 255 when it is first spawned, to 0 on the last frame it is alive.

## Configuration File:

The configuration file will have one line each specifying the window size, font format, player, bullet specification, and enemy specifications. Lines will be given in that order, with the following syntax:

### Window W H FL FS
- This line declares that the window properties.

    |Token|Datatype|Description|
    |:---:|:---:|:---:|
    |W|int|Width|
    |H|int|Height|
    |FL|int|Frame limit|
    |FS|int|Full-screen mode (1) or not (0)|

### Font F S R G B
- This lines defines the font which is to be used to draw text for this program. The format of the line is as follows:

    |Token|Datatype|Description|
    |:---:|:---:|:---:|
    |F|string|Font file name or path|
    |S|int|Font size|
    |R,G,B|(int,int,int)|RGB color|

### Player SR CR S FR FG FB OR OG OB OT V

- This line declares that the player apecifications.

    |Token|Datatype|Description|
    |:---:|:---:|:---:|
    |SR|int|Shape Radius|
    |CR|int|Collision Radius|
    |S|float|Speed|
    |(FR, FG, FB)|(int,int,int)|Fill RGB Color|
    |(OR, OG, OB)|(int,int,int)|Outline RGB Color|
    |OT|int|Outline Thickness|
    |V|int|Shape Vertices|

### Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SP
- This line declares that the enemy apecifications.
    |Token|Datatype|Description|
    |:---:|:---:|:---:|
    |SR|int|Shape Radius|
    |CR|int|Collision Radius|
    |SMIN,SMAX|float,float|Min/Max Speed|
    |(OR, OG, OB)|(int,int,int)|Outline RGB Color|
    |OT|int|Outline Thickness|
    |VMIN VMAX|int, int|Min/Max Vertices|
    |L|int|Lifespan|
    |SP|int|Spawn Interval |


## Bullet SR CR S FR FG FB OR OG OB OT V L
- This line declares that the bullet apecifications.
    |Token|Datatype|Description|
    |:---:|:---:|:---:|
    |SR|int|Shape Radius|
    |CR|int|Collision Radius|
    |S|float|Speed|
    |(FR, FG, FB)|(int,int,int)|Fill RGB Color|
    |(OR, OG, OB)|(int,int,int)|Outline RGB Color|
    |OT|int|Outline Thickness|
    |V|int|Shape Vertices|
    |L|int|Lifespan|
