// This class implements VITAL protocol for online communication
#ifndef HOSTCONTROLIMPL_H
#define HOSTCONTROLIMPL_H

//#include "HostControl_Server.h"
#include "HostOperationEventImpl.h"
#include "HostInterface.h"
#include "AccessManager.h"
#include "patch.h"


#include "host_errors.h"

// Error
#define ERR_HOST_LOADING_COM_LIB   0xC1000001
#define ERR_HOST_OBJECT_NOT_LOADED 0xC1000002
#define ERR_HOST_COM_EXCEPTION     0xC1000003

typedef int (* HOST_CONNECT)(UINT_KEY Key);
typedef int (* SEND_DATA)(UINT_KEY Key,
                                                  int msg_type,
                                                  const byte *out_data, UNINT out_len,
                                                  UNINT timeout = SCS_TO_INFINITE);
typedef void (* HOST_DISCONNECT)(UINT_KEY Key);
typedef int (* GETONLINEDATATAGS)(UINT_KEY Key, ONLINE_DATA_TAGS tagType);
typedef ONLINE_RESULT (* ANALYZEAUTHRESPONSE)(UINT_KEY Key,
                                                                                          const byte* const AuthRespCode);

class HostControlImpl :
	public EventAdder,
	public OperationEvent,
	public amAdder,
	public ServiceControl
{
public:
	HostControlImpl(void);
	virtual ~HostControlImpl(void);

	virtual int host_connect();
	virtual int send_data(int msg_type,
						  const byte *out_data, UNINT out_len,
						  UNINT timeout = SCS_TO_INFINITE);
	int getOnlineDataTags (ONLINE_DATA_TAGS tagType);
	
	// Disconnects from the host
	virtual void host_disconnect();

	// Returns an array of tags for data required for online message.
	//virtual int getOnlineDataTags (ONLINE_DATA_TAGS tagType);

	// Analyzes a Response Code and sets approved == 1 if the decision is Approved,
	// and 0 otherwise.
	virtual ONLINE_RESULT AnalyzeAuthResponse (const byte* const AuthRespCode);

private: //Private member functions
	long checkInitialization (bool checkEvent = true);
	int mapError(long res);
	void DestroyHostObject();
	int connect2host (const char *aid);
	int CreateHostObject ();
	SAFEARRAY* CreateSafeArray(const byte *fillArr, UNINT size);
	byte* ParseSafeArr (SAFEARRAY *psaArray, unsigned long size);

private:
	_VSDCAuthPtr ptrHost; // Ponter to a host interface

};

#endif

