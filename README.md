# FabKit

## Introduction

FabKit is an object-oriented UI library for C++ made with SDL3 using its SDL_GPU backend. It aims to be a jumping-off point for 2D game projects, although it can be used as a GUI for other desktop applications as well.

## Features

- Wrappers around SDL objects like sounds and textures that manage the object lifecycle for you
- A number of extendable UI components such as buttons, text input, and dropdowns
- A screen management system that handles screen history along with all of the object management that goes along with that
- A configuration template for setting up configuration files for your program

## Requirements

- C++ 23
- Only MSVC is supported as a build system at this time

While this should work with Linux/Mac, I've only tested this with Windows

## Credits

The following libraries are used:
- SDL3: https://github.com/libsdl-org/SDL
- Glaze: https://github.com/stephenberry/glaze
