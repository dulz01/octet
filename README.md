# octet

Octet is a framework for teaching OpenGL and the rudiments of game programming such
as Geometry construction, Shaders, Matrices, Rigid body Physics and Fluid dynamics.

It has a number of examples in the src/examples directory.

To use with visual studio, fork this repository into your own account and then
"Clone Into Desktop" using the GitHub tool and open one of the .sln files in src/examples.

There is a python script for generating your own projects from a template.

From the octet directory run:

packaging\make_example.py my_example

To create your own project in src/examples

Examples should also work with Xcode, although testing is a lot less thorough. If it does not work, send
me a pull request with fixes, please...

Octet is a bit unusual in that it does not use external libraries such as libjpeg or zlib.
These are implemented in source form in the framework so that you can understand the code.
The source of most academic libraries is almost unreadble, so we aim to help your understanding
of coding codecs such as GIF, JPEG, ZIP and so on.


# Legend of Hilda - A Fink of the Past

# Brief
To take the base game from example_invaderers and modify it into a different game.

# Introduction
The game is a Zelda clone and the aim is to modify the game enough that it closely follows the mechanics of Zelda.

# Changes made to example_invaderers
Minor tweaks were made in the beginning such as adding a pause button, allowing the invaderers and the player to move in the Y-axis, collision detection with the top and bottom borders and the player taking damage when touching the enemy. 

## Pause button
For the pause button, it was initially assigned to the Esc key and the word 'Paused' would appear in the middle of the screen. After adding extra keys that refer to the alpha characters to the enum in app_common.h, I reassigned the pause button to 'p'. A bug I encountered was that 'Paused' would disappear after trying to pause a second time. Because I've made this function based on the 'Game Over' sprite appearing at the end of the game, I failed to realise that the sprite was loaded initially offscreen and then moved into view. For the 'Paused' sprite, this would mean that it is continually moved in one direction every time the pause button is pressed. I fixed this by creating a variable for the position of the 'Paused' sprite and inverted the position every time the button is pressed.

    paused_position_x = -paused_position_x;
    sprites[paused_sprite].translate(paused_position_x, 0);
    
## Y-axis movement
This is a relatively simple change made to the invaderers and the player. For the invaderers, I just added a value in the move_invaderers() function for the Y-axis. For the player, I've added two more if statements for up and down movement.

# Collision detection
Now that the player and the enemy has Y-axis movement, the borders on the top and bottom of the game will have to keep them in. The collision detection code for invaderers live in the simulate() function while the collision detection code for the player is kept where the player makes inputs.

    sprite &border = sprites[first_border_sprite + (invader_velocity < 0 ? 2 : 3)];
    if (invaders_collide(border_x)) {
      invader_velocity = -invader_velocity;
      move_invaders(invader_velocity, 0);
    }
    
The invaderer collision code for the border is tied to the velocity of the invaderer. The border sprite the invaderer will collide with depends on the direction it is going. Then when the invader collides with the border, it will invert its velocity, changing its direction as well as the border the collision detection code will look for. To make it do the same for the top and bottom borders, I changed the original code to this:

    sprite &border_x = sprites[first_border_sprite + (invader_velocity_x < 0 ? 2 : 3)];
    if (invaders_collide(border_x)) {
      invader_velocity_x = -invader_velocity_x;
      move_invaders(invader_velocity_x, 0);
    }
    
    sprite &border_y = sprites[first_border_sprite + (invader_velocity_y < 0 ? 0 : 1)];
    if (invaders_collide(border_y)) {
      invader_velocity_y = -invader_velocity_y;
      move_invaders(0, invader_velocity_y);
    }
    
I've split the variable border to border_x and border_y and split the invader_velocity to invader_velocity_x and invader_velocity_y. The code is similar to one for the X-axis but adapted for the Y-axis and the top and bottom borders.

## Player collision
    if (is_key_down(key_left)) {
      sprites[player_sprite].translate(-player_speed, 0);
      if (sprites[player_sprite].collides_with(sprites[first_border_sprite + 2])) {
        sprites[player_sprite].translate(+player_speed, 0);
      }
    }
    
The player collision works just like the invaderer collision but the difference here would be that each border is set to a key input and when the player collides with the border it negates the movement instead of reversing it. This is because the player will continually push a direction and the collision will continually push the opposite direction causing the player to stay at the same spot.

The final bit of collision detection for the player is when the player collides with the invaderers. I just added an if statement where the other collision detection code for invaderers are:

    sprite &player = sprites[player_sprite];
    if (invaders_collide(player)) {
      on_hit_player();
    }
    
I've added a player_collision_disabled variable to the on_hit_player() function. This is based on the timers made for the missiles and bombs. The idea here is to give the player some invulnerability frames so that the collision wouldn't eat all of the player's lives while trying to move away. The timer is set to 0 when a bomb hits the player though. This is so that the player won't be invulnerable for longer than intended.

# Animating sprites
To animate the sprites, I found a post by TheNut at http://forum.devmaster.net/t/spritesheet-animation-in-opengl/24020 that outlines how I should think about building an animated sprite system in OpenGL. I investigated the code to look for where the UVs will be defined. I found them to be in sprite::render before they were pushed to the shader. Modifying the values led me to discover that the texture coordinates start from the bottom left. While keeping that information in the back of my mind, I started to develop the sprite animation code.

To avoid confusion while programming, the sprite class was separated into its own file and #included into invaderers_app.h. While TheNut on the Devmaster forum suggested having an XML file accompanying the sprite sheet, I decided on a simpler system where the sprites are laid out uniformly in a grid. The calculations for the positions and size for each frame of the sprite sheet will be done as the texture is loaded into the game.

The sprite is animated by assigning a frame number to each frame of the sprite sheet. As the frame number is iterated through, the coordinates for the corners of the frame are updated and sent through to the shader. The frame size is calculated by determining the number of frames in a row and in a column. The frame width and height as well as the texture width and height are then used to determine the top, bottom, left and right edges of the frame. These will be the coordinates that will be sent to the shader, instead of the whole texture.

The range of frames to be used for the animations can also be set as shown with the player's orientation affecting the direction the character is facing. These are a result of the sprite sheet containing animations for these directions.