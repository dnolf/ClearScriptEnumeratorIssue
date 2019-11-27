// NoShowHelper.h : Declaration of the CNoShowHelper

#pragma once
#include "resource.h"       // main symbols



#include "CwiNoShowHelper_i.h"
#include "ATLComTime.h"



using namespace ATL;


// CNoShowHelper

class ATL_NO_VTABLE CNoShowHelper :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CNoShowHelper, &CLSID_CWINoShowHelper>,
	public IDispatchImpl<INoShowHelper, &IID_INoShowHelper, &LIBID_CwiNoShowHelperLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CNoShowHelper()
	{
		m_pUnkMarshaler = nullptr;
	}

DECLARE_REGISTRY_RESOURCEID(106)

DECLARE_NOT_AGGREGATABLE(CNoShowHelper)

BEGIN_COM_MAP(CNoShowHelper)
	COM_INTERFACE_ENTRY(INoShowHelper)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		SetupAllObjects();
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

	CComPtr<IChildList> m_spChildList;


public:

	STDMETHOD(get_ChildList)(IChildList* *ppChildList);

	void SetupAllObjects();

};

OBJECT_ENTRY_AUTO(__uuidof(CWINoShowHelper), CNoShowHelper)
