//
//  yhzIphoneClientViewController.h
//  yhzIphoneClient
//
//  Created by thcz on 11-9-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once 

#import <UIKit/UIKit.h>

#include "pch.h"
#include "NetWorkClient.h"
#import "yhzIphoneClientViewController.h" 


class MessageReceive;


@interface yhzIphoneClientViewController : UIViewController 
{
    IBOutlet UIButton*    m_pSendButton;///发送按钮
    IBOutlet UILabel*     m_pServerIPLabel; ///连接服务器ip
    
    IBOutlet UITextField*   m_SendTextField;//需要发送的文内容
    IBOutlet UITextView*    m_ReceiveTextView;///接收消息内容
    
    
    NetWorkClient*        m_pNetWork;  ///网络连接
    
    MessageReceive*        m_pMessageReceive;
    
    
    
}


@property (nonatomic, retain) IBOutlet UITextView *m_ReceiveTextView;

@property (nonatomic, retain) IBOutlet UILabel *m_pServerIPLabel;


-(IBAction) send:(id) sender;

-(void)  initNetwork;

-(void)  destroyNetwork;

-(void)  reviceMessage;

-(void)  printMessage:(NSString*) pMessage;///输出一个消息


///设置连接的远程ip
-(void)  setRemoteServerIP:(NSString*) pIP;


@end
