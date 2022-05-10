#include "../headers/Register.h"
#include "../headers/Map.h"

template <typename T>
Register<T>::Register() {
	Map::registerType<T>();
}