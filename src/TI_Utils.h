/*
 *  TI_Utils.h
 *  openFrameworks
 *
 *  Created by Pat Long on 15/12/08.
 *  Copyright 2008 Tangible Interaction. All rights reserved.
 *
 */
#ifndef _TI_UTILS
#define _TI_UTILS

#include "ofMath.h"
#include "ofTypes.h"
#include "ofUtils.h"
#include "ofGraphics.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
//using namespace std;

float tiAngle(float dx, float dy);
float tiAngle(float x1, float y1, float x2, float y2);
float tiAngleXComponent(float angle, float magnitude=1.0, bool radians=false);
float tiAngleYComponent(float angle, float magnitude=1.0, bool radians=false);
float tiAngleToRadians(float angle);
float tiRadiansToAngle(float radians);
float tiNormalizeAngle(float angle);
float tiDistance(float dx, float dy);
float tiDistance(float x1, float y1, float x2, float y2);
float tiAbs(float num);

bool timeInRange(int cHour, int cMin, int startHour, int startMin, int stopHour, int stopMin);
bool timeInRange(string cTime, string startTime, string endTime);

// string split functions. Source: http://stackoverflow.com/questions/236129/c-how-to-split-a-string/236803#236803
vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

// replaces all instances of searchString with replaceString in theString. Source: http://www.java2s.com/Code/Cpp/Data-Type/StringFindandreplace.htm
string stringReplace(string theString, string searchString, string replaceString);

// converts a string to any type. Source: http://www.codeguru.com/forum/showthread.php?t=231054
template <class T>
bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&)){
	if(s != ""){
		std::istringstream iss(s);
		return !(iss >> f >> t).fail();	
	}
};

// copied from the ofxDirList.cpp to here (so we can use it even when ofxDirList is not used)
static string tiStrToLower(string myStr){
    transform( myStr.begin(), myStr.end(), myStr.begin(), ::tolower );
    return myStr;
}


float mapX(ofPoint pNorm, ofRectangle rect, bool updatePosition=true);
float mapY(ofPoint pNorm, ofRectangle rect, bool updatePosition=true);
ofPoint mapPoint(ofPoint pNorm, ofRectangle rect, bool updatePosition=true);
float normalizeX(float x, ofRectangle rect, bool positionOnly=false);
float normalizeY(float y, ofRectangle rect, bool positionOnly=false);

bool tiDirectoryExists(string directoryPath, bool createIfMissing=false);
bool tiFileExists(string filename, bool isAbsolute=false);
bool tiCopyFile(string filename, string newFilename, bool isAbsolute=false);
int tiGetFileSize(string filename, bool isAbsolute=false);
bool tiRemoveFile(string filename, bool isAbsolute=false);
bool tiRenameFile(string filename, string newFilename, bool isAbsolute=false);

#endif
