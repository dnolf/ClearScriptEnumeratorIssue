// NoShowHelper.cpp : Implementation of CNoShowHelper

#include "stdafx.h"
#include "NoShowHelper.h"
#include "ChildList.h"
#include "Child.h"

STDMETHODIMP CNoShowHelper::get_ChildList(IChildList** ppChildList)
{

	*ppChildList = m_spChildList.p;
	if (m_spChildList.p != nullptr)
	{
		(*ppChildList)->AddRef();
	}

	return S_OK;

}

void CNoShowHelper::SetupAllObjects()
{
	CComObject<CChildList>* pChildList = nullptr;
	CComObject<CChildList>::CreateInstance(&pChildList);
	m_spChildList = pChildList;

	for (int i = 1; i <= 2; i++)
	{
		CComObject<CChild>* pChild = nullptr;
		CComObject<CChild>::CreateInstance(&pChild);
		pChild->m_lId = i;
		CComPtr<IChild> spChild = pChild;
		pChildList->m_ChildList.push_back(spChild);
	}


}



// CNoShowHelper

