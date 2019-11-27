// Child.cpp : Implementation of CChild

#include "stdafx.h"
#include "Child.h"

STDMETHODIMP CChild::get_Id(long* plId)
{
	*plId = m_lId;
	return S_OK;
}
// CChild

