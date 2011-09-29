//
//  yhzIphoneClientViewController.m
//  yhzIphoneClient
//
//  Created by thcz on 11-9-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "yhzIphoneClientViewController.h"
#include "MessageReceive.h"


@implementation yhzIphoneClientViewController

@synthesize m_ReceiveTextView,m_pServerIPLabel;


- (void)dealloc
{
    [self destroyNetwork];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

//*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self initNetwork];
    
    ///定时器函数，每帧接收消息
    [NSTimer scheduledTimerWithTimeInterval:1.0/30.0f  target:self  selector:@selector(reviceMessage) 
                                   userInfo:nil 
                                    repeats:YES];

}
//*/

- (void)viewDidUnload
{
    [super viewDidUnload];
    
    
    
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}



-(void)  initNetwork
{
    m_pNetWork = new NetWorkClient();
    m_pNetWork->connect("172.16.100.245", 1234, "8889");
    
    
    
    m_pMessageReceive=new MessageReceive(self);
    
    m_pNetWork->setListener(m_pMessageReceive);
    
    return ;
    
}

-(void)  destroyNetwork
{
    
    SafeDelete(m_pMessageReceive);
    
    SafeDelete(m_pNetWork);
    
    
}

-(void) send:(id) sender
{

    NSString* pSendMessage= m_SendTextField.text;
    NSInteger len=[pSendMessage length];
    if(len<=0)
        return ;
    const char* message= [pSendMessage cStringUsingEncoding:NSASCIIStringEncoding]; 
    
    UserLogin userlogine;
    sscanf(message, "%s = %s",userlogine.m_account,userlogine.m_password);
    m_pNetWork->send(GM_ACCOUNT_REQUEST,userlogine);
    //m_SendTextField.text=@"";
    
    return ;

    
}


-(void) reviceMessage
{
    if(m_pNetWork==NULL)
        return ;
    m_pNetWork->update();
}

-(void)  printMessage:(NSString*) pMessage;
{
    
    m_ReceiveTextView.text=pMessage;
    
    //m_ReceiveTextView.text=[m_ReceiveTextView.text componentsJoinedByString:pMessage];
    
    return ;
}



-(void)  setRemoteServerIP:(NSString*) pIP
{
    m_pServerIPLabel.text=pIP;
    
}


@end
