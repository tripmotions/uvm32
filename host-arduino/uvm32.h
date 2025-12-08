#ifndef UVM32_H
#define UVM32_H 1

#include <stdint.h>
#include <stdbool.h>
#include "common/uvm32_sys.h"

#define LIST_OF_UVM32_ERRS \
    X(UVM32_ERR_NONE) \
    X(UVM32_ERR_NOTREADY) \
    X(UVM32_ERR_MEM_RD) \
    X(UVM32_ERR_MEM_WR) \
    X(UVM32_ERR_BAD_SYSCALL) \
    X(UVM32_ERR_HUNG) \
    X(UVM32_ERR_INTERNAL_CORE) \
    X(UVM32_ERR_INTERNAL_STATE) \

#define X(name) name,
typedef enum {
  LIST_OF_UVM32_ERRS
} uvm32_err_t;
#undef X

typedef enum {
    UVM32_EVT_ERR,
    UVM32_EVT_SYSCALL,
    UVM32_EVT_YIELD,
    UVM32_EVT_END,
} uvm32_evt_typ_t;

typedef enum {
    UVM32_SYSCALL_TYP_BUF_TERMINATED_WR,   // data write from vm, NULL terminated string of bytes, in uvm32_evt_syscall_t.val.buf
    UVM32_SYSCALL_TYP_VOID,     // no data
    UVM32_SYSCALL_TYP_U32_WR,   // data write from vm, in uvm32_evt_syscall_t.val.u32
    UVM32_SYSCALL_TYP_U32_RD,   // data read from vm, expects response in uvm32_evt_syscall_t.val.u32p
} uvm32_syscall_typ_t;

typedef uint32_t uvm32_user_syscall_code_t;

// user supplied mapping from syscall to typed syscall
typedef struct {
    uint32_t syscall;
    uvm32_user_syscall_code_t code;
    uvm32_syscall_typ_t typ;
} uvm32_mapping_t;

typedef struct {
    uint8_t *ptr;
    uint32_t len;
} uvm32_evt_syscall_buf_t;

typedef struct {
    uvm32_syscall_typ_t typ;
    uvm32_user_syscall_code_t code;
    union {
        uvm32_evt_syscall_buf_t buf;
        uint32_t u32;
        uint32_t *u32p;
    } val;
} uvm32_evt_syscall_t;

typedef struct {
    uvm32_err_t errcode;
    const char *errstr;
} uvm32_evt_err_t;

typedef struct {
    uvm32_evt_typ_t typ;
    union {
        uvm32_evt_syscall_t syscall;
        uvm32_evt_err_t err;
    } data;
} uvm32_evt_t;

#define MINIRV32_DECORATE static
#define MINI_RV32_RAM_SIZE UVM32_MEMORY_SIZE
#define MINIRV32_POSTEXEC(pc, ir, retval) {if (retval > 0) return 3;}
#ifndef MINIRV32_IMPLEMENTATION
#define MINIRV32_STEPPROTO
#endif
#include "mini-rv32ima.h"

typedef enum {
    UVM32_STATUS_PAUSED,
    UVM32_STATUS_RUNNING,
    UVM32_STATUS_ERROR,
    UVM32_STATUS_ENDED,
} uvm32_status_t;

typedef struct {
    uvm32_status_t status;
    uvm32_err_t err;
    struct MiniRV32IMAState* core;  // points at end of memory
    uint8_t memory[UVM32_MEMORY_SIZE];
    uvm32_evt_t ioevt; // for building up in callbacks
    const uvm32_mapping_t *mappings;
    uint32_t numMappings;
} uvm32_state_t;

void uvm32_init(uvm32_state_t *vmst, const uvm32_mapping_t *mappings, uint32_t numMappings);
bool uvm32_load(uvm32_state_t *vmst, uint8_t *rom, int len);
bool uvm32_hasEnded(const uvm32_state_t *vmst);
uint32_t uvm32_run(uvm32_state_t *vmst, uvm32_evt_t *evt, uint32_t instr_meter);

#endif
