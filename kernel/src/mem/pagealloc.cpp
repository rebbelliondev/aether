#include "limine.h"
#include <stddef.h>

// TAKE NOTE THAT THIS IS GOING TO BE CHANGED IN THE FUTURE

static struct limine_memmap_request mem_mapget = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 2
};
typedef struct page {
    struct page *next;
} page_t;
#define page_size 4096
static page_t *free_pages = NULL;

void get_memmap() {
    if (mem_mapget.response == NULL) {
        asm volatile ("cli; hlt");
        return;
    }



    for (uint64_t i = 0; i < mem_mapget.response->entry_count; i++) {
        struct limine_memmap_entry *entry = mem_mapget.response->entries[i];
                switch (entry->type) {
            case LIMINE_MEMMAP_USABLE:
                  {
                    uint64_t address = entry->base;
                    uint64_t end = entry->base + entry->length;

                    // Align address to PAGE_SIZE
                    if (address % page_size!= 0) {
                        address += page_size - (address % page_size);
                    }

                    // Add pages to free list
                    for (; address + page_size <= end; address += page_size) {
                        page_t *page = (page_t *)address;
                        page->next = free_pages;
                        free_pages = page;
                    }
                }
               
                break;
            case LIMINE_MEMMAP_RESERVED:
                    // GOING TO BE ADDED LATER NOT RN
                break;
            // Handle other types as needed
        }
    }
}


// Inline assembly to halt the CPU
void halt() {
    asm volatile ("cli; hlt" : : : "memory");
}
void *alloc_page() {
    if (free_pages == NULL) {
        halt();
        return NULL;
    }

    page_t *page = free_pages;
    free_pages = free_pages->next;
    return (void *)page;
}

// Function to free a page
void free_page(void *page) {
    page_t *p = (page_t *)page;
    p->next = free_pages;
    free_pages = p;
}

// Inline assembly to halt the CPU

