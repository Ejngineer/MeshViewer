# MeshViewer
3D graphics application for importing, viewing, and interacting with 3D models of various formats.

This application is written in C++ and uses the OpenGL (opengl 3.3) API. It is also my first computer graphics project that I built from scratch. C++ is highly optimizable and perfect for getting the best performance out of our computer hardware. OpenGL is very easy to use and allows our application to maintain a simplistic architecture relative to its function.  
 
Fig. 1 Mesh view of Stanford bunny 
![StanfordBunny 2](https://user-images.githubusercontent.com/100335668/182112038-b5b8b4bc-14e0-41f9-9cc3-fbba97fb12f2.jpg)

# Table of Contents
1. [Design](#Design)
2. [Instructions](#Instructions)
3. [Installation](#Installation)
4. [Known Issues](#Known-Issues "Goto Known Issues")
5. [Future features](#Future-features "Goto Future features")
6. [Challenges and Experience](#Challenges-and-Experience)

## Design
MeshViewer is an Object Oriented app designed to be easy to use and easily scaled for storing and interacting with a large number of models. The structure of the software is kept simple and makes use of only a few design patterns (Factory, Singleton, etc). MeshViewer also makes use of several open source third party software. This includes:

* GLFW for creating windows
* Glad OpenGL loader/generator
* Open Asset Importing (ASSIMP)
* GLM math library 
* ImGui Ui library 
* Jsoncpp for parsing json files in C++
* stb_image for loading textures

Other than this, everything is built from scratch. MeshViewer is made up of three main components.The Window class is responsible for creating our window context that everything with be drawn on. It is also used for loading the opengl implementaion using GLAD. The UI class is responsible for setting up and drawing the UI using ImGui and Jsoncpp. Lastly, our Renderer class is responsible for drawing our 3D models and acts as a factory for model and light objects. 

Some of the main features provided by MeshViewer include:
* Ability to add new models without needing to touch internal functionality
* Extensive options for interacting with models (Transform, Color, lighting, render modes)
* Support for multiple file formats
* Lightweight bloat free application 

Fig. 2 Point view of 3D skull model
![screenshot 4](https://user-images.githubusercontent.com/100335668/182234666-c33aa954-ce7f-4275-8c01-0ed125e54c02.jpg)
*NOTE: Unfortunately the skull model is not included in this project due to being an OBJ file. I can manually add the file but GitHub Limits file sizes to 25 MB
(May use git LFS in the future)

## Instructions
#### Adding models
MeshViewer creates a list of all possible models that can be loaded in from a json file. The json is initially empty with the exception of two hardcoded models. These are for getting familiar with the app's core functions. Adding new models is simple and requires that the files for that model be placed in a folder on your local machine. It is best to store the files for the model in the same directory as the app. To add additional models to the json file simply follow this format.

***{
"name": "Example",
"ObjNo": 123,
"Uitype": "Example",
"Texture": false,
"Path": "Example/Path"
}***

The "name" element decides the name that will show up in the UI drop down list to identify the model. ObjNo designates where in the json list the model is located. Note, the ObjNo needs to start from 0 to the nth entry in the json list. The first two elements are our hardcoded geometries so the first model entry will start with ObjNo 2. From there ObjNo should be incremented by ***ONE*** for each additional model. It shoudl also be noted that duplicate ObjNo can cause issues in the program. The Uitype tells the program how the UI elements should be drawn and which options will be avaible. Currently, there are three type "TwoD", "ThreeD", "Model". All models that come from a file (ex. OBJ, DAE, FBX) should have a Uitype of "Model". 

* *Ignore the texture element, this feature has not been implemented yet.*

Finally, the path entry provides the location of the model files for the application to load in. Everything that needs to be done is complete and the model should be possible to load into the application.

#### Using the app
Using the ImGui framework, MeshViewer is able to provide an extensive set of options for interacting with models. The UI window is fixed to the right and intially shows only a dropdown list of all the objects that can be rendered. When an object is picked, and depedning on the type of object choses, additional UI elements are drawn. This inlcudes multiple sliders for modifying the object's transform Data, color, ambient color, and specular component. There will also be opetions on how the Object is rendered (Filled, Line, Point) and with which shaders (Default, Phong). MeshViewer also supports lighting effect with similar options to the model options such as changing color and position. Currently, MeshViewer supports having 16 point lights and 16 directioanl lights.


Fig. 3 Typical UI setup in MeshViewer

![UI 2](https://user-images.githubusercontent.com/100335668/182348235-6d36b61b-7c64-49c8-8711-b8e3ff2f2f10.jpg)


## Installation
To use the app, simply download a zip file of this repository. The .exe file is located in the MeshViewer directory. Simply run the executable and the app should work. Please note, that this app has only been tested on Windows 8.1 and windows 10.

## Known Issues
* some .dae files have an issue where the index count label and actual number of index values are different, casuing an error in ASSIMP.
* OBJ files cause issues when included in Visual Studio C++ projects due to obj extensions files getting ignored and causing conflict with C++ obj files
 
## Future features
 * Textures
 * Skyboxes
 * Child mesh interactiblity
 * Flash/Spot light support
 * Normal/Parallax Mapping
 * Console UI window
 * Top window support for messages/errors

## Challenges and Experience
This is my first attempt at developing standalone graphics applications from scratch. This project has taught me alot not just about graphics but also about software design. It is the culmination of months of self study and prototyping in computer graphics. Like any project, there were multiple roadblocks and challenges that arise from being new to a field and using unfamiliar technology. 
 
Firstly, the design process was exceptionally difficult in comparison to other projects I have done. Deciding exactly what the application should be is a long and complex process that I do not yet have an expertise in. Approahcing the problem slowly and investing the time to design makes the later steps of development easy and manageable. Keeping the application simple and focused while ensuring at least one major factor that seperates our application from others out there makes the endeavor much more valuable. 

The next biggest issue was learning the various third party softwares necessary to develop our app. For exmaple, ImGui has many features useful for creating elegant and complex UIs. However, due to this rich set of features, it can be difficult to know which ways to construct a UI follows best practices. Of course, reading documentation is key in these circumstances and provides a way to always know that best practices are being followed.   

 Fig 4. Mesh View of Teapot
![screenshot 3](https://user-images.githubusercontent.com/100335668/182384197-7d40dc2d-0a70-4b8b-8903-e04f38952dd2.jpg)


