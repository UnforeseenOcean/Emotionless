#include "core/ee/ee.h"
#include "core/ee/interpreter/interpreter.h"

namespace EE
{

ee_state_t ee_state;

ee_interpreter* interpreter;

u32 TranslateAddress(u32 virt_addr)
{
    //TODO: HACKY
    if(virt_addr >= 0x70000000 && virt_addr < 0x70004000) return (virt_addr - 0x6e000000);
    if(virt_addr >= 0x30100000 && virt_addr < 0x32000000) return (virt_addr - 0x30000000);
    return virt_addr & 0x1fffffff;
}

u8 Read8(u32 virt_addr)
{
    return Memory::Read8(TranslateAddress(virt_addr));
}

u32 Read32(u32 virt_addr)
{
    return Memory::Read32(TranslateAddress(virt_addr));
}

u64 Read64(u32 virt_addr)
{
    return Memory::Read64(TranslateAddress(virt_addr));
}

void Write8(u32 virt_addr, u8 data)
{
    Memory::Write8(TranslateAddress(virt_addr),data);
}

void Write32(u32 virt_addr, u32 data)
{
    Memory::Write32(TranslateAddress(virt_addr),data);
}

void Write64(u32 virt_addr, u64 data)
{
    Memory::Write64(TranslateAddress(virt_addr),data);
}

void Write128(u32 virt_addr, ee_reg data)
{
    u32 phys_addr = TranslateAddress(virt_addr);
    Memory::Write64(phys_addr,data.ud[0]);
    Memory::Write64(phys_addr+8,data.ud[1]);
}

}
