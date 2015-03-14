//
//  ofxMacUtilsEncryption.h
//  Configurator
//
//  Created by Nick Hardeman on 3/14/15.
//

#pragma once
#include "ofMain.h"

class ofxMacUtilsEncryption {
public:
    ofxMacUtilsEncryption();
    
    void setPassphrase( string aPass );
    void setSalt( string aSalt );
    string getEncrypted( string aInput, bool bEncrypt );
    
    string salt, passphrase;
};
