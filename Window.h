#pragma once

#include "RiftWin.h"
#include "RiftException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

#include <optional>
#include <memory>

class Window
{
public:
    // Pencere ile ilgili hataları işlemek için özel istisna sınıfı
    class Exception : public RiftException {
    public:
        Exception(int line, const char* file, HRESULT hr) noexcept; // Yapıcı
        const char* what() const noexcept override; // Hata açıklamasını döner
        virtual const char* GetType() const noexcept; // Hata türünü döner
        static std::string TranslateErrorCode(HRESULT hr) noexcept; // HRESULT hata kodlarını dizeye çevirir
        HRESULT GetErrorCode() const noexcept; // HRESULT hata kodunu alır
        std::string GetErrorString() const noexcept; // Hata açıklamasını dize olarak alır
    private:
        HRESULT hr; // HRESULT hata kodunu saklar
    };
private:
    // Pencere sınıfının kaydını ve temizliğini yöneten singleton sınıfı
    class WindowClass
    {
    public:
        static constexpr const char* GetName() noexcept; // Pencere sınıfının adını alır
        static HINSTANCE GetInstance() noexcept; // Uygulamanın HINSTANCE'ını alır
    private:
        WindowClass() noexcept; // Yapıcı
        ~WindowClass(); // Yıkıcı
        WindowClass(const WindowClass&) = delete; // Kopyalama yapıcısını sil
        WindowClass& operator=(const WindowClass&) = delete; // Kopyalama atama operatörünü sil
        static constexpr const char* wndClassName = "Rift Engine"; // Pencere sınıfının adı
        static WindowClass wndClass; // Singleton örneği
        HINSTANCE hInst; // Uygulama örneği işaretçisi
    };
public:
    Window(int width, int height, const char* name); // Yapıcı
    ~Window(); // Yıkıcı
    Window(const Window&) = delete; // Kopyalama yapıcısını sil
    Window& operator=(const Window&) = delete; // Kopyalama atama operatörünü sil
    void SetTitle(const std::string& title);
    static std::optional<int> ProcessMessages();
    Graphics& Gfx();
private:
    static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept; // Kurulum mesaj işleyici
    static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept; // Mesaj yönlendirme işleyici
    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept; // Mesaj işleme işlevi
public:
    Keyboard kbd; // Klavye girişi işleyici
    Mouse mouse;
private:
    int width; // Pencere genişliği
    int height; // Pencere yüksekliği
    HWND hWnd; // Pencere işaretçisi
    std::unique_ptr<Graphics> pGfx;
};

// HRESULT hata kodları ile pencere istisnaları oluşturmak için makro
#define RIFTWND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)
#define RIFTWND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError())