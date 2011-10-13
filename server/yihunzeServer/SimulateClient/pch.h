

#pragma  once



#include <Windows.h>
#include <WinUser.h>
#include <vector>
#include <string>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <list>
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include "wx/wxprec.h"
#include "wx/wx.h"

#include "mysql.h"
#include "xmain.h"






#define  SafeDelete(a) if(a!=NULL){delete a; a=NULL;}


#define  GAMESERVER   "gameserver"