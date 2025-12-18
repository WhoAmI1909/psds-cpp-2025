#include <stdexcept>


template <typename T>
void SwapPtr(T*& ptr1, T*& ptr2) {
    // Проверяем, указывают ли ptr1 и ptr2 на указатели
    if constexpr (std::is_pointer_v<std::remove_pointer_t<T>>) {
        // T* - это указатель на указатель (например: int**)
        // Меняем значения, на которые указываем
        SwapPtr(*ptr1, *ptr2);  // Рекурсивный вызов
    }
    
    // Меняем сами указатели
    T* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}