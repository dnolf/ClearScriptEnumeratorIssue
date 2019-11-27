// dllmain.h : Declaration of module class.

class CCwiNoShowHelperModule : public ATL::CAtlDllModuleT< CCwiNoShowHelperModule >
{
public :
	DECLARE_LIBID(LIBID_CwiNoShowHelperLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CWINOSHOWHELPER, "{7ae73476-5e57-4512-b583-f9dd99dd05e4}")
};

extern class CCwiNoShowHelperModule _AtlModule;
