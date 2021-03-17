[BITS 32]
global enable_paging
global load_pdpt
global enable_pae

enable_pae:
	;Preserve EBP by pushing
	push ebp
	;Establish stack frame
	mov ebp, esp

	mov eax, cr4
	;Set 5th bit of CR4
	or eax, 0x10
	mov cr4, eax

	mov  esp, ebp
	pop ebp
	ret

mov ebp, esp
enable_paging:
	;Preserve EBP by pushing
	push ebp
	;Establish stack frame
	mov ebp, esp
	;Set highest bit of CR0
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	;
	;Restore Stack
	mov  esp, ebp
	pop ebp
	ret

load_pdpt:
	;Preserve RBP by pushing
	push ebp
	;Establish stack frame
	mov ebp, esp
	add esp, 8

	;
	;Load Address of page directory into cr3
	mov eax, [esp]
	mov cr3, eax
	;
	
	sub esp, 8
	;Restore Stack
	mov ebp, esp
	pop ebp
	ret
