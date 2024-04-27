# Ultimate Spider-Man Debug menu for PC 

**Recreation** of the PS2 version's debug menu for the PC version

## Download

Get the menu from [here](https://github.com/krystalgamer/usm-debug-menu/releases)

## Installation

* Rename `binkw32.dll` in the game's folder to `binkw32_.dll`
* Copy the `binkw32.dll` in the zip file to the game's folder

## Usage

* **INSERT** - opens and closes the menu
* **UP/DOWN Arrows** - moves the current select option up and down
* **ENTER** - executes the selected option
* **LEFT/RIGHT Arrows** - changes the value of the current **boolean** option
* **ESCAPE** - go to previous menu

## Current implemented options

### Warp

Allows to teleport to any in-game region

**NOTE**: Points of Interest(POI) are only used in missions and the option only works when the direction arrow is visible 

### District variants

Allows to switch between variants of given regions

### Char Select

Allows to switch between *all* available characters

**NOTE**: `peter_parker` and `peter_hooded` are versions of peter without powers, used in the first missions of the game

### Options

Allows to modify in-game flags that controls certain behaviours

* Live in Glass House: disables the `Area unavailable` messages

### Script

Access to in-game scripts that allow the player to tap into debug features

### Progression

Set your progress to any point in the game

### Camera

Allows to switch between 3 cameras: player chase camera, user camera and scene analyzer camera (the functionality of the last camera is still unknown).

#### Usage of user camera

* **T** - lock/unlock camera target to character 
* **I** - move camera forward  
* **K** - move camera backward
* **O** - move camera up 
* **U** - move camera down 
* **J** - move camera left 
* **L** - move camera right 
* **Right Shift** - speed up the camera 
* **Right Alt** - slow down camera 


## Extending functionality

If you desire to add any new option(s) to the menu, it's very simple.
`create_menu` is used to create a new menu.
`add_debug_menu_entry` is used to add entries to a menu.


## License

This project is MIT licensed
