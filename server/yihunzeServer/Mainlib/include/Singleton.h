/******************************************
单件对像，不支持多线程
*******************************************/
#ifndef  Singleton_h_h_h_h_h
#define Singleton_h_h_h_h_h







template <typename T> class Singleton
{
protected:

	static T* ms_Singleton;

public:
	Singleton( void )
	{
		assert( !ms_Singleton );

		ms_Singleton = static_cast< T* >( this );

	}

	~Singleton( void )
	{  assert( ms_Singleton );  ms_Singleton = 0;  }

	static T& getSingleton( void )
	{	assert( ms_Singleton );  return ( *ms_Singleton ); }


	static T* getSingletonPtr( void )
	{ return ms_Singleton; }

};





#endif