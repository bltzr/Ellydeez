//
//  SerialIn.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 14/07/2018.
//

#include "SerialIn.hpp"

/* // we might need those for serial inputs
 
 // Serial messages management
 //
 void Serial::onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args)
 {
 // Decoded serial packets will show up here.
 SerialMessage message(args.getBuffer().toString(), "", 255);
 serialMessages.push_back(message);
 
 // ofLogNotice("onSerialBuffer") << "got serial buffer : " << message.message;
 }
 
 
 void Serial::onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args)
 {
 // Errors and their corresponding buffer (if any) will show up here.
 SerialMessage message(args.getBuffer().toString(),
 args.getException().displayText(),
 500);
 
 serialMessages.push_back(message);
 ofLogNotice("onSerialError") << "got serial error : " << message.exception;
 }
 */
