// WebService.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif

#include "WebService.h"
#include "boost/thread/once.hpp"
#include "util/standardout.h"

[ module(name="MyWebService", type=dll) ]
class CDllMainOverride
{
public:
};

[ emitidl(restricted) ];

// TODO: StandardOutLog

boost::once_flag flagInitRoblox = BOOST_ONCE_INIT;
static bool initRobloxFailed;

void initRoblox()
{
	RBX::StandardOut::singleton()->print(RBX::MESSAGE_INFO, "Initializing Roblox Web Service");
	// TODO
}

class CRbxIsapiExtension : public CIsapiExtension<>
{
private:
	virtual const char* GetExtensionDesc()
	{
		return "ROBLOX Web Service";
	}
};

typedef CRbxIsapiExtension ExtensionType;

// The ATL Server ISAPI extension
ExtensionType theExtension;


// Delegate ISAPI exports to theExtension
//
extern "C" DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB)
{
	boost::call_once(&initRoblox, flagInitRoblox);

	if (initRobloxFailed)
		return HSE_STATUS_ERROR;

	return theExtension.HttpExtensionProc(lpECB);
}

extern "C" BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	return theExtension.GetExtensionVersion(pVer);
}

extern "C" BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	return theExtension.TerminateExtension(dwFlags);
}
