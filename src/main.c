//
// Created by vsevolod on 26.01.2021.
//

#include <stdio.h>
#include "mem_internals.h"
#include "mem.h"

void first(void* heap) {
    fprintf(stdout, "Before allocation:\n");
    debug_heap(stdout, heap);
    void* block = _malloc(24);
    fprintf(stdout, "After allocation:\n");
    debug_heap(stdout, heap);
    _free(block);
}

void second(void* heap) {
    fprintf(stdout, "Before allocation:\n");
    debug_heap(stdout, heap);
    void* first_block = _malloc(24);
    void* second_block = _malloc(25);
    fprintf(stdout, "After allocation:\n");
    debug_heap(stdout, heap);
    _free(second_block);
    fprintf(stdout, "After deallocation:\n");
    debug_heap(stdout, heap);
    _free(first_block);
}

void third(void* heap) {
    fprintf(stdout, "Before allocation:\n");
    debug_heap(stdout, heap);
    void* first_block = _malloc(66);
    void* second_block = _malloc(67);
    void* third_block = _malloc(68);
    fprintf(stdout, "After allocation:\n");
    debug_heap(stdout, heap);
    _free(third_block);
    _free(second_block);
    fprintf(stdout, "After deallocation:\n");
    debug_heap(stdout, heap);
    _free(first_block);
}

void fourth(void* heap) {
    fprintf(stdout, "Before allocation:\n");
    debug_heap(stdout, heap);
    void* too_much = _malloc(9000);
    fprintf(stdout, "After too big block allocation, extending old region:\n");
    debug_heap(stdout, heap);
    _free(too_much);
    fprintf(stdout, "After too big block deallocation:\n");
    debug_heap(stdout, heap);
}

void fifth(void* heap) {
    fprintf(stdout, "Before allocation:\n");
    debug_heap(stdout,heap);
    mmap((uint8_t*)heap+5*4096, 1000000, PROT_READ | PROT_WRITE, MAP_PRIVATE | 0x20 | MAP_FIXED, 0, 0 );
    void* too_much_again = _malloc(19484924);
    fprintf(stdout, "After too big block allocation, creating new region:\n");
    debug_heap(stdout,heap);
    _free(too_much_again);
    fprintf(stdout, "After too big block deallocation:\n");
    debug_heap(stdout, heap);
}

int main() {
    void* heap = heap_init(666);
//    first(heap);
//    second(heap);
//    third(heap);
//    fourth(heap);
    fifth(heap);
    return 0;
}