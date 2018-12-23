#ifndef Device_hpp
#define Device_hpp

#include <vector>

class Device {
public:
    
    enum opcode : char {
        addr, addi,
        mulr, muli,
        banr, bani,
        borr, bori,
        setr, seti,
        gtir, gtri, gtrr,
        eqir, eqri, eqrr
    };
    
    Device();
    
    void setReg(const std::vector<int> &);
    
    const std::vector<int> & instruction(const std::vector<int> &);
    
    const std::vector<int> & runOp(const opcode, const int, const int, const int);
    
    const std::vector<int> & safeRunOp(const opcode, const int, const int, const int);
    
private:
    std::vector<int> instr;
    std::vector<int> reg;
    
    void addRegister();
    void addImmediate();
    void multiplyRegister();
    void multiplyImmediate();
    void bitAndReg();
    void bitAndImm();
    void bitOrReg();
    void bitOrImm();
    void setReg();
    void setImm();
    void gtImmReg();
    void gtRegImm();
    void gtRegReg();
    void eqImmReg();
    void eqRegImm();
    void eqRegReg();
    
    
};

#endif /* Device_hpp */
