This openFrameworks application allows to send images to APA102 LED strips (and, optionally, DMX) through a bunch of teensy-based bridge applications (code included as a submodule) via SLIP-OSC.

Some ofAddons are necessary to build this app:
- https://github.com/bakercp/ofxSerial.git  which itself requires:
- https://github.com/bakercp/ofxIO.git (on branch stable)
- https://github.com/astellato/ofxSyphon.git (on the Mac)
