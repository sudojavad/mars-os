#include "syscall.h"

#include "../../include/debug.h"
#include "../console/print.h"
#include "stddef.h"

static SYSTEMCALL system_calls[10];

// when we call print function in the user program,
// we just convert the message to the string,
// prepare the string as argument on the user stack
// and execute int instruction

// argptr is the data on the stack in user mode
static int sys_write(int64_t *argptr) {
  write_screen((char *)argptr[0], (int)argptr[1], 0xe);
  return (int)argptr[1];
}

void init_syscall(void) { system_calls[0] = sys_write; }

void syscall(struct trap_frame *tf) {
  // the index number of syscall
  int64_t i = tf->rax;
  int64_t param_count = tf->rdi;
  // points to the args we passed to the function
  int64_t *argptr = (int64_t *)tf->rsi;

  // TODO, since we only have 1 syscall then i != 0
  if (param_count < 0 || i != 0) {
    // the error code
    tf->rax = -1;
    return;
  }

  ASSERT(system_calls[i] != NULL);
  // find syscall by the index,
  // pass the parameters and execute them
  // the rax holds the error code
  tf->rax = system_calls[i](argptr);
}