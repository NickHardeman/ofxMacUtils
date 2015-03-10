# ofxMacUtils

This class includes functions to make it easier to work with OSX applications. 
Tested with OF v.0.08 and OSX 10.8 - 10.10.

If you want to use some of the functionality, you need to activate some objective-c functionality. Add the following line to the project.xcconfig.
![project.xcconfig](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%204.52.06%20PM.png)

Any files that will be using ofxMacUtils with OFX_MAC_UTILS_USE_OBJ_C active need to be set to compile as Objective-C++ Source. You can do that by selecting the file and changing the type drop down to Objective-C++ Source. Don't forget to change main.cpp also! See image below.
![Change source on main.cpp](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%204.52.31%20PM.png)

You can also set all the files in your project to compile as Objective-C++ Source in the Build Settings of the project. Using this method, you don't have to change each file individually, but all of your files need to be compatible with Objective-C++ (.h, .cpp, .mm, .m, etc.). See Image below.
![Change source on project](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%204.53.05%20PM.png)

Receiving this message? Look at the included PowerNotifications example on how to avoid it.
![Log Out Message](https://github.com/NickHardeman/ofxMacUtils/blob/master/ReadMeImages/Screen%20Shot%202015-03-10%20at%201.54.15%20PM.png)

