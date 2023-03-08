# Assignment 3 Justification

If you think any of the questions within the sections are not applicable, please write "N/A".
If you are answering a criteria in a different section, please describe that like: "4a. This criteria is met by the implementation described in 2b."

## Section 1: Design Pitch. Describe a possible setting and what kind of graphics technology would be necessary to implement this. These components do not have to be implemented in this project. Suggestion: 200 words should be more than enough for this.

In this game, you wake up in what seems to be a city in the sky with no memories and with the power to see things that other people cannot normally see. There are corrupt spirits lurking all around you, and you are able to see and open portals that take you to other sky cities. The game is a 1st person action-adventure game. Your goal is to defeat and find the source of all the corrupt spirits that exist in all the sky cities.

The game will be using motion blur and cel-shading in order to invoke the feeling that you are in the sky. The game will also make use of frame buffers to switch between both the normal view and the inverted view that lets you see all the corrupted spirits, as well as to display the portals to other cities. Since the game prominently takes place in the sky cities, cube mapped and skybox reflections will be used. The game should also be able to handle multiple scenes and seamlessly being able to switch between the scenes through the portals. HDR will also be used to dynamically adjust the exposure from dark and light settings so that the player is able to view their surroundings easily.


## Section 2: Advanced Lighting

### 2a: Blinn-Phong Lighting. Include code references to the implementation of lighting in your project.

I have implemented blinn-phong lighting on the blue spot light in my scene. The blue spot light is visible on the stage in my scene. The spot light is defined in my renderer.hpp, with line 31 defining the blue specular colour of the spot light. This is then sent in as a uniform into the fragment shader in line 172 in renderer.cpp. In the shader.frag fragment shader, in line 74-79, I define the light direction, view direction and the halfway direction, which is used in calculating the colour of the specular lighting.

### 2b: High Dynamic Range. Show use of an intermediate frame buffer to store light values > 1.0 and how that is converted to Low Dynamic Range. Include code references.

In my scene, I have used exposure tone mapping HDR. In my renderer.hpp, I have defined light values higher than 1.0 in lines 23 and 31. In my renderer.cpp, I set the hdr program vert and frag shader in line 73. In my main.cpp, in line 53 I have defined a frame buffer which I will use to apply the post processing on. I have also defined the screen quad in line 56. I render the scene to the frame buffer in line 95, and then apply the HDR post processing in line 96. The function post_process in my renderer.cpp at line 200 uses the renderer.hdr_program to set the correct vertex and fragment shader which applies the tone mapping.

## Section 3: Reflections

### 3a: Environment Mapped Reflections. Show at least one object can reflect a cube map. Cube map can be a preprepared skybox and the object doesn't need to reflect other objects in the scene. Include code references to implementation.

I have environment mapped reflections visible on the cube in the middle of the stage in the scene, which reflects the cubemapped skybox. In main.cpp, I create the cubemap the cube object will use in line 57, and then send this into the make_cube_volume function in line 59. The cube map texture is set in line 119 in scene.cpp. In line 126 in renderer.cpp, a uniform is set in the fragment shader to check if the surface is reflective. In the shader.frag file, in line 122, I check if the surface is reflective, and then calculate the I and R vector to calculate the reflection and set the fFragColour texture to the skybox texture.

### 3b: Realtime Cube Map. Describe how the cube map is created during the frame render and then used for a reflective object. Include code references to the generation of the cube map (3a should already describe the reflection process).

I did not complete part 3b. (If you would like your 3b to be marked, you will need to replace this line)

### 3c: In-World Camera/Magic Mirror. Describe how you have placed a camera in a scene that renders to a texture. Show where both of these objects are and how they function to show a different viewpoint of the scene. Include references to code.

I have a In-World Camera screen that is visible behind the desks and chairs in the scene. The screen displays the player's camera. I first create a frame buffer for the screen in line 55 of main.cpp. In line 83-87 of main.cpp, I bind this framebuffer and then render the scene, whilst also making the screen object itself invisible, so that there are no visual glitches since what is displayed on the screen will not contain the screen itself.

### 3d: Planar Reflections. Describe the system used to generate a planar reflection, including any techniques for perspective and/or near plane correction. Include references to code.

I did not complete part 3d. (If you would like your 3d to be marked, you will need to replace this line)

## Section 4: Post Processing

### 4a: Simple Colour Change. Describe how this project uses a framebuffer and what change is made to the colour data, including references to where this is implemented in code.

I have a simple colour change framebuffer that inverts the colours displayed on the screen. When the player preses the space bar, the colours on the screen invert. Pressing space again reverts the colours back to normal. I make the screen framebuffer and the screen quad in lines 53 and 56 in my main.cpp. A boolean is defined in line 74, which determines if the colours on the screen need to be inverted/reverted. the glfwSetKeyCallback function in line 76 is set to check when the user presses space to set the boolean to either true or false. The screen is rendered to the screen framebuffer in line 95 of main.cpp and the post processing applied in line 96 displays the post processed scene to the player. In renderer.cpp, the invert_program is set in line 74, and the post_process function in line 200 checks if the invert_colours boolean is set, and then sets the program to use.

### 4b: Use of Kernels. Describe the kernel sampling technique in use, including code references.

I did not complete part 4b. (If you would like your 4b to be marked, you will need to replace this line)

### 4c: Multiple Intermediate Framebuffers. Show use of more than one framebuffer for post processing (like chaining two post processing effects in a row). Include references to code.

I did not complete part 4c. (If you would like your 4c to be marked, you will need to replace this line)

### 4d: Multiple Render Targets. Describe how this project uses multiple frame buffers to write information from the initial fragment shader pass and how it uses them in post processing. Include references to fragment shader output code as well as post processing code.

I did not complete part 4d. (If you would like your 4d to be marked, you will need to replace this line)

### 4e: Temporal Post Processing. Show storage of framebuffers from previous frame(s) and how they are being used in post processing. Include references to where this is happening in code.

I did not complete part 4e. (If you would like your 4e to be marked, you will need to replace this line)

## Section 5: Show Me What You Got. Implement any techniques that are not part of previous criteria for assignments in this course. This is open, so must be documented clearly with code references to show what has been created to add to the visual effects of the scene or objects in it. 

I did not complete part 5. (If you would like your 5 to be marked, you will need to replace this line)

## Section 6: Subjective Mark

### How have you fulfilled this requirement?

In my project, I have created what it would be like to traverse the sky cities, with the stage being set in the floating sky, surrounded by the skybox, with the ability
to invert the colours.

### What is your vision for the scene you are showing?

My vision for this scene was to replicate the feeling of being in the sky cities that I had explained in my design pitch.

### Are you referencing anything in this scene? Is this a quote or homage to any other art? Please describe it.

The stage object that I have used is the Melancholic Girl stage from Hatsune Miku: Project Mirai 2, developed and published by SEGA.
Link: https://www.models-resource.com/3ds/hatsunemikuprojectmirai2/model/44508/

The skybox textures that I have used are the Sky Box - Sunny Day textures from opengameart.org, with edited colours.
Link: https://opengameart.org/content/sky-box-sunny-day/

### Please give instructions for how a viewer/player should interact with this scene to see all the content you have created.

You can move around the scene using the camera and the WASD keys. You can also use the R and F keys to move up and down the scene vertically. Pressing the Space key will invert the colours on the screen, and pressing Space again will revert them back to normal.

## Section 7 (optional): Code Style Feedback

### There are no marks assigned to code style in this assignment. However, if you would like to receive some feedback on your coding style, please point out a section of your code (up to 100 lines) and your tutor will give you some written feedback on the structure and readability of that code.

Write your answer here (lines numbers or function names that you'd like reviewed)

## Section 8 (optional): Use of External Libraries

### What does the library do?

Write your answer here...

### Why did you decide to use it?

Write your answer here...

### How does this integrate with the assignment project build system? Please include any instructions and requirements if a marker needs to integrate an external library.

Write your answer here...
