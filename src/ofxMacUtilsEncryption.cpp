//
//  ofxMacUtilsEncryption.cpp
//  Configurator
//
//  Created by Nick Hardeman on 3/14/15.
//

#include "ofxMacUtilsEncryption.h"

#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CipherFactory.h"

//--------------------------------------------------------------
ofxMacUtilsEncryption::ofxMacUtilsEncryption() {
    setSalt( "thisIsTheDefaultSalt_callSetSaltToChangeIt" );
    setPassphrase( "openframeworks_cc" );
}

//--------------------------------------------------------------
void ofxMacUtilsEncryption::setPassphrase( string aPass ) {
    passphrase = aPass;
}

//--------------------------------------------------------------
void ofxMacUtilsEncryption::setSalt( string aSalt ) {
    salt = aSalt;
}

//--------------------------------------------------------------
string ofxMacUtilsEncryption::getEncrypted( string aInput, bool bEncrypt ) {
    
    if( aInput == "" ) {
        cout << "getEncrypted :: password is empty " << endl;
        return "";
    }
    
    string password = aInput;
    Poco::Crypto::CipherKey key( "des3", passphrase, salt );
    
    Poco::Crypto::CipherFactory& factory = Poco::Crypto::CipherFactory::defaultFactory();
    
    string encrypted = "";
    string decrypted = "";
    
    try {
        Poco::Crypto::Cipher* pCipher = factory.createCipher( key );
        encrypted = pCipher->encryptString(aInput, Poco::Crypto::Cipher::ENC_BASE64);
        
        if( !bEncrypt ) {
            decrypted = pCipher->decryptString( aInput, Poco::Crypto::Cipher::ENC_BASE64);
        }
    } catch( Poco::Exception& e ) {
        cout << "Error : " << e.displayText() << endl;
        return "";
    }
    
    if( bEncrypt ) return encrypted;
    return decrypted;
}













