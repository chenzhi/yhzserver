///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_receiveText = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer3->Add( m_receiveText, 1, wxBOTTOM|wxEXPAND, 10 );
	
	m_sendText = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer3->Add( m_sendText, 1, wxBOTTOM|wxEXPAND|wxTOP, 10 );
	
	bSizer1->Add( bSizer3, 5, wxEXPAND, 0 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_serverList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer4->Add( m_serverList, 1, wxALL|wxEXPAND, 5 );
	
	m_messagelist = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer4->Add( m_messagelist, 1, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( bSizer4, 2, wxEXPAND, 5 );
	
	m_MessageText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_MessageText, 2, wxALL|wxEXPAND, 5 );
	
	m_send = new wxButton( this, wxID_ANY, wxT("·¢ËÍ"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_send, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxTOP, 5 );
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainFrame::onMainFrameKeyDown ) );
	m_serverList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MainFrame::onSelectServer ), NULL, this );
	m_messagelist->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MainFrame::onSelectMessage ), NULL, this );
	m_MessageText->Connect( wxEVT_KEY_UP, wxKeyEventHandler( MainFrame::OnMessageTextKeyup ), NULL, this );
	m_send->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnSend ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainFrame::onMainFrameKeyDown ) );
	m_serverList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MainFrame::onSelectServer ), NULL, this );
	m_messagelist->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MainFrame::onSelectMessage ), NULL, this );
	m_MessageText->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( MainFrame::OnMessageTextKeyup ), NULL, this );
	m_send->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnSend ), NULL, this );
	
}
