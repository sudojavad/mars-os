#include "idt.h"

static struct idt_entry idt[TOTAL_INTERRUPTS];
static struct idt_ptr *idt_ptr;

static void idt_entry_set(struct idt_entry *entry, uint64_t addr,
                          uint8_t attr) {
  entry->offset_1 = (uint16_t)addr;
  entry->selector = KERNEL_CODE_SELECTOR;
  entry->attr = attr;
  entry->offset_2 = (uint16_t)(addr >> 16);
  entry->offset_3 = (uint32_t)(addr >> 32);
}

void idt_init() {
  idt_entry_set(&idt[0], (uint64_t)vector0, 0x8e);
  idt_entry_set(&idt[1], (uint64_t)vector1, 0x8e);
  idt_entry_set(&idt[2], (uint64_t)vector2, 0x8e);
  idt_entry_set(&idt[3], (uint64_t)vector3, 0x8e);
  idt_entry_set(&idt[4], (uint64_t)vector4, 0x8e);
  idt_entry_set(&idt[5], (uint64_t)vector5, 0x8e);
  idt_entry_set(&idt[6], (uint64_t)vector6, 0x8e);
  idt_entry_set(&idt[7], (uint64_t)vector7, 0x8e);
  idt_entry_set(&idt[8], (uint64_t)vector8, 0x8e);
  idt_entry_set(&idt[10], (uint64_t)vector10, 0x8e);
  idt_entry_set(&idt[11], (uint64_t)vector11, 0x8e);
  idt_entry_set(&idt[12], (uint64_t)vector12, 0x8e);
  idt_entry_set(&idt[13], (uint64_t)vector13, 0x8e);
  idt_entry_set(&idt[14], (uint64_t)vector14, 0x8e);
  idt_entry_set(&idt[16], (uint64_t)vector16, 0x8e);
  idt_entry_set(&idt[17], (uint64_t)vector17, 0x8e);
  idt_entry_set(&idt[19], (uint64_t)vector19, 0x8e);
  idt_entry_set(&idt[32], (uint64_t)vector32, 0x8e);
  idt_entry_set(&idt[39], (uint64_t)vector39, 0x8e);

  idt_ptr->limit = sizeof(idt) - 1;
  idt_ptr->base = (uint64_t)idt;
  load_idt(idt_ptr);
}

void handler(struct trap_frame *tf) {
  unsigned char isr_value;

  switch (tf->trapno) {
    case 32:
      eoi();
      break;

    case 39:
      isr_value = read_isr();
      if ((isr_value & (1 << 7)) != 0) {
        eoi();
      }
      break;

    default:
      while (1) {
      }
  }
}