#include "core/ee/interpreter/interpreter_tables.h"
#include "core/ee/interpreter/interpreter.h"
#include "core/ee/ee.h"
#include "core/ee/ee_inst.h"

namespace EE
{
namespace interpreter_tables
{

struct ee_op_template
{
    u32 opcode;
    std::function<void(ee_inst)> inst;
};

static ee_op_template primary_table[] =
{
    {0,  ee_interpreter::run_table0},
    {1,  ee_interpreter::run_table1},
    {3,  ee_interpreter::jal},
    {4,  ee_interpreter::beq},
    {5,  ee_interpreter::bne},
    {9,  ee_interpreter::addiu},
    {10, ee_interpreter::slti},
    {11, ee_interpreter::sltiu},
    {12, ee_interpreter::daddi},
    {13, ee_interpreter::ori},
    {15, ee_interpreter::lui},
    {16, ee_interpreter::run_table16},
    {20, ee_interpreter::beql},
    {21, ee_interpreter::bnel},
    {22, ee_interpreter::blezl},
    {31, ee_interpreter::sq},
    {32, ee_interpreter::lb},
    {35, ee_interpreter::lw},
    {43, ee_interpreter::sw},
    {55, ee_interpreter::ld},
    {63, ee_interpreter::sd},
};

static ee_op_template table0[] =
{
    {0,  ee_interpreter::sll},
    {2,  ee_interpreter::srl},
    {8,  ee_interpreter::jr},
    {9,  ee_interpreter::jalr},
    {15, ee_interpreter::sync},
    {16, ee_interpreter::mfhi},
    {18, ee_interpreter::mflo},
    {24, ee_interpreter::mult},
    {27, ee_interpreter::divu},
    {36, ee_interpreter::and_ee},
    {37, ee_interpreter::or_ee},
    {42, ee_interpreter::slt},
    {43, ee_interpreter::sltu},
    {45, ee_interpreter::daddu},
};

static ee_op_template table1[] =
{
};

static ee_op_template table16[] =
{
    {0,  ee_interpreter::mfc0},
    {4,  ee_interpreter::mtc0},
    {16, ee_interpreter::run_table16_16},
};

static ee_op_template table16_16[] =
{
    {2, ee_interpreter::tlbwi},
};

void init_tables()
{
    for(int i = 0; i < 64; i++)
    {
        ee_interpreter::op_table[i] = ee_interpreter::unknown;
    }

    for(int i = 0; i < 64; i++)
    {
        ee_interpreter::op_table0[i] = ee_interpreter::unknown;
    }

    for(int i = 0; i < 32; i++)
    {
        ee_interpreter::op_table1[i] = ee_interpreter::unknown;
    }

    for(int i = 0; i < 32; i++)
    {
        ee_interpreter::op_table16[i] = ee_interpreter::unknown;
    }
    
    for(int i = 0; i < 64; i++)
    {
        ee_interpreter::op_table16_16[i] = ee_interpreter::unknown;
    }

    for(auto& tbl_op : primary_table)
    {
        ee_interpreter::op_table[tbl_op.opcode] = tbl_op.inst;
    }

    for(auto& tbl_op : table0)
    {
        ee_interpreter::op_table0[tbl_op.opcode] = tbl_op.inst;
    }

    for(auto& tbl_op : table1)
    {
        ee_interpreter::op_table1[tbl_op.opcode] = tbl_op.inst;
    }

    for(auto& tbl_op : table16)
    {
        ee_interpreter::op_table16[tbl_op.opcode] = tbl_op.inst;
    }
    
    for(auto& tbl_op : table16_16)
    {
        ee_interpreter::op_table16_16[tbl_op.opcode] = tbl_op.inst;
    }
}
}
}