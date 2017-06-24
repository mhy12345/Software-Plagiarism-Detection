#ifndef DETECTORS_H
#define DETECTORS_H

#include "file.h"
#include "project.h"

class Detector
{
	public:
		Detector();
		virtual void init(const char* path1,const char* path2) = 0;
		virtual double compare() = 0;
		virtual ~Detector() = 0;
};

class FileDetector:public Detector
{
	private:
		PFile *pf1,*pf2;
	public:
		FileDetector();
		~FileDetector();
		void init(const char* path1,const char* path2);
		double compare();

};
class ProjectDetector:public Detector
{
	private:
		PProject *pp1,*pp2;
	public:
		ProjectDetector();
		~ProjectDetector();
		void init(const char* path1,const char* path2);
		double compare();
};

#endif
