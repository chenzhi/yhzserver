#pragma once 


#ifdef  XMAIN_EXPORTS
#define XClass _declspec(dllexport)
#else
#define XClass _declspec(dllimport)
#endif



#pragma warning(disable: 4996)
#pragma warning(disable: 4661)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)



#include "Singleton.h"
#include "xLogManager.h"
#include "EventManager.h"
#include "netWork.h"
#include "databaseInstance.h"
#include "Config.h"

