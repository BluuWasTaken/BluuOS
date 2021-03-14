#pragma once
#include "BluuUEFI/EFI_TYPES.h"

static UINT32 page_directory[1024] __attribute__((aligned(4096)));
static UINT32 first_page_table[1024] __attribute__((aligned(4096)));

extern void enable_paging();
extern void load_page_directory(UINT64 Address);