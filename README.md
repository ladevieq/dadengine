# DadEngine

## Warning
As this is a project i'm currently working on, the README file will evolve as the project growth.

## Description
This is my second attempt to create a fully fonctionnal engine almost from scrath.

## Core
The core library implements all the platform dependent features as the IO api, threads and so on. These are implemented in a basic, simple and unoptimized way.

## Math
Similarly to the core library, the maths library has been implemented in a very basic way and some things are functions missing. Later on it will use vector registers supported by the target.

## Graphic engine
The graphic engine implement Vulkan has the main rendering API. In case the target doesn't support enough Vulkan extensions the graphic engine will fallback to the OpenGL implementation.


* ### OpenGL
    The OpenGL version used is 4.1 because it's the first version where the GLSL version is compatible for both OpenGL and Vulkan.

    I have also created my own OpenGL wrapper, instead of one that already exist.

* ### Meshes formats
    The supported meshes formats will be [GLTF 2.0](https://github.com/KhronosGroup/glTF) and FBX, except if i use [Assimp](http://assimp.sourceforge.net/) to load assets.

* ### Textures formats
    Almost all images formats will be supported.
