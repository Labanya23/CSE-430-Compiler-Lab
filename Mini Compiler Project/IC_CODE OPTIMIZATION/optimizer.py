import re
import sys

# ---------------- Utility Lambdas ---------------- #
is_temp = lambda s: bool(re.fullmatch(r"t\d+", s))
is_identifier = lambda s: bool(re.fullmatch(r"[A-Za-z]\w*", s))

PRINT_MODE = False

# ---------------- Expression Evaluator ---------------- #
def compute(op1, oper, op2):
    """Evaluate a binary operation between constants"""
    a, b = int(op1), int(op2)
    ops = {
        '+': a + b,
        '-': a - b,
        '*': a * b,
        '/': a / b if b != 0 else 0,
        '<': int(a < b),
        '>': int(a > b),
        '||': int(bool(a) or bool(b)),
        '&&': int(bool(a) and bool(b))
    }
    return ops.get(oper, 0)

# ---------------- Pretty Printer ---------------- #
def display_code(lines, title=None):
    if title:
        print(f"\n--- {title} ---")
    for line in lines:
        print(line.strip())
    print()

# ---------------- Optimization Passes ---------------- #
def propagate_constants(lines, consts):
    """Replace variable references with known constants"""
    new_lines = []
    for text in lines:
        text = text.strip()
        if not text or text.endswith(":"):
            new_lines.append(text + "\n")
            continue

        parts = text.split()
        if len(parts) == 3:
            # Simple assignment
            lhs, eq, rhs = parts
            if rhs.isdigit():
                consts[lhs] = rhs
            elif rhs in consts:
                rhs = consts[rhs]
            new_lines.append(f"{lhs} = {rhs}\n")

        elif len(parts) == 5:
            lhs, eq, op1, oper, op2 = parts
            if op1 in consts:
                op1 = consts[op1]
            if op2 in consts:
                op2 = consts[op2]
            new_lines.append(f"{lhs} = {op1} {oper} {op2}\n")

        else:
            new_lines.append(text + "\n")

    return new_lines


def fold_constants(lines):
    """Evaluate expressions where both operands are numeric"""
    new_lines = []
    for line in lines:
        line = line.strip()
        if not line or line.endswith(":"):
            new_lines.append(line + "\n")
            continue

        parts = line.split()
        if len(parts) == 5 and parts[2].isdigit() and parts[4].isdigit():
            val = compute(parts[2], parts[3], parts[4])
            new_lines.append(f"{parts[0]} = {val}\n")
        else:
            new_lines.append(line + "\n")

    return new_lines


def eliminate_dead_code(lines):
    """Remove temporary variables that are never used"""
    cleaned = [ln.strip() for ln in lines if ln.strip() and not ln.strip().endswith(":")]

    temps_defined = {ln.split()[0] for ln in cleaned if len(ln.split()) > 0 and is_temp(ln.split()[0])}
    temps_used = set()

    for ln in cleaned:
        tokens = ln.split()[1:]
        for tok in tokens:
            if is_temp(tok):
                temps_used.add(tok)

    to_remove = temps_defined - temps_used
    new_code = [ln + "\n" for ln in cleaned if not (ln.split()[0] in to_remove if len(ln.split()) > 0 else False)]

    return new_code


# ---------------- File Handling ---------------- #
def read_icg(file_path):
    with open(file_path) as f:
        return f.readlines()

def write_optimized(lines):
    with open("optimized_icg.txt", "w") as f:
        f.writelines(lines)

# ---------------- Driver ---------------- #
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 optimizer.py <icg_file> [--print]")
        sys.exit(1)

    icg_file = sys.argv[1]
    if len(sys.argv) == 3 and sys.argv[2] == "--print":
        PRINT_MODE = True

    code_lines = read_icg(icg_file)
    const_table = {}

    if PRINT_MODE:
        display_code(code_lines, "Original ICG")
        code_lines = propagate_constants(code_lines, const_table)
        display_code(code_lines, "After Constant Propagation")

        code_lines = fold_constants(code_lines)
        display_code(code_lines, "After Constant Folding")

        code_lines = eliminate_dead_code(code_lines)
        display_code(code_lines, "After Dead Code Elimination")

        write_optimized(code_lines)
        print("✅ Optimized ICG written to optimized_icg.txt")

    else:
        code_lines = propagate_constants(code_lines, const_table)
        code_lines = fold_constants(code_lines)
        code_lines = eliminate_dead_code(code_lines)
        write_optimized(code_lines)
