//
//  Header.h
//  yhzIphoneClient
//
//  Created by thcz on 11-9-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once


#define Platform   P_IPHONE

#define XClass   


#include <assert.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <vector>

#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "PacketLogger.h"
#include "RakNetTypes.h"


typedef unsigned int   DWORD;

typedef char     byte;
typedef char     BYTE;

#define _snprintf  sprintf

#define SafeDelete(a)  if(a!=NULL){delete a; a=NULL;}