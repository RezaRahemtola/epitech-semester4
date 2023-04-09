# Arcade - Libraries documentation

This project is composed of 3 parts:
- the graphics libraries, which are dynamic libraries (`.so`) used to display elements and retrieve user inputs
- the game libraries, which are dynamic libraries (`.so`) containing the logic of an arcade game and capable to react to inputs and return elements to display
- the `Core` which handles the main loop & logic to connect a game library and a graphics library loaded at runtime


This document will help you to implement new graphics or game libraries and use them with this Arcade project.

> 💡 Any library created following this document will also be compatible with the project of the group given in [the main README](/README.md)


## Graphics

A graphics library has several objective:
- Display elements given to it by the `Core`
- Retrieving user inputs to send them to the `Core`

To implement a graphics library, you have to create a class inheriting `IDisplayModule` defined in [this common file](/include/common/display/IDisplayModule.hpp)

It contains two notable methods:

### Display
```cpp
void display(const Data &data);
```
This `display` method receives a [`Data`](/include/common/Data.hpp) object (which is sent by the game library, for more information look at [the games section](#games)).\
It contains multiple vectors of elements, like sprites, texts, sounds...\
The implementation of the rendering of these elements is up to you: you can create sub-methods like `displaySprites` or `displayTexts` for example.
> 💡 Each sprite contains a position, which is given in the range of the `mapWidth` / `mapHeight`, it's also up to you to adapt it's rendering to the size of your window.

### Input
```cpp
std::optional<Input> getInput();
```
This `getInput` method is called by the `Core` to retrieved a potential user [`Input`](/include/common/Input.hpp).\
You have to implement it to retrieve events emitted in your window.\
You can map any user input (keyboard, mouse...) to each of the [type of Inputs available in the `enum`](/include/common/Input.hpp) and return it.
> 💡 If no event is found, you can return a `std::nullopt`, which will be handled correctly in the core to avoid passing it to the game.

## Games

A game library has several objective:
- Handle its logic internally
- React to given input to update to internal game state
- Return the current elements of the game in a common format to pass it to the `Core`

To implement a game library, you have to create a class inheriting `IGameModule` defined in [this common file](/include/common/game/IGameModule.hpp)

It contains two notable methods:

### Input
```cpp
void handleInput(Input in);
```
This `handleInput` method is called by the `Core` to pass an [`Input`](/include/common/Input.hpp) (itself retrieved by a graphics library).\
You have to implement it to react accordingly in your game, to move a player for example.

### Tick
```cpp
Data &tick();
```
This `tick` is used bu the `Core` to retrieve a [`Data`](/include/common/Data.hpp) object representing the current state of the game with its elements (sprites, texts, sounds...).\
Its implementation depends once again on the internal logic of your game. You could build your game logic to have a single data object which you will interact with and directly return in this method.
> 💡 This data will be passed by the `Core` to a graphic library (see the [graphics section](#graphics) for more details)


## Support
If you have any questions about this document, you can send a mail to `reza.rahemtola@epitech.eu`

## Author
| [<img src="https://github.com/RezaRahemtola.png?size=85" width=85><br><sub>Reza Rahemtola</sub>](https://github.com/RezaRahemtola)
|:---:
