#include "MemoryManager.hpp"


void* operator new(size_t _InChunkSize) {
	return DadEngine::Core::MemoryManager::Allocate(1, _InChunkSize);
}

void operator delete(void * _InMemLocation) noexcept {
	DadEngine::Core::MemoryManager::Deallocate(_InMemLocation);
}
