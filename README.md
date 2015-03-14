# ofxMacUtils

This class includes functions to make it easier to work with OSX applications. 
It was designed to configure OSX for long term installations.
Tested with OF v.0.08 and OSX 10.8 - 10.10.

This addon is evolving and new functionality is currently being added.

### CAUTION
Some of this functionality can be difficult to undo, for example accidentaly turning off screen sharing on a remote computer you don't have access to.

### Instafigurator
Added a GUI to easily configure a mac for a long term installtion.
![Instafigurator](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-14%20at%207.52.25%20PM.png)

### Example Functionality:
* Set Wifi to on, off.
* Set GateKeeper
* Disable Notification Center
* Disable / Enable Software Updates
* Disable Bluetooth and its notifications
* Disable Screen Saver
* Disable Power Saver
* Set the Desktop Image
* Take screen captures on all monitors
* Many more functions...

If you want to use some of the functionality, you need to activate some objective-c functionality. Add the following line to the project.xcconfig.
![project.xcconfig](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%204.52.06%20PM.png)

Any files that will be using ofxMacUtils with OFX_MAC_UTILS_USE_OBJ_C active need to be set to compile as Objective-C++ Source. You can do that by selecting the file and changing the type drop down to Objective-C++ Source. Don't forget to change main.cpp also! If you are still having trouble, try Project > Clean and then build again. See image below.
![Change source on main.cpp](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%204.52.31%20PM.png)

You can also set all the files in your project to compile as Objective-C++ Source in the Build Settings of the project. Using this method, you don't have to change each file individually, but all of your files need to be compatible with Objective-C++ (.h, .cpp, .mm, .m, etc.). See Image below.
![Change source on project](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%204.53.05%20PM.png)

Receiving this message? Look at the included PowerNotifications example on how to avoid it.
![Log Out Message](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%201.54.15%20PM.png)

