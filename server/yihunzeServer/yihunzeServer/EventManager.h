#ifndef _DreamIsland_EventManager_hpp__
#define _DreamIsland_EventManager_hpp__

class CFunctionSlotBase
{
public:
	virtual ~CFunctionSlotBase(){}
	virtual bool operator()( void * pdata ){ return true;}
	virtual long getThisAddr() { return 0;}
	virtual long getFunAddr() { return 0;}
	virtual void emptyThisAddr(){}
};

template<typename T , typename T2>
class CFunctionSlot : public CFunctionSlotBase
{
	typedef void (T::*f)( T2* );
public:
	CFunctionSlot( void (T::*f)( T2* ) , T * obj )
		:m_funPtr( f ),m_this( obj )
	{

	}
	virtual ~CFunctionSlot(){}

	virtual bool operator() ( void* pdata )
	{
		if( m_this != NULL && m_funPtr != NULL ) 
		{
			(m_this->*m_funPtr)( reinterpret_cast<T2*>( pdata ) );
			return true;
		}
		else
			return false;
	}

	virtual long getThisAddr()
	{
		return ( *reinterpret_cast<long*>( &m_this ) );
	}
	virtual void emptyThisAddr()
	{
		m_this = NULL;
	}

	virtual long getFunAddr()
	{
		//��ȡ���Ա������ַ��&m_funPtr ȡ����Ա����ָ���ַ������תΪָ��long�͵�ָ�룬����*ȡ����ֵַ
		return ( *reinterpret_cast<long*>( &m_funPtr ) );
	}

private:
	f m_funPtr;
	T * m_this;
};




class CEventManager
{
public:
	~CEventManager()
	{
		for( MSGMAP::iterator it = m_msgMap.begin() ; it != m_msgMap.end() ; it++ )
		{
			std::vector<CFunctionSlotBase* > * p = it->second ;
			for( std::vector<CFunctionSlotBase* >::iterator it2 = p->begin() ; it2 != p->end() ; it2++ )
			{
				delete *it2;
			}
			p->clear();
			delete p;
		}
		m_msgMap.clear();
	}
	/*
	*ע��������ط��¼��������̵ĺ���
	*����һ����Ϣ����
	*���������������̵ĵ�ַ ���̺�������Ϊ void f( char* )
	*�����������̶���ĵ�ַ
	*/
	template<typename T , typename T2>
	bool registerMessageHandle( unsigned long msgType , void (T::*f)( T2* ) , T * obj )
	{
		std::vector<CFunctionSlotBase* > * vec = NULL;
		MSGMAP::iterator it = m_msgMap.find( msgType );
		if( it == m_msgMap.end() )
			vec = new  std::vector<CFunctionSlotBase* >;
		else
			vec = it->second;

		CFunctionSlotBase * pslot = new CFunctionSlot<T,T2>( f , obj );
		if( !pslot ) return false;

		vec->push_back( pslot );
		m_msgMap.insert( std::make_pair( msgType , vec ) );
		return true;
	}

	template<typename T>
	bool unregisterMessageHandle( unsigned long msgType , T* obj )
	{
		std::vector<CFunctionSlotBase* > * vec = NULL;
		MSGMAP::iterator it = m_msgMap.find( msgType );
		if( it == m_msgMap.end() )
			return true ;
		else
			vec = it->second;

		long thisAddr = *reinterpret_cast<long *>( &obj );

		for( std::vector<CFunctionSlotBase* >::iterator itor =  vec->begin() ; itor != vec->end() ; ++itor)
		{
			if( (*itor)->getThisAddr() == thisAddr )
			{
				//��ע�Ტ����ʵɾ����ֻ�ǽ�thisָ���ÿ�
				(*itor)->emptyThisAddr();
			}

		}
		return true;
	}
	template<typename T>
	void fireMessage( unsigned long type , T * pdata)
	{

		//�жϸ������¼��Ƿ���ϵͳ��ע��
		MSGMAP::iterator typeIt = m_msgMap.find( type );
		if( typeIt == m_msgMap.end() ) return ;

		//�������ݵ���Ӧ��ע�ắ����
		for( std::vector<CFunctionSlotBase* >::iterator itor =  typeIt->second->begin() ; itor != typeIt->second->end() ; itor++ )
		{
			//�жϸó�Ա����ָ���Ӧ�Ķ����Ƿ�Ϊ0����ֹ�������ⱻɾ��
			if( (*itor)->getThisAddr() != 0 )
				(**itor)( pdata );
		}
		return ;
	}
protected:
	//���ڱ���ע��ĺ�����ַ
	std::map< unsigned long , std::vector<CFunctionSlotBase* >* > m_msgMap;
	typedef std::map< unsigned long , std::vector<CFunctionSlotBase* >* > MSGMAP;
};

#endif // _DreamIsland_EventManager_hpp__