#pragma once

#include <queue>
#include <bitset>
#include <optional>

// Keyboard sınıfı klavye olaylarını yönetir
class Keyboard {
private:
	// Window sınıfı ile arkadaş yapıyoruz böylece Window sınıfı Keyboard sınıfının özel üyelerine erişebilir
	friend class Window;
public:
	// Event sınıfı klavye olaylarını temsil eder
	class Event {
	public:
		// Klavye olaylarının türlerini tanımlar
		enum class Type {
			Pressed,		// Tuşa basıldı
			Released,		// Tuş serbest bırakıldı
			Invalid			// Geçersiz olay
		};
	private:
		Type type;			// Olayın türü
		unsigned char code;	// Tuşun kodu
	public:
		// Varsayılan kurucu, olayı geçersiz ve tuş kodunu 0 olarak ayarlar
		Event() {
			type = Type::Invalid;
			code = 0u;
		}
		// Belirtilen tür ve tuş kodu ile olayı oluşturur
		Event(Type type, unsigned char code) noexcept {
			this->type = type;
			this->code = code;
		}
		
		// Olayın bir tuşa basma olup olmadığını kontrol eder
		bool IsPressed() const noexcept {
			return type == Type::Pressed;
		}

		// Olayın bir tuş bırakma olup olmadığını kontrol eder
		bool IsRelease() const noexcept {
			return type == Type::Released;
		}

		// Tuş kodunu döndürür
		unsigned char GetCode() const noexcept {
			return code;
		}
	};
public:
	// Varsayılan kurucu
	Keyboard() = default;
	// Kopyalama kurucusu silindi
	Keyboard(const Keyboard&) = delete;
	// Kopya atama operatörü silindi
	Keyboard& operator=(const Keyboard&) = delete;

	// Tuş olayı fonksiyonları
	bool KeyIsPressed(unsigned char keycode) const noexcept; // Bir tuşun basılı olup olmadığını kontrol eder
	std::optional<Event> ReadKey() noexcept;                 // Bir tuş olayını okur
	bool KeyIsEmpty() const noexcept;                        // Tuş olayı kuyruğunun boş olup olmadığını kontrol eder
	void FlushKey() noexcept;                                // Tuş olayı kuyruğunu temizler

	// Karakter olayı fonksiyonları
	std::optional<char> ReadChar() noexcept;                 // Bir karakter olayını okur
	bool CharIsEmpty() const noexcept;                       // Karakter olayı kuyruğunun boş olup olmadığını kontrol eder
	void FlushChar() noexcept;                               // Karakter olayı kuyruğunu temizler
	void Flush() noexcept;                                   // Tüm olayları temizler

	// Otomatik tekrar kontrolü
	void EnableAutorepeat() noexcept;                        // Otomatik tekrarı etkinleştirir
	void DisableAutorepeat() noexcept;                       // Otomatik tekrarı devre dışı bırakır
	bool AutorepeatIsEnabled() const noexcept;               // Otomatik tekrarın etkin olup olmadığını kontrol eder
private:
	// Özel fonksiyonlar
	void OnKeyPressed(unsigned char keycode) noexcept;       // Tuşa basıldığında çağrılır
	void OnKeyReleased(unsigned char keycode) noexcept;      // Tuş bırakıldığında çağrılır
	void OnChar(char character) noexcept;                    // Karakter girildiğinde çağrılır
	void ClearState() noexcept;                              // Klavye durumunu temizler

	// Kuyrukları belirli bir boyutta tutmak için yardımcı fonksiyon
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;              // Maksimum tuş sayısı
	static constexpr unsigned int bufferSize = 16u;          // Maksimum kuyruk boyutu
	bool autorepeatEnabled = false;                          // Otomatik tekrar durumu
	std::bitset<nKeys> keystates;                            // Tuş durumları
	std::queue<Event> keybuffer;                             // Tuş olayları kuyruğu
	std::queue<char> charbuffer;                             // Karakter olayları kuyruğu
};
