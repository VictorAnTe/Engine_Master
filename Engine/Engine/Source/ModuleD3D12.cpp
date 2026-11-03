#include "Globals.h"
#include "ModuleD3D12.h"

ModuleD3D12::ModuleD3D12() = default;

ModuleD3D12::~ModuleD3D12() = default;

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
    // Ensure factory is created
#if defined(_DEBUG)
    HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory));
#else
    HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&factory));
#endif
    if (FAILED(hr))
    {
        return false;
    }

    ComPtr<IDXGIAdapter4> adapter;
    hr = factory->EnumAdapterByGpuPreference(
        0,
        DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
        IID_PPV_ARGS(&adapter)
    );
    if (FAILED(hr))
    {
        return false;
    }

    // Create the D3D12 device
    hr = D3D12CreateDevice(
        adapter.Get(),
        D3D_FEATURE_LEVEL_12_0,
        IID_PPV_ARGS(&device)
    );
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}