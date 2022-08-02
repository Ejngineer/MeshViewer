# MeshViewer
3D graphics application for importing, viewing, and interacting with 3D models of various formats.

This application is written in C++ and uses the OpenGL (opengl 3.3) API. It is also my first computer graphics project that I built from scratch. C++ is highly optimizable and perfect for getting the best performance out of our computer hardware. OpenGL is very easy to use and allows our application to maintain a simplistic architecture relative to its function.  
 
Fig. 1 Mesh view of Stanford bunny 
![StanfordBunny 2](https://user-images.githubusercontent.com/100335668/182112038-b5b8b4bc-14e0-41f9-9cc3-fbba97fb12f2.jpg)

# Table of Contents
1. [Design](#Design)
2. [Instructions](#Instructions)
3. [Installation](#Installation)
4. [Known issues](#Knownissues)
5. [Future features](#Futurefeatures)
6. [Challenges](#Challenges)
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
Using the ImGui framework, MeshViewer is able to provide an extensive set of options for interacting with models. The UI window is fixed to the right and intially shows only a dropdown list of all the objects that can be rendered. When an object is picked, and depedning on the type of object choses, additional UI elements are drawn. This inlcudes multiple sliders for modifying the object's transform Data, color, ambient color, and specular component. There will also be opetions on how the Object is rendered (Filled, Line, Point) and with which shaders (Default, Phong). MeshViewer also supports lighting effect with similar options to the model options such as changing color and position. Currently there are two different light supported by MeshViewer.


Fig. 3 Typical UI setup in MeshViewer

![UI 2](https://user-images.githubusercontent.com/100335668/182348235-6d36b61b-7c64-49c8-8711-b8e3ff2f2f10.jpg)


## Installation

## Known issues

## Future features

## Challenges



