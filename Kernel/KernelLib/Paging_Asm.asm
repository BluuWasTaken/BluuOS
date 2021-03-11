[BITS 64]
global _enable_paging
global _load_page_directory

_enable_paging:
	;Preserve EBP by pushing
	push ebp
	;Establish stack frame
	mov ebp, esp
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	;Restore Stack
	mov  esp, ebp
	pop ebp
	ret
	;

_load_page_directory:
	;Preserve EBP by pushing
	push ebp
	;Establish stack frame
	mov ebp, esp
	add esp, 8
	;
	;Load Address of page directory into cr3
	mov eax, [esp]
	mov cr3, eax
	;
	;Restore Stack
	mov ebp, esp
	pop ebp
	ret
	
