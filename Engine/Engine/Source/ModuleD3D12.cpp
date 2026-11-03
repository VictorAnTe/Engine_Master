#include "Globals.h"
#include "ModuleD3D12.h"

bool ModuleD3D12::Init()
{
#if defined(_DEBUG)
	if(!AddDebugLayer())
	{
		// LOG_ERROR("Failed to add D3D12 debug layer.");
		return false;
	}
#endif
	if (!CreateDevice())
	{
		// LOG_ERROR("Failed to create D3D12 device.");
		return false;
	}
	return true;
}

bool ModuleD3D12::AddDebugLayer()
{
	ComPtr<ID3D12Debug> debugInterface;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface))))
	{
		debugInterface->EnableDebugLayer();
		return true;
	}
	else
	{
		// LOG_ERROR("Failed to get D3D12 debug interface.");
		return false;
	}
}

bool ModuleD3D12::CreateDevice()
{
	// Create the D3D12 device.
	HRESULT hr = D3D12CreateDevice(
		nullptr, // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&device)
	);
	if (FAILED(hr))
	{
		// LOG_ERROR("Failed to create D3D12 device.");
		return false;
	}
	return true;
}
