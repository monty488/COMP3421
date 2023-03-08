# Assignment 2 Justification

If you think any of the questions within the sections are not applicable, please write "N/A".

## Section 1: Creation and Use of 3D Objects

### 1a: Show that you have created or imported at least one 3D object that is visible in your application. Include references to where this is implemented in your code.

When my program is run, there are two character models, two spheres, and a plane that acts as a floor. All the objects are imported from 
the res/obj folder (with each model having its own folder). In the code, the models are loaded in scene.cpp, with the paths to the obj files being defined as 
their own const char* at the top of the file, and they are imported using the load_obj function from model.cpp.

### 1b: Describe your scene graph and the hierarchy within the scene. Include references to where this is implemented in your code.

The scene graph consists of a plane defined in line 42 in scene.cpp, that is the highest in terms of heirarchy, with both the Cloud and Sephiroth model being the 2nd level of heirarchy within the scene graph. The two spheres that orbit each character are also children of the Cloud and Sephiroth models respectively, being the 3rd level
of heirarchy. In line 32 of scene.cpp, the light_sphere object is a child of the Cloud model. In line 39, the light_sphere_2 is a child of the Sephiroth
model. In line 46, both the Cloud and Sephiroth model are children of the plane object.

### 1c: Describe how your objects are moving or animating in realtime. Include code references (line numbers and function names) to use of delta time and also how this affects the scene graph.

The two spheres can be seen animated around each of the character models, one oribiting the Sephiroth model and one oribiting the Cloud model. Since the
spheres are children to their respective character model, they are animated following a circular path around their respective parent character model. In
animator.cpp, lines 128 and lines 132 show that both the LIGHT_SPHERE and LIGHT_SPHERE_2 are animated in regards to the current time given.

### 1d: Describe how you have used parametric splines in your application. Include code references to the implementation of control point based curves in your project.

I have used a parametric spline in order to animate both the light_sphere and light_sphere_2 such that they follow a circular path around their
respective character model. The control points are defined in the make_animator() function in animator.cpp in line 86, with the control points being
defined in lines 87 to 93 for s1, and lines 95 to 100 for s2. These control points create the parametric spline in the shape of a circle which the 
two light spheres are animated on.

## Section 2: Camera

### 2a: Describe what controls the player should use to move the camera in your scene. Include code references to the implementation of delta time control of speed and use of user input in your project.

When the program is run, the default camera is the free roam camera. The player can use the WASD keys to move up, left, down and right in the scene and
can use their mouse to look where they would want to go. Since this is the free roam camera, the player is able to fly around the scene. The camera is defined in scene.cpp and the update_camera function is called in line 53 to update the camera's position.

### 2b: Describe how your camera interacts with the scene. Is it able to "walk" on the Z-X plane or follow terrain? Include code references.

When the Z button is pressed, the camera chagnes from the free roam camera to the player camera, that is locked to a specific y axis so the player
is not able to fly as they could with the free roam character. In my camera.hpp, the struct defined in line 10 has a enum to determine what type of
cameras can exist, either FREE_ROAM, PLAYER or CUTSCENE. In scene.cpp, I have both a free_cam defined in line 10 which is the FREE_ROAM camera, and a 
player_cam in line 11 which is the PLAYER camera. These use the functions make_freeroam_camera and make_player_camera defined in camera.cpp which return 
a camera with the specific type that is specified. In scene.hpp, in the scene_t struct defined in line 36, I have a main_cam defined, and when the player 
presses the Z key, this will change the main_cam (which is by default set to the free_cam) to the player_cam. If the player presses the X key, it will change 
the camera to the free roam camera. This behaviour is defined in main.cpp in lines 42 to 47. In order to lock the player camera's y axis, the update_cam_pos 
function in camera.cpp defined in line 50 checks if the cam.kind is equal to the camera_t::PLAYER type.

### 2c: Describe how the view of your scene can change from player controlled to application controlled (specify user input that makes this change happen). Include code references to use of parametric curves and delta time in the application controlled camera.

I did not complete part 2c. (If you would like your 2c to be marked, you will need to replace this line)

## Section 3: Lighting

### 3a: Describe where Diffuse Lighting is clear to see in your application. Include code references to your implemented lighting (including where this is implemented in your shaders).

When the application is run, there is a directional light applied to the whole scene that is of a dark purple colour. There is also diffuse lighting from both of the two animated point lights which are the colour purple and green. In the default.frag file, the directional light diffuse colour is defined in line 30, and the diffuse lighting from the point lights are defined from the uniforms "u_light_color_1" and "u_light_color_2". The diffuse lighting of the directional light is calculated and added in line 52 and the diffuse lighting from the point lights is calculated in lines 55 and 56, and is added in lines 65 and 67. 

### 3b: Describe where Specular Lighting is clear to see in your application, including how the camera position affects the lighting. Include code references to your implemented lighting (including where this is implemented in your shaders).

When the application is run, the specular lighting can be seen from the purple and green point lights when they are shining on the plane ground, which uses a specular map so that the cracks in the texture will shine. Moving the camera will also adjust the lighting. The specular map is called in model.cpp in the load_obj function in line 105. This is then used to calculate the specular lighting in lines 59 and 60 in the fragment shader, and is then added to the final color in lines 66 and 67.

### 3c: Describe which of your light(s) in your scene are point light(s) and how you have placed objects in the scene to clearly show the point lights functioning. Include code references to point light implementation.

In my scene, the point lights are placed such that their position almost matches up with the positions of the oribiting spheres, and the point lights also move in a circular path similar to the oribiting spheres. The green point light is placed near the Cloud model and the purple point light is placed near the Sephiroth model. The point lights are initially defined in scene.cpp in lines 49 to lines 58 as light_1 and light_2. The uniform locations for the lights are defined in renderer.cpp in lines 25 to 28, and the lighting is set up in lines 106 to lines 110 so that they can be sent into the fragment shader.

### 3d: Describe all the lights in your scene and what type they are. Include code references to implementation of the capability to work with an arbitrary number of lights.

In total, the number of lights in my scene are a total of 3 lights, with one directional light that is dark purple lighting the whole scene, and two point lights that are moving in a ciruclar path, a purple point light orbiting around the Sephiroth model and a green point light orbiting around the Cloud model. The directional light is defined
in the fragment shader file "default.frag", and the 2 point lights are defined in the scene.cpp and sent into the fragment shader as uniforms.

### 3e: Explain what maps you have used and which objects they are on. Your application should clearly show the effect these maps are having on lighting. Include code references to maps on objects and vertices as well as lighting code that uses the maps.

There is a specular map applied to the plane object on the ground, and this is visible asthe cracks in the ground texture shine much brighter compared to the rest of the texture. The specular map is loaded from the plane.mtl file in line 105 of model.cpp. The material_t struct defined in model.hpp has a variable which stores the spec_map for the given object in line 29. This is then binded in line 53 in renderer.cpp so that it can be used in the fragment shader. In the default.frag shader file, the specular map (called u_spec_map) is then used in specular lighting calculations in lines 59 and 60.

## Section 4: Subjective Mark

### How have you fulfilled this requirement?

I have attempted to reference a scene from the 1997 game Final Fantasy 7.

### What is your vision for the scene you are showing?

My vision was to replicate the final battle scene between Sephiroth and Cloud from Final Fantasy 7.

### Are you referencing anything in this scene? Is this a quote or homage to any other art? Please describe it.

The scene I am attempting to reference is the final phase of the final battle from Final Fantasy 7, in which Cloud and Sephiroth are facing each other in a dark, empty setting. A video of this scene can be viewed here: https://www.youtube.com/watch?v=DP-E2xQmH5Y

The Cloud and Sephiroth model that I have used comes from Dissida: Final Fantasy, developed by Square Enix:
Cloud: https://www.models-resource.com/psp/dissidiafinalfantasy/model/18421/
Sephiroth: https://www.models-resource.com/psp/dissidiafinalfantasy/model/18417/

The texture for the plane that I have used comes from 3Dtextures.me:
Plane Texture: https://3dtextures.me/2021/10/23/surface-imperfections-cracks-001/

### Please give instructions for how a viewer/player should interact with this scene to see all the content you have created.

By default, the camera is set to free roam mode. You can use the WASD keys to move around and can look in any direction. If you would like to change the camera to the player camera, press the Z key. If you would like to change it back to free roam, press the X key.

## Section 5 (optional): Code Style Feedback

### There are no marks assigned to code style in this assignment. However, if you would like to receive some feedback on your coding style, please point out a section of your code (up to 100 lines) and your tutor will give you some written feedback on the structure and readability of that code.

Write your answer here (lines numbers or function names that you'd like reviewed)

## Section 6 (optional): Use of External Libraries

### What does the library do?

Write your answer here...

### Why did you decide to use it?

Write your answer here...

### How does this integrate with the assignment project build system? Please include any instructions and requirements if a marker needs to integrate an external library.

Write your answer here...
