import sys
import time

# ---------------- Helper functions ---------------- #

def load_constant(cmds, reg, val):
    """Load constant value into a register"""
    cmds.append(f"MOV R{reg}, #{val}")
    out_reg = reg
    reg = (reg + 1) % 13
    return cmds, reg, out_reg


def load_variable(cmds, reg, name):
    """Load variable value into a register"""
    cmds.append(f"MOV R{reg}, ={name}")
    addr_reg = reg
    reg = (reg + 1) % 13
    cmds.append(f"MOV R{reg}, [R{addr_reg}]")
    val_reg = reg
    reg = (reg + 1) % 13
    return cmds, reg, addr_reg, val_reg


def emit_arith(cmds, dest, left, op, right, mode):
    """Generate arithmetic instruction"""
    if mode == 1:  # one side constant
        if left.isdigit():
            cmds.append(f"{get_op(op)} R{dest}, #{left}, R{right}")
        elif right.isdigit():
            cmds.append(f"{get_op(op)} R{dest}, R{left}, #{right}")
    else:  # both registers
        cmds.append(f"{get_op(op)} R{dest}, R{left}, R{right}")
    return cmds


def get_op(op):
    """Map operation symbols to ARM mnemonics"""
    return {
        '+': 'ADD',
        '-': 'SUBS',
        '*': 'MUL',
        '/': 'SDIV'
    }.get(op, 'NOP')


def branch_condition(op):
    """Return ARM branch condition"""
    return {
        '>': 'LE',
        '<': 'GE',
        '>=': 'L',
        '<=': 'G',
        '==': 'NE',
        '!=': 'E'
    }[op]

# ---------------- Conversion Logic ---------------- #

def icg_to_assembly(lines):
    cmds, data, declared = [], [], []
    reg = 0

    for idx, line in enumerate(lines):
        parts = line.strip().split()
        if not parts:
            continue

        # Single-token line
        if len(parts) == 1:
            cmds.append(parts[0])

        # goto label
        elif len(parts) == 2 and parts[0] == "goto":
            cmds.append(f"B {parts[1]}")

        # assignment (x = a + b)
        elif len(parts) == 5:
            lhs, _, op1, operator, op2 = parts

            # both constants
            if op1.isdigit() and op2.isdigit():
                cmds, reg, r1 = load_constant(cmds, reg, op1)
                cmds, reg, addr, val = load_variable(cmds, reg, lhs)
                cmds = emit_arith(cmds, val, str(r1), operator, op2, 1)
                cmds.append(f"STR R{val}, [R{addr}]")

            # left const, right var
            elif op1.isdigit():
                cmds, reg, r2a, r2b = load_variable(cmds, reg, op2)
                cmds, reg, a3, a4 = load_variable(cmds, reg, lhs)
                cmds = emit_arith(cmds, a4, op1, operator, str(r2b), 1)
                cmds.append(f"STR R{a4}, [R{a3}]")

            # right const
            elif op2.isdigit():
                cmds, reg, r1a, r1b = load_variable(cmds, reg, op1)
                cmds, reg, a3, a4 = load_variable(cmds, reg, lhs)
                cmds = emit_arith(cmds, a4, str(r1b), operator, op2, 1)
                cmds.append(f"STR R{a4}, [R{a3}]")

            # both vars
            else:
                cmds, reg, r1a, r1b = load_variable(cmds, reg, op1)
                cmds, reg, r2a, r2b = load_variable(cmds, reg, op2)
                cmds, reg, ra, rb = load_variable(cmds, reg, lhs)
                cmds = emit_arith(cmds, rb, r1b, operator, r2b, 2)
                cmds.append(f"STR R{rb}, [R{ra}]")

        # conditional branch
        elif len(parts) == 4:
            prev = lines[idx - 1].split()
            cond = branch_condition(prev[3])
            if prev[2].isdigit() and prev[4].isdigit():
                cmds, reg, r = load_constant(cmds, reg, prev[2])
                cmds.append(f"CMP R{r}, #{prev[4]}")
            else:
                cmds, reg, _, r1 = load_variable(cmds, reg, prev[2])
                if prev[4].isdigit():
                    cmds.append(f"CMP R{r1}, #{prev[4]}")
                else:
                    cmds, reg, _, r2 = load_variable(cmds, reg, prev[4])
                    cmds.append(f"CMP R{r1}, R{r2}")
            cmds.append(f"B{cond} {parts[-1]}")

        # variable definition
        elif len(parts) == 3 and parts[1] == "=":
            var, _, val = parts
            if var not in declared:
                data.append(f"{var}: .WORD {val}")
                declared.append(var)
            else:
                cmds, reg, a1, a2 = load_variable(cmds, reg, var)
                cmds, reg, r3 = load_constant(cmds, reg, val)
                cmds.append(f"STR R{r3}, [R{a1}]")

    return data, cmds

# ---------------- File output ---------------- #

def write_output(code, data, fout):
    fout.write(".text\n")
    for line in code:
        fout.write(line + "\n")
    fout.write("SWI 0x011\n\n.DATA\n")
    for d in data:
        time.sleep(0.01)
        fout.write(d + "\n")

# ---------------- Main Entry ---------------- #

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python asm_generator.py [input_file]")
        sys.exit(1)

    infile = sys.argv[1]
    outfile = infile.split('.')[0] + ".s"

    print("Assembling Intermediate Code...")

    with open(infile) as fin:
        lines = fin.readlines()
    with open(outfile, "w") as fout:
        data, code = icg_to_assembly(lines)
        write_output(code, data, fout)

    print("✅ Assembly code saved as:", outfile)
