#pragma once



class MainFrame;
class NetWork;
class ServerListener;
class SimulateClientMainFrame;






class MyApp : public wxApp
{
public:

	MyApp(){};

	virtual ~MyApp(){}


	virtual bool OnInit();


	bool ProcessIdle();

	virtual int OnExit();


	void  OnKeyUp(wxKeyEvent& event);


	SimulateClientMainFrame* m_pframe;



protected:


	NetWork* m_pNetWorker;


	ServerListener*  m_pNetWorkListener;

};

DECLARE_APP(MyApp)