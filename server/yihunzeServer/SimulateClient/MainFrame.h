///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxRichTextCtrl* m_receiveText;
		wxRichTextCtrl* m_sendText;
		wxListBox* m_serverList;
		wxListBox* m_messagelist;
		wxTextCtrl* m_MessageText;
		wxButton* m_send;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onMainFrameKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void onSelectServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSelectMessage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMessageTextKeyup( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnSend( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1154,791 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

#endif //__MAINFRAME_H__
