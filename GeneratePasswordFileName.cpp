#include<iostream>
#include<ctime>
#include<cstdlib>
#include"GeneratePasswordFileName.h"

GeneratePasswordFileName::GeneratePasswordFileName()
{
	generatedFileName();
}
void GeneratePasswordFileName::generatedFileName()
{
	filename.assign(dateString());
	for (auto index = 0; index!=8; ++index)
	{
		if (index==0) filename.append("_");
		else
		{
			auto randomInteger = rand() % 10;	
			filename.append(std::to_string(randomInteger));
		}
	}
}

string GeneratePasswordFileName::passwordFileNameString() const { return filename; }
int GeneratePasswordFileName::retrieveYear() const { return year; }
int GeneratePasswordFileName::retrieveMonth() const { return month; }
int GeneratePasswordFileName::retrieveDayOfMonth() const { return dayOfMonth; }
