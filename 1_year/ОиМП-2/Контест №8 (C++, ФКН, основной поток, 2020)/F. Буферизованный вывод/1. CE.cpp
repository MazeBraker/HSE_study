#include <utility>

// Это исключение нужно генерировать в функции value
// при обращении к пустому объекту Optional
struct BadOptionalAccess {
};

template<typename T>
class Optional {
private:
    // alignas нужен для правильного выравнивания блока памяти
    alignas(T) unsigned char data[sizeof(T)];
    bool defined = false;

public:
    Optional() : defined(false) {}

    Optional(const T& elem) : defined(true) {
        new(data) T(elem);
    }

    Optional(T && elem) : defined(true) {
        new(data) T(std::move(elem));
    }

    Optional(const Optional& other) : defined(other.def()) {
        if (other.def()) {
            new(data) T(other.def());
        }
    }

    Optional &operator=(const Optional& other) {
        if (other.def()) {
            if (defined) {
                (**this) = other.def();
            } else {
                new(data) T(other.def());
            }
            defined = true;
        } else {
            reset();
        }
        return *this;
    }

    Optional &operator=(const T& elem) {
        if (defined) {
            **this = elem;
        } else {
            new(data) T(elem);
        }
        defined = true;
        return *this;
    }

    Optional &operator=(T && elem) {
        if (defined) {
            **this = std::move(elem);
        } else {
            defined = true;
            new(data) T(std::move(elem));
        }
        return *this;
    }

    bool has_value() const {
        return defined;
    }

    T& operator*() {
        if (defined) {
            return *reinterpret_cast<T *>(data);
        }
    }

    const T& operator*() const {
        return *reinterpret_cast<const T *>(data);
    }

    T *operator->() {
        return reinterpret_cast<T *>(data);
    }

    const T *operator->() const {
        return reinterpret_cast<const T *>(data);
    }

    T& value() {
        if (defined) {
            return **this;
        }
        throw BadOptionalAccess();
    }

    const T& value() const {
        if (defined) {
            return **this;
        }
        throw BadOptionalAccess();
    }

    void reset() {
        if (defined) {
            defined = false;
            reinterpret_cast<T *>(data)->~T();
        }
    }

    ~Optional() {
        (*this).reset();
    }
};