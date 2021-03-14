[BITS 64]
global _enable_paging
global _load_page_directory

_enable_paging:
	;Preserve RBP by pushing
	push rbp
	;Establish stack frame
	mov rbp, rsp
	mov rax, cr0
	or eax, 0x80000000
	mov cr0, rax
	;Restore Stack
	mov  esp, ebp
	pop rbp
	ret
	;

_load_page_directory:
	;Preserve RBP by pushing
	push rbp
	;Establish stack frame
	mov rbp, rsp
	add rsp, 8
	;
	;Load Address of page directory into cr3
	mov rax, [rsp]
	mov cr3, rax
	;
	;Restore Stack
	mov rbp, rsp
	pop rbp
	ret
	
