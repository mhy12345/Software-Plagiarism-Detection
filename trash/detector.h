#ifndef __DETECTOR_H
#define __DETECTOR_H
#include "project.h"

class PDetector
{
	private:
		PProject *p1,*p2;
	public:
		void load_file1(const char* filename);
		void load_file2(const char* filename);
};

#endif

