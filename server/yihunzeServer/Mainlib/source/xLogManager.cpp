
//多线程非安全



#include "pch.h"
#include <iomanip>
#include <time.h>

#include "xLogManager.h"


template<> xLogMessager* Singleton<xLogMessager>::ms_Singleton = NULL;

xLogMessager::~xLogMessager()
{
	mfpLog.close();

}
xLogMessager::xLogMessager(const std::string& filename)
:m_WriteLevel(Log_NormalLevel)
{
	assert(!filename.empty());
	mfpLog.open(filename.c_str());
}

//-----------------------------------------------------------------------
void xLogMessager::logMessage( const std::string& message,LogLevel level )
{


	if(level<m_WriteLevel)
		return;

    /*/
	tm pTime;
	time_t ctTime;

	//__time64_t long_time;

	time(&ctTime);

	errno_t  er = localtime_s( &pTime,&ctTime );
	if(er!=0)
		return;
	mfpLog<< std::setw(2) << std::setfill('0') << 1900+pTime.tm_year<< "/" 
		<< std::setw(2) << std::setfill('0') << pTime.tm_mon+1<< "/" 
		<< std::setw(2) << std::setfill('0') << pTime.tm_mday<< "/" 
		<<std::setw(2) << std::setfill('0') << pTime.tm_hour<< ":" 
		<< std::setw(2) << std::setfill('0') << pTime.tm_min<< ":" 
		<< std::setw(2) << std::setfill('0') << pTime.tm_sec << ":" 
		<< message << std::endl;

    //*/
	// Flush stcmdream to ensure it is written (incase of a crash, we need log to be up to date)
    
    struct tm *pTime;
    time_t ctTime; time(&ctTime);
    pTime = localtime( &ctTime );
    mfpLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
    << ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
    << ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
    << ": ";


    mfpLog << message << std::endl;

	mfpLog.flush();


}





