#include "Graphics.h"

// Direct3D 11 kütüphanesini link eder
#pragma comment(lib, "d3d11.lib")

Graphics::Graphics(HWND hWnd)
{
    // Swap chain tanımı
    DXGI_SWAP_CHAIN_DESC sd = {};

    // Arka tamponun genişliği ve yüksekliği (0, pencere boyutuna göre ayarlanır)
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;

    // Tampon formatı (B8G8R8A8_UNORM, 8-bit mavi, yeşil, kırmızı ve alfa kanalları)
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

    // Yenileme hızı (0, otomatik seçim)
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;

    // Ekran ölçekleme ve tarama sırası (varsayılan ayar)
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    // Multi-sampling ayarları (1 örnek, kalite 0)
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    // Tampon kullanım amacı (Render target output, yani çizim yapılacak tampon)
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    // Tampon sayısı (1 arka tampon)
    sd.BufferCount = 1;

    // Çizim yapacağımız pencere
    sd.OutputWindow = hWnd;

    // Pencere modu (TRUE, pencere modunda çalışacağız)
    sd.Windowed = TRUE;

    // Swap efekti (DXGI_SWAP_EFFECT_DISCARD, tampon değiştirildiğinde eski veriyi at)
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    // Ekstra bayraklar (0, ekstra bir bayrak kullanılmıyor)
    sd.Flags = 0;

    // Direct3D cihazı, bağlamı ve swap chain oluşturma
    D3D11CreateDeviceAndSwapChain(
        nullptr, // Display adapter (null, otomatik seçim)
        D3D_DRIVER_TYPE_HARDWARE, // Donanım kullanımı
        nullptr, // Yazılım rasterizer (null, kullanmıyoruz)
        0, // Ekstra seçenekler
        nullptr, // Özellik seviyeleri (null, varsayılan)
        0, // Özellik seviyesi sayısı
        D3D11_SDK_VERSION, // SDK versiyonu
        &sd, // Swap chain tanımı
        &pSwap, // Swap chain (çıktı)
        &pDevice, // Direct3D cihazı (çıktı)
        nullptr, // Desteklenen özellik seviyesi (kullanılmıyor)
        &pContext // Cihaz bağlamı (çıktı)
    );

    // Swap chain içindeki arka tamponu al ve render target view oluştur
    ID3D11Resource* pBackBuffer = nullptr;
    pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
    pDevice->CreateRenderTargetView(
        pBackBuffer,
        nullptr,
        &pTarget
    );

    // Arka tamponu serbest bırak
    pBackBuffer->Release();
}

void Graphics::EndFrame()
{
    // Swap chain'i ekrana yansıtır
    pSwap->Present(1u, 0u);
}

Graphics::~Graphics()
{
    // Direct3D kaynaklarını serbest bırak
    if (pDevice != nullptr) {
        pDevice->Release();
    }

    if (pSwap != nullptr) {
        pSwap->Release();
    }

    if (pTarget != nullptr) {
        pTarget->Release();
    }
}

