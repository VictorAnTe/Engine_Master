
#include "Globals.h"
#include "Module.h"

#include <windows.h>
#include <wrl.h>
#include <d3d12.h>

using Microsoft::WRL::ComPtr;

class ModuleD3D12 : public Module
{
public:
	ModuleD3D12();
	~ModuleD3D12();
	bool Init();

private:
	bool AddDebugLayer();
	bool CreateDevice();

private:
	ComPtr<ID3D12Device> device;
};