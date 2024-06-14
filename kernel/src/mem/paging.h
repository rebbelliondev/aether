#ifndef PAGING_H_IMPORT
#define PAGING_H_IMPORT

typedef uint64_t pt_entry_t;

// Page table structure
typedef struct page_table {
    pt_entry_t entries[512];
} page_table_t;

page_table_t *alloc_page_table();
void map_page(page_table_t *pml4, uint64_t virtual_address, uint64_t physical_address, uint64_t flags);
void load_page_tables(page_table_t *pml4);
void enable_paging();

void *alloc_page();
void free_page(void *page);
void get_memmap();

typedef struct page {
    struct page *next;
} page_t;
#define page_size 4096

#endif