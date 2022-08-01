# MeshViewer
3D graphics application for importing, viewing, and interacting with 3D models of various formats.

This application is written in C++ and uses the OpenGL (opengl 3.3) API. It is also my first computer graphics project that I built from scratch. C++ is highly optimizable and perfect for getting the best performance out of our computer hardware. OpenGL is very easy to use and allows our application to maintain a simplistic architecture relative to its function.  
 
Fig. 1 Mesh view of Stanford bunny 
![StanfordBunny 2](https://user-images.githubusercontent.com/100335668/182112038-b5b8b4bc-14e0-41f9-9cc3-fbba97fb12f2.jpg)

# Table of Contents
1. [Design](#Design)
2. [Installation](#Installation)
3. [Known issues](#Knownissues)
4. [Future features](#Futurefeatures)
5. [Challenges](#Challenges)
## Design
MeshViewer is an Object Oriented app designed to be easy to use and easily scaled for storing and interacting with a large number of models. The structure of the software is kept simple and makes use of only a few design patterns (Factory, Singleton, etc). MeshViewer also makes use of several open source third party software. This includes:
* GLFW for creating windows
* Glad OpenGL loader/generator
* Open Asset Importing (ASSIMP)
* GLM math library 
* ImGui Ui library 
* Jsoncpp for parsing json files in C++
* stb_image for loading textures

## Installation

## Known issues

## Future features

## Challenges


