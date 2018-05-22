This openFrameworks application allows to send images to APA102 LED strips (and, optionally, DMX) through a bunch of teensy-based bridge applications (code included as a submodule) via SLIP-OSC.

Some ofAddons are necessary to build this app:
- https://github.com/bakercp/ofxSerial.git  which itself requires ofxIO:
- https://github.com/bakercp/ofxIO.git (on branch stable)
- https://github.com/astellato/ofxSyphon.git (on the Mac)

It runs on Mac. Raspberry Pi will soon be supported as wel

This Application has been initially developed for the [Nebula art project](http://www.baltazars.org/project/nebula/).
Thanks to @avilleret for initial help!