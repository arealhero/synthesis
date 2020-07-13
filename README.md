# `View` class

Протестировано на
* macOS 10.15.5 Catalina (clang version 10.0.0, CMake version 3.17.3)
* Linux Mint 20 Ulyana (Cinnamon, g++ version 9.3.0, CMake version 3.16.3)

## Установка

```shell script
git clone https://github.com/arealhero/synthesis
cd synthesis
mkdir build
cd build
cmake ..
make
```

## Сравнение `View` и `FastView`

| Class name | Add         | Remove      | Find        | Get    |
|------------|-------------|-------------|-------------|--------|
| `View`     | `O(n)`      | `O(n)`      | `O(n)` | `O(1)` |
| `FastView` | `O(log(n))` | `O(log(n))` | `O(n)` | `O(n)` |

В описании задания сказано, что

> `add` и `remove` вызываются чрезвычайно редко.

Можно предположить, что `Get` будет вызываться гораздо чаще. Следовательно, в данном случае лучше использовать `View`.

_Замечание: в файле `include/Folder.h` присутствует using-директива, с помощью которой можно проверить работоспособность `View` и `FastView`._
