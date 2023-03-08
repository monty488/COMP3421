# Assignment 1 Justification

If you think any of the questions within the sections are not applicable, please write "N/A".

## Section 1: It runs

### How have you fulfilled this requirement?

My code compiles and runs on Windows OS with no errors as well as displays the window.

### When your application is run, what should the tutor look for or do to see that you have fulfilled this requirement? 

The OpenGL Window displays when the code is running.

### Where in the code should tutors look to see that you've fulfilled this requirement?

The window created in line 115, and the main while loop in line 175, which displays the window.


## Section 2: Visibility & Shaders

### How have you fulfilled this requirement?

I have one fragment shader and two vertex shaders (one for the background, and one for the individual sprites displayed on the screen).
My vertex shaders are called bg_vert.glsl and sprite_vert.glsl, and it is in the res/shaders/ folder
My fragment shader is called frag.glsl and it is in the res/shaders/ folder.

These shaders are visible when you run the code, as the background and sprites are all displayed on the screen.

### When your application is run, what should the tutor look for or do to see that you have fulfilled this requirement?

The background, and the 4 meshes that are displayed on the screen.

### Where in the code should tutors look to see that you've fulfilled this requirement?

The shader files bg_vert.glsl, sprite_vert.glsl, and frag.glsl.
In my code, lines 119, 121, and 123 make the shaders, and add them to the programs
in lines 125 and 126.

In the main render while loop, the programs are used in line 187 and line 192.

## Section 3: Creation and Use of 2D Shapes

### How have you fulfilled this requirement?

I have completed 3a and 3b by displaying 5 rectangles on the screen, 1 for the background and 4 for the sprites.
I have completed 3c and 3d by scaling each of the sprites as well as animating a transform on the bigger sprite
for it to move up and down the screen.


### When your application is run, what should the tutor look for or do to see that you have fulfilled this requirement?

The background, and the 3 animated sprites on the right and the 1 larger sprite on the left of the screen.

### Where in the code should tutors look to see that you've fulfilled this requirement?

My "mesh_t make_mesh" function in line 67 will create the 2D shapes, and I use this function in the
main function to create the meshes from line 133 to line 137. In the render while loop that begins 
in line 175 contains the code that displays the meshes on the screen. Line 186 is where I begin drawing 
the background on the screen. Line 198 is where I draw one of the bigger rectangles on the screen. 
Line 247 is where I draw the 3 smaller rectangles on the screen.

## Section 4: Use of Textures

### How have you fulfilled this requirement?

I have completed 4a and 4b By displaying multiple textures on the screen. I have textured the background as well as the
4 sprites on the screen with blending enabled for transparency. 
I have completed 4c by having 3 of the meshes change textures every 0.2 seconds when the code is run, making them animated.

My textures are in the res/img/ folder, res/img/background.png is the texture for the background,
res/img/sephiroth.png is the texture for the big mesh on the left of the screen,
and each of the 3 smaller meshes on the right side of the screen have folders for each of their sprites
res/img/barret/, res/img/cloud/ and res/img/tifa/ since they have multiple textures that change every 0.2 seconds.

### When your application is run, what should the tutor look for or do to see that you have fulfilled this requirement?

In the window, the background, and the 4 sprites on screen are all textured, with 3 of the smaller sprites
on the right side of the screen being animated, and the larger sprite on the left side animated with a matrix
transform to move up and down.

### Where in the code should tutors look to see that you've fulfilled this requirement?

The textures that are made in lines 144 to 167, and the textures are binded in the main
loop in lines 189, 200, 249, 254, and 259. I also have a switch statement in line 208 that 
sets the correct texture for the meshes that are animated depending on the time passed, such that
every 0.2 seconds the texture is changed.

### Section 5: Subjective Mark

### How have you fulfilled this requirement?

My project references the 1997 game Final Fantasy 7. Specifically, I am referencing the final boss fight
of the game, where a party of 3 characters (in my case, the three characters are Cloud, Barret and Tifa) 
are fighting the final boss named "Sephiroth" in one of his last forms, known as his "Safer" form.
(A video showing the fight can be seen here: https://www.youtube.com/watch?v=Yi60o4oYak0).

The textures for Cloud, Barret and Tifa I have used come from Final Fantasy: Brave Exvius,
developed by Gumi, Alim Co., Ltd and published by Square Enix:
Cloud: https://www.spriters-resource.com/mobile/finalfantasybraveexvius/sheet/138405/
Barret: https://www.spriters-resource.com/mobile/finalfantasybraveexvius/sheet/138407/
Tifa: https://www.spriters-resource.com/mobile/finalfantasybraveexvius/sheet/102937/

The texture for Sephiroth I have used comes from Pictlogica: Final Fantasy,
developed by Jupiter Corporation and publised by Square Enix:
Sephiroth:https://finalfantasy.fandom.com/wiki/Safer%E2%88%99Sephiroth?file=PFF_Safer_Sephiroth.png

The background I have used comes from Final Fantasy 6, developed and published by Square Enix:
https://www.spriters-resource.com/snes/ff6/sheet/54685/

### When your application is run, what should the tutor look for or do to see that you have fulfilled this requirement?

The big sprite on the left is Sephiroth, and on the right the 3 smaller sprites are Cloud, Barret and Tifa.

### Where in the code should tutors look to see that you've fulfilled this requirement?

The textures that are made in lines 144 to 167, as well as the main while loop to render
all the meshes onto the screen.

## Use of External Libraries

### What does the library do?

N/A

### Why did you decide to use it?

N/A