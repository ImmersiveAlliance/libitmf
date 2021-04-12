
#include <emscripten.h>

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.

EM_JS(void, array_bounds_check_error, (size_t idx, size_t size), {
  throw 'Array index ' + idx + ' out of bounds: [0,' + size + ')';
});

void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    array_bounds_check_error(array_idx, array_size);
  }
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// ITMFEncoder

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_InitStreamsAtStart_0(ITMFEncoder* self) {
  self->InitStreamsAtStart();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_InitStreamsAtEnd_0(ITMFEncoder* self) {
  self->InitStreamsAtEnd();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_InitCustom_0(ITMFEncoder* self) {
  self->InitCustom();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_AddStringProperty_2(ITMFEncoder* self, char* key, char* value) {
  self->AddStringProperty(key, value);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_AddLongProperty_2(ITMFEncoder* self, char* key, int value) {
  self->AddLongProperty(key, value);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_AddFile_1(ITMFEncoder* self, char* filepath) {
  self->AddFile(filepath);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder_Write_2(ITMFEncoder* self, char* location, char* filename) {
  self->Write(location, filename);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_ITMFEncoder___destroy___0(ITMFEncoder* self) {
  delete self;
}

}

