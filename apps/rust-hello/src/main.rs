#![no_std]
#![no_main]

use core::arch::global_asm;
use core::arch::asm;
use core::panic::PanicInfo;

// fetch IOREQ definitions from C header
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

// startup code
global_asm!(include_str!("../../crt0.S"));

fn syscall(id: u32, n: u32) -> u32 {
    let mut value;
    unsafe {
        asm!("ecall",
            in("a0") n,
            in("a7") id,
            lateout("a1") value,
        );
    }
    return value;
}

fn println(message: &str) {
    let addr_value = message.as_ptr() as u32;
    syscall(IOREQ_PRINTLN, addr_value);
}

fn printd(n: u32) {
    syscall(IOREQ_PRINTD, n);
}

#[no_mangle]
pub extern "C" fn main() {
    for i in 0..10 {
        printd(i);
    }
    println("Hello, world!\0");
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    //println("Something went wrong");
    loop {
        continue;
    }
}
