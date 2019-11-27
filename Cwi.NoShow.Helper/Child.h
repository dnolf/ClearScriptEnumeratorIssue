// Child.h : Declaration of the CChild

#pragma once
#include "resource.h"       // main symbols



#include "CwiNoShowHelper_i.h"



using namespace ATL;


// CChild

class ATL_NO_VTABLE CChild :
	public CComObjectRootEx<CComMultiThreadModel>,
	//public CComCoClass<CChild, &CLSID_Child>,
	public IDispatchImpl<IChild, &IID_IChild, &LIBID_CwiNoShowHelperLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CChild()
	{
		m_pUnkMarshaler = nullptr;
	}

DECLARE_REGISTRY_RESOURCEID(108)


BEGIN_COM_MAP(CChild)
	COM_INTERFACE_ENTRY(IChild)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;
	long m_lId = 0L;

public:

	STDMETHOD(get_Id)(long* plId);


};

//OBJECT_ENTRY_AUTO(__uuidof(Child), CChild)
