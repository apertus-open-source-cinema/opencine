#ifndef OCCORE_H
#define OCCORE_H

//#include "FSHelper.h"

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

void EXPORT_API TestFunc();

#endif //OCCORE_H
