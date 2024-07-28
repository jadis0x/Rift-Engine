#include "Keyboard.h"

// Belirtilen tuşun basılı olup olmadığını kontrol eder
// Bu fonksiyon, keystates bitset'ini kullanarak belirtilen tuş kodunun basılı olup olmadığını döner
bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept {
    return keystates[keycode];
}

// Tuş olaylarını okur ve kuyruğun önündeki olayı döndürür
// Eğer tuş olayı kuyruğu boş değilse, en önündeki olayı çıkarır ve döner
std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept {
    if (!keybuffer.empty()) {
        Keyboard::Event e = keybuffer.front();
        keybuffer.pop();
        return e;
    }
    return {}; // Eğer kuyruk boşsa, boş bir std::optional döner
}

// Tuş olayı kuyruğunun boş olup olmadığını kontrol eder
// Bu fonksiyon, tuş olayı kuyruğunun boş olup olmadığını kontrol eder ve sonucu döner
bool Keyboard::KeyIsEmpty() const noexcept {
    return keybuffer.empty();
}

// Tuş olayı kuyruğunu temizler
// Bu fonksiyon, tuş olayı kuyruğunu tamamen temizler
void Keyboard::FlushKey() noexcept {
    keybuffer = std::queue<Event>();
}

// Karakter olaylarını okur ve kuyruğun önündeki karakteri döndürür
// Eğer karakter olayı kuyruğu boş değilse, en önündeki karakteri çıkarır ve döner
std::optional<char> Keyboard::ReadChar() noexcept {
    if (!charbuffer.empty()) {
        unsigned char charCode = charbuffer.front();
        charbuffer.pop();
        return charCode;
    }
    return {}; // Eğer kuyruk boşsa, boş bir std::optional döner
}

// Karakter olayı kuyruğunun boş olup olmadığını kontrol eder
// Bu fonksiyon, karakter olayı kuyruğunun boş olup olmadığını kontrol eder ve sonucu döner
bool Keyboard::CharIsEmpty() const noexcept {
    return charbuffer.empty();
}

// Karakter olayı kuyruğunu temizler
// Bu fonksiyon, karakter olayı kuyruğunu tamamen temizler
void Keyboard::FlushChar() noexcept {
    charbuffer = std::queue<char>();
}

// Tüm olayları temizler (hem tuş hem de karakter olayları)
// Bu fonksiyon, hem tuş hem de karakter olaylarını temizler
void Keyboard::Flush() noexcept {
    FlushKey();
    FlushChar();
}

// Otomatik tekrarı etkinleştirir
// Bu fonksiyon, otomatik tekrar özelliğini etkinleştirir
void Keyboard::EnableAutorepeat() noexcept {
    autorepeatEnabled = true;
}

// Otomatik tekrarı devre dışı bırakır
// Bu fonksiyon, otomatik tekrar özelliğini devre dışı bırakır
void Keyboard::DisableAutorepeat() noexcept {
    autorepeatEnabled = false;
}

// Otomatik tekrarın etkin olup olmadığını kontrol eder
// Bu fonksiyon, otomatik tekrar özelliğinin etkin olup olmadığını döner
bool Keyboard::AutorepeatIsEnabled() const noexcept {
    return autorepeatEnabled;
}

// Bir tuşa basıldığında çağrılır, tuş durumunu günceller ve olayı kuyruğa ekler
void Keyboard::OnKeyPressed(unsigned char keycode) noexcept {
    keystates[keycode] = true; // Tuş durumunu günceller
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Pressed, keycode)); // Olayı kuyruğa ekler
    TrimBuffer(keybuffer); // Kuyruğun boyutunu sınırlandırır
}

// Bir tuş bırakıldığında çağrılır, tuş durumunu günceller ve olayı kuyruğa ekler
void Keyboard::OnKeyReleased(unsigned char keycode) noexcept {
    keystates[keycode] = false; // Tuş durumunu günceller
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Released, keycode)); // Olayı kuyruğa ekler
    TrimBuffer(keybuffer); // Kuyruğun boyutunu sınırlandırır
}

// Bir karakter girildiğinde çağrılır ve karakteri kuyruğa ekler
void Keyboard::OnChar(char character) noexcept {
    charbuffer.push(character); // Karakteri kuyruğa ekler
    TrimBuffer(charbuffer); // Kuyruğun boyutunu sınırlandırır
}

// Klavye durumunu temizler
// Bu fonksiyon, tüm tuş durumlarını sıfırlar
void Keyboard::ClearState() noexcept {
    keystates.reset();
}

// Kuyruğun boyutunu sınırlandırır, belirtilen boyutu aşarsa eski olayları çıkarır
template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept {
    while (buffer.size() > bufferSize) {
        buffer.pop();
    }
}