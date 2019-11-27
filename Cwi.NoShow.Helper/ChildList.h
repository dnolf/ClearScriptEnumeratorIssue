// ChildList.h : Declaration of the CChildList

#pragma once
#include "resource.h"       // main symbols



#include "CwiNoShowHelper_i.h"

#include <vector>

using namespace ATL;


// CChildList

class ATL_NO_VTABLE CChildList :
	public CComObjectRootEx<CComMultiThreadModel>,
	//public CComCoClass<CChildList, &CLSID_ChildList>,
	public IDispatchImpl<IChildList, &IID_IChildList, &LIBID_CwiNoShowHelperLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CChildList()
	{
		m_pUnkMarshaler = nullptr;
	}

DECLARE_REGISTRY_RESOURCEID(107)


BEGIN_COM_MAP(CChildList)
	COM_INTERFACE_ENTRY(IChildList)
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

	STDMETHOD(get__NewEnum)(LPUNKNOWN *ppEnumerator);
	STDMETHOD(get_Count)(long * plCount);

	std::vector< CComPtr<IChild> > m_ChildList;

public:



};

//OBJECT_ENTRY_AUTO(__uuidof(ChildList), CChildList)
