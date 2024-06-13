#include <stdint.h>
#include <stddef.h>

// Constants
#define PAGE_SIZE 4096
#define PML4_SHIFT 39
#define PDP_SHIFT  30
#define PD_SHIFT   21
#define PT_SHIFT   12

#define PML4_INDEX(x) (((x) >> PML4_SHIFT) & 0x1FF)
#define PDP_INDEX(x)  (((x) >> PDP_SHIFT) & 0x1FF)
#define PD_INDEX(x)   (((x) >> PD_SHIFT) & 0x1FF)
#define PT_INDEX(x)   (((x) >> PT_SHIFT) & 0x1FF)

#define PRESENT 0x1
#define WRITE   0x2
#define USER    0x4

// Page table entry type
typedef uint64_t pt_entry_t;

// Page table structure
typedef struct page_table {
    pt_entry_t entries[512];
} page_table_t;

// Allocate a page table (assuming you have a page allocator)
page_table_t *alloc_page_table() {
    return (page_table_t *)alloc_page();
}

// Map a virtual address to a physical address
void map_page(page_table_t *pml4, uint64_t virtual_address, uint64_t physical_address, uint64_t flags) {
    // Get indices
    uint64_t pml4_idx = PML4_INDEX(virtual_address);
    uint64_t pdp_idx  = PDP_INDEX(virtual_address);
    uint64_t pd_idx   = PD_INDEX(virtual_address);
    uint64_t pt_idx   = PT_INDEX(virtual_address);

    // Get or create PDP
    if (!(pml4->entries[pml4_idx] & PRESENT)) {
        page_table_t *pdp = alloc_page_table();
        pml4->entries[pml4_idx] = (uint64_t)pdp | flags;
    }
    page_table_t *pdp = (page_table_t *)(pml4->entries[pml4_idx] & ~0xFFF);

    // Get or create PD
    if (!(pdp->entries[pdp_idx] & PRESENT)) {
        page_table_t *pd = alloc_page_table();
        pdp->entries[pdp_idx] = (uint64_t)pd | flags;
    }
    page_table_t *pd = (page_table_t *)(pdp->entries[pdp_idx] & ~0xFFF);

    // Get or create PT
    if (!(pd->entries[pd_idx] & PRESENT)) {
        page_table_t *pt = alloc_page_table();
        pd->entries[pd_idx] = (uint64_t)pt | flags;
    }
    page_table_t *pt = (page_table_t *)(pd->entries[pd_idx] & ~0xFFF);

    // Map the page
    pt->entries[pt_idx] = physical_address | flags;
}

// Load page tables into CR3
void load_page_tables(page_table_t *pml4) {
    asm volatile ("mov %0, %%cr3" : : "r" (pml4) : "memory");
}

// Enable paging
void enable_paging() {
    uint64_t cr0;
    uint64_t cr4;

    // Read CR0
    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    // Set the PG (paging) bit in CR0
    cr0 |= 0x80000000;
    // Write back to CR0
    asm volatile ("mov %0, %%cr0" : : "r" (cr0));

    // Read CR4
    asm volatile ("mov %%cr4, %0" : "=r" (cr4));
    // Set the PAE (Physical Address Extension) bit in CR4
    cr4 |= 0x00000020;
    // Write back to CR4
    asm volatile ("mov %0, %%cr4" : : "r" (cr4));
}
