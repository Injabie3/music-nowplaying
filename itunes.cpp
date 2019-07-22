#include <iostream>
#include <string>
#include "iTunesCOMInterface.h"
using namespace std;

int main() {
    HRESULT hResult;
    IiTunes* application;
    IITTrack* track;
    BSTR* strCurrTrackName = new BSTR; 
    BSTR* strPrevTrackName = new BSTR;
    BSTR* strCurrArtistName = new BSTR; 
    BSTR* strPrevArtistName = new BSTR;
    BSTR* strCurrAlbumName = new BSTR;
    BSTR* strPrevAlbumName = new BSTR;

    *strPrevTrackName = (BSTR)"";
    *strPrevArtistName = (BSTR)"";
    *strPrevAlbumName = (BSTR)"";

    setlocale(LC_ALL, "Japanese"); // Must do this or else wcout will not print Japanese characters.
    CoInitialize(NULL); // Must do this before doing CoCreateInstance

    // Instantiate the COM interface to iTunes (as per the iTunes COM Interface Reference from Apple)
    hResult = CoCreateInstance(CLSID_iTunesApp, NULL, CLSCTX_LOCAL_SERVER, IID_IiTunes, (PVOID *)&application);
    
    if (hResult != S_OK) {
        cerr << "There was a problem creating the iTunes application object!";
    }
    else {
        while (true) {
            hResult = application->get_CurrentTrack(&track);
            if (hResult == S_OK) {
                track->get_Name(strCurrTrackName);
                track->get_Artist(strCurrArtistName);
                track->get_Album(strCurrAlbumName);
                if (wcscmp(*strCurrTrackName, *strPrevTrackName) != 0 ||
                    wcscmp(*strCurrArtistName, *strPrevArtistName) != 0 ||
                    wcscmp(*strCurrAlbumName, *strPrevAlbumName) != 0) {
                    wcout << "Name  : " << *strCurrTrackName << endl;
                    wcout << "Artist: " << *strCurrArtistName << endl;
                    wcout << "Album : " << *strCurrAlbumName << endl;
                }

                *strPrevTrackName = *strCurrTrackName;
                *strPrevArtistName = *strCurrArtistName;
                *strPrevAlbumName = *strCurrAlbumName;

                Sleep(5000);
            }
        }
    }

    return 0;
}

