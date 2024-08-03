#pragma once

#include "RiftWin.h"
#include <d3d11.h>

// Graphics sınıfı, Direct3D 11 ile grafik işlemlerini yönetir.
class Graphics {
public:
    // Constructor, pencere tanımlayıcı (hWnd) alır ve Direct3D cihazı oluşturur
    Graphics(HWND hWnd);
    // Kopyalama constructor'ı devre dışı, nesnenin kopyalanmasını engeller
    Graphics(const Graphics&) = delete;
    // Atama operator'ü devre dışı, nesnenin başka bir nesneye atanmasını engeller
    Graphics& operator=(const Graphics&) = delete;
    // Destructor, Direct3D kaynaklarını serbest bırakır
    ~Graphics();
    // Frame'in sonlandırılması, swap chain'in içeriğini ekrana yansıtır
    void EndFrame();

    // Arka planı temizler ve belirli bir renk ile doldurur
    inline void ClearBuffer(float red, float green, float blue) noexcept {
        const float color[] = { red, green, blue };
        pContext->ClearRenderTargetView(pTarget, color);
    }

private:
    // Direct3D cihazı
    ID3D11Device* pDevice = nullptr;
    // Swap chain (ekranın önbelleği)
    IDXGISwapChain* pSwap = nullptr;
    // Direct3D cihaz bağlamı
    ID3D11DeviceContext* pContext = nullptr;
    // Render target view (çizim yapılacak hedef)
    ID3D11RenderTargetView* pTarget = nullptr;
};