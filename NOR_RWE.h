#ifndef NOR_RW_H 
#define NOR_RW_H

void NOR_byte_write(uint8_t *ptr);
void NOR_byte_read(uint8_t *ptr);
void NOR_long_words_write(uint32_t *ptr);
__attribute__((ramfunc))
void NOR_block_write(uint32_t *ptr);
void NOR_bank_erase(uint8_t *ptr);

#endif
