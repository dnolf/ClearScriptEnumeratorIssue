// ChildList.cpp : Implementation of CChildList

#include "stdafx.h"
#include "ChildList.h"
#include <vector>

STDMETHODIMP CChildList::get__NewEnum(LPUNKNOWN *ppEnumerator)
{
	typedef CComObject<CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > > enumvar;

	std::vector<CComVariant> Vect;

	CComQIPtr<IDispatch, &IID_IDispatch> spDisp;

	auto iter = m_ChildList.begin();
	auto iterEnd = m_ChildList.end();

	for (; iter != iterEnd; iter++)
	{

		spDisp = ((*iter).p);

		Vect.push_back(CComVariant(spDisp));

		spDisp.Release();

	}

	enumvar* pEnumVar = new enumvar;

	if (Vect.size() > 0)
	{
		pEnumVar->Init(&(*Vect.begin()), &(*Vect.begin()) + Vect.size(), NULL, AtlFlagCopy);
	}
	else
	{
		pEnumVar->Init(NULL, NULL, NULL, AtlFlagCopy);
	}

	pEnumVar->QueryInterface(IID_IEnumVARIANT, (void**)ppEnumerator);

	Vect.clear();

	return S_OK;

}

STDMETHODIMP CChildList::get_Count(long * plCount)
{
	*plCount = m_ChildList.size();
	return S_OK;
}
// CChildList

