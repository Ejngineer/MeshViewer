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

![screenshot 4](https://user-images.githubusercontent.com/100335668/182234666-c33aa954-ce7f-4275-8c01-0ed125e54c02.jpg)
## Instructions

## Installation

## Known issues

## Future features

## Challenges


