#include "Device.hpp"

using std::vector;

Device::Device() {
    reg = vector<int>(4, 0);
    instr = vector<int>(4, 0);
}

void Device::setReg(const vector<int> & in) {
    reg = in;
}

const vector<int> & Device::getReg() {
    return reg;
}

void Device::setOpcodes(const vector<opcode> & codes) {
    opcodes = codes;
}

const vector<int> & Device::instruction(const vector<int> & in) {
    instr = in;
    runOp(opcodes[instr[0]], in[1], in[2], in[3]);
    return reg;
}

const vector<int> & Device::runOp(const opcode op, const int a, const int b, const int c) {
    
    instr[1] = a;
    instr[2] = b;
    instr[3] = c;
    
    switch (op) {
        case addr:
            addRegister();
            break;
        case addi:
            addImmediate();
            break;
        case mulr:
            multiplyRegister();
            break;
        case muli:
            multiplyImmediate();
            break;
        case banr:
            bitAndReg();
            break;
        case bani:
            bitAndImm();
            break;
        case borr:
            bitOrReg();
            break;
        case bori:
            bitOrImm();
            break;
        case setr:
            setReg();
            break;
        case seti:
            setImm();
            break;
        case gtir:
            gtImmReg();
            break;
        case gtri:
            gtRegImm();
            break;
        case gtrr:
            gtRegReg();
            break;
        case eqir:
            eqImmReg();
            break;
        case eqri:
            eqRegImm();
            break;
        case eqrr:
            eqRegReg();
            break;
    }
    
    return reg;
    
}

const vector<int> & Device::safeRunOp(const opcode op, const int a, const int b, const int c) {
    
    if (c > 3) throw false;
    
    switch (op) {
        case addr:
        case mulr:
        case banr:
        case borr:
        case setr:
        case gtrr:
        case eqrr:
            if (a > 3 or b > 3) throw false;
            else break;
        case addi:
        case muli:
        case bani:
        case bori:
        case seti:
        case gtir:
        case eqir:
            if (a > 3) throw false;
            else break;
        case gtri:
        case eqri:
            if (b > 3) throw false;
            else break;
    }
    
    return runOp(op, a, b, c);
}



void Device::addRegister() {
    reg[instr[3]] = reg[instr[1]] + reg[instr[2]];
}

void Device::addImmediate() {
    reg[instr[3]] = reg[instr[1]] + instr[2];
}

void Device::multiplyRegister() {
    reg[instr[3]] = reg[instr[1]] * reg[instr[2]];
}

void Device::multiplyImmediate() {
    reg[instr[3]] = reg[instr[1]] * instr[2];
}

void Device::bitAndReg() {
    reg[instr[3]] = reg[instr[1]] bitand reg[instr[2]];
}

void Device::bitAndImm() {
    reg[instr[3]] = reg[instr[1]] bitand instr[2];
}

void Device::bitOrReg() {
    reg[instr[3]] = reg[instr[1]] bitor reg[instr[2]];
}

void Device::bitOrImm() {
    reg[instr[3]] = reg[instr[1]] bitor instr[2];
}

void Device::setReg() {
    reg[instr[3]] = reg[instr[1]];
}

void Device::setImm() {
    reg[instr[3]] = instr[1];
}

void Device::gtImmReg() {
    reg[instr[3]] = instr[1] > reg[instr[2]] ? 1 : 0;
}

void Device::gtRegImm() {
    reg[instr[3]] = reg[instr[1]] > instr[2] ? 1 : 0;
}

void Device::gtRegReg() {
    reg[instr[3]] = reg[instr[1]] > reg[instr[2]] ? 1 : 0;
}

void Device::eqImmReg() {
    reg[instr[3]] = instr[1] == reg[instr[2]] ? 1 : 0;
}

void Device::eqRegImm() {
    reg[instr[3]] = reg[instr[1]] == instr[2] ? 1 : 0;
}

void Device::eqRegReg() {
    reg[instr[3]] = reg[instr[1]] == reg[instr[2]] ? 1 : 0;
}
