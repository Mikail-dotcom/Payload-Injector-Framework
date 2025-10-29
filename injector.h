// ınjector.h

#pragma once // Bu baslık sadece bir kez derlenmesine saglar

#include <windows.h> //Windows apı fonksiyonlarına saglar
#include <stdbool.h> //C dilinde bool veri tipini kullanabilmek için dahil edilir


//BU injector.c dosyasında fonksiyonunn bildirimi kısmıdır
BOOL inject_payload(LPCSTR targetPath, unsigned char* payload, SIZE_T payloadSize);
