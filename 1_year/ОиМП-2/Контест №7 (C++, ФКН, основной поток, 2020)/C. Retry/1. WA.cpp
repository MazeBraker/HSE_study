#include <exception>
#include <functional>
#include <optional>

template<typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(std::function<Result()> func,
                                  int retryCount, int sleepTime, bool throwLast) {
    for (auto i = 0; i != retryCount + 1; i++) {
        // повтор попытки
        try {
            Result res = func();
            return res;
        } catch (const Exception &e) {
            // Исключение указанного типа
            if (i != retryCount) {
                Sleep(sleepTime);
                // если попыток не осталось
            } else {
                if (throwLast) {
                    throw e;
                } else {
                    return std::optional<Result>();
                }
            }
        }
    }
}