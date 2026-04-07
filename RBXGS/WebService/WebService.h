// WebService.h : Defines the ATL Server request handler class
//
#pragma once

namespace WebServiceService
{
// all struct, enum, and typedefs for your webservice should go inside the namespace

// IWebServiceService - web service interface declaration
//
[
	uuid("73A2AE7C-30FD-48E1-86DE-795691F553DE"), 
	object
]
__interface IWebServiceService
{
	// HelloWorld is a sample ATL Server web service method.  It shows how to
	// declare a web service method and its in-parameters and out-parameters
	[id(1)] HRESULT HelloWorld([in] BSTR bstrInput, [out, retval] BSTR *bstrOutput);
	// TODO: Add additional web service methods here
};


// WebServiceService - web service implementation
//
[
	request_handler(name="Default", sdl="GenWebServiceWSDL"),
	soap_handler(
		name="WebServiceService", 
		namespace="urn:WebServiceService",
		protocol="soap"
	)
]
class CWebServiceService :
	public IWebServiceService
{
public:
	// This is a sample web service method that shows how to use the 
	// soap_method attribute to expose a method as a web method
	[ soap_method ]
	HRESULT HelloWorld(/*[in]*/ BSTR bstrInput, /*[out, retval]*/ BSTR *bstrOutput)
	{
		CComBSTR bstrOut(L"Hello ");
		bstrOut += bstrInput;
		bstrOut += L"!";
		*bstrOutput = bstrOut.Detach();
		
		return S_OK;
	}
	// TODO: Add additional web service methods here
}; // class CWebServiceService

} // namespace WebServiceService
