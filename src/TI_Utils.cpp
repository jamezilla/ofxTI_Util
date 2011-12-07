/*
 *  TI_Utils.cpp
 *  openFrameworks
 *
 *  Created by Pat Long on 15/12/08.
 *  Copyright 2008 Tangible Interaction. All rights reserved.
 *
 */

#include "TI_Utils.h"

float tiAngle(float dx, float dy){
	float theta;

	// get a proper angle from one point to the next
	theta = atan2(-dy, dx);
	if(dy > 0)
		theta += 2.0 * PI;
	
	return theta;
}

float tiAngle(float x1, float y1, float x2, float y2){
	float dx = x2 - x1;
	float dy = y2 - y1;
	return tiAngle(dx, dy);
}

float tiAngleXComponent(float angle, float magnitude, bool radians){
	if(magnitude == 0.0){
		return 0.0;
	}
	else if(!radians){
		if(angle == 90.0 || angle == 270.0)
			return 0.0;
	}
	if(!radians){
		angle = tiAngleToRadians(angle);
	}
	return magnitude * cos(angle);
}

float tiAngleYComponent(float angle, float magnitude, bool radians){
	if(magnitude == 0.0){
		return 0.0;
	}
	else if(!radians){
		if(angle == 0.0 || angle == 180.0 || angle == 360.0)
			return 0.0;
	}
	if(!radians){
		angle = tiAngleToRadians(angle);
	}
	return magnitude * sin(angle);
}

float tiAngleToRadians(float angle){
	return angle * PI / -180.0;
}

float tiRadiansToAngle(float radians){
	return radians * 180.0 / PI;
}

float tiNormalizeAngle(float angle){
	float normalized = std::fmod(angle, (float)360.0);
	if(normalized < 0)
		normalized += 360.0;
	return normalized;
}

float tiDistance(float dx, float dy){
	return sqrt(double(dx*dx + dy*dy));
}

float tiDistance(float x1, float y1, float x2, float y2){
	float dx = x2 - x1;
	float dy = y2 - y1;
	return tiDistance(dx, dy);
}

float tiAbs(float num){
	return (num < 0.0)?num*-1.0:num;
}

bool timeInRange(int cHour, int cMin, int startHour, int startMin, int stopHour, int stopMin){
	int startMins = startHour * 60 + startMin;
	int stopMins = stopHour * 60 + stopMin;
	int cMins = cHour * 60 + cMin;
	
	if(startMins > stopMins){
		if(cMins < startMins)
			cMins += 24*60;
		stopMins += 24*60;
	}
	
	return (cMins >= startMins && cMins <= stopMins);
}

bool timeInRange(string cTime, string startTime, string endTime){
	int cHour, cMin, startHour, startMin, endHour, endMin;
	cHour = cMin = startHour = startMin = endHour = endMin = -1;
	vector<string> splits;
	splits = split(cTime, ':');
	if(splits.size() == 2){
		if(!from_string(cHour, splits[0], std::dec))
			cHour = -1;
		if(!from_string(cMin, splits[1], std::dec))
			cMin = -1;
	}
	
	splits = split(startTime, ':');
	if(splits.size() == 2){
		if(!from_string(startHour, splits[0], std::dec))
			startHour = -1;
		if(!from_string(startMin, splits[1], std::dec))
			startMin = -1;
	}
	
	splits = split(endTime, ':');
	if(splits.size() == 2){
		if(!from_string(endHour, splits[0], std::dec))
			endHour = -1;
		if(!from_string(endMin, splits[1], std::dec))
			endMin = -1;
	}
	
	if(cHour != -1 && cMin != -1 && startHour != -1 && startMin != -1 && endHour != -1 && endMin != -1)
		return (timeInRange(cHour, cMin, startHour, startMin, endHour, endMin));
	return false;
}

vector<string> &split(const string &s, char delim, vector<string> &elems){
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)){
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim){
    vector<string> elems;
    return split(s, delim, elems);
}

string stringReplace(string theString, string searchString, string replaceString){
	string::size_type pos = 0;
	while ( (pos = theString.find(searchString, pos)) != string::npos ) {
		theString.replace( pos, searchString.size(), replaceString );
		pos++;
	}
	return theString;
}


float mapX(ofPoint pNorm, ofRectangle rect, bool updatePosition){
	float res = (pNorm.x*rect.width);
	if(updatePosition)
		res += rect.x;
	return res;
}

float mapY(ofPoint pNorm, ofRectangle rect, bool updatePosition){
	float res = (pNorm.y*rect.height);
	if(updatePosition)
		res += rect.y;
	return res;
}

ofPoint mapPoint(ofPoint pNorm, ofRectangle rect, bool updatePosition){
	ofPoint res;
	res.x = mapX(pNorm, rect, updatePosition);
	res.y = mapY(pNorm, rect, updatePosition);
	return res;
}

float normalizeX(float x, ofRectangle rect, bool positionOnly){
	float res = x-rect.x;
	if(!positionOnly)
		res /= rect.width;
	return res;
}

float normalizeY(float y, ofRectangle rect, bool positionOnly){
	float res = y-rect.y;
	if(!positionOnly)
		res /= rect.height;
	return res;
}

bool tiDirectoryExists(string directoryPath, bool createIfMissing){
	bool result = false;
	struct stat st;
	if(stat(directoryPath.c_str(), &st) == 0)
		result = true;
	else{
		if(createIfMissing){
			stringstream commandBuilder;
			commandBuilder << "mkdir -p " << directoryPath;
			system(commandBuilder.str().c_str());
			commandBuilder.str("");
			result = tiDirectoryExists(directoryPath, false);
		}
	}
	
	return result;
}

bool tiFileExists(string filename, bool isAbsolute){
	return (tiGetFileSize(filename, isAbsolute) >= 0);
}

bool tiCopyFile(string filename, string newFilename, bool isAbsolute){
	if(filename != ""){
		if(tiFileExists(filename, isAbsolute)){
			if(!isAbsolute){
				filename = ofToDataPath(filename, true);
				newFilename = ofToDataPath(newFilename, true);
			}
			stringstream commandBuilder;
			commandBuilder << "cp " << filename << " " << newFilename;
			system(commandBuilder.str().c_str());
			commandBuilder.str("");
			return true;
		}
	}
	return false;
}

// return size in bytes of specified filename (please pass as absolute path)
int tiGetFileSize(string filename, bool isAbsolute){
	if(filename != ""){
		if(!isAbsolute)
			filename = ofToDataPath(filename, true);
		
		// snippet from: http://en.allexperts.com/q/C-1040/size-file-C.htm
		FILE * stream = fopen( filename.c_str(), "r" );
		if(stream != NULL){
			fseek( stream, 0L, SEEK_END );
			long endPos = ftell( stream );
			fclose( stream );
			return endPos;
		}
	}
	return -1;
}

bool tiRemoveFile(string filename, bool isAbsolute){
	if(filename != ""){
		if(!isAbsolute)
			filename = ofToDataPath(filename, true);
		stringstream commandBuilder;
		commandBuilder << "rm " << filename;
		system(commandBuilder.str().c_str());
		commandBuilder.str("");
		return true;
	}
	return false;
}

bool tiRenameFile(string filename, string newFilename, bool isAbsolute){
	if(filename != ""){
		if(tiFileExists(filename, isAbsolute)){
			if(!isAbsolute){
				filename = ofToDataPath(filename, true);
				newFilename = ofToDataPath(newFilename, true);
			}
			stringstream commandBuilder;
			commandBuilder << "mv " << filename << " " << newFilename;
			system(commandBuilder.str().c_str());
			commandBuilder.str("");
			return true;
		}
	}
	return false;
}
