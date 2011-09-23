
#pragma  once


#include <Windows.h>
#include <WinUser.h>
#include <vector>
#include <string>

//
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "mysql.h"



#include "xmain.h"


#define  SafeDelete(a) if(a!=NULL){delete a; a=NULL;}