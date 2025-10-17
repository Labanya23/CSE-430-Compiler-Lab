
from collections import defaultdict

def normalize_sym(s):
    # treat 'e' or 'eps' or 'ε' as epsilon symbol 'ε'
    if s in ("e", "eps", "epsilon", "ε"):
        return "ε"
    return s


n = int(input("Enter number of productions: ").strip())
grammar_raw = []
lhs_order = []  
for _ in range(n):
    line = input().strip()
    parts = line.split("->")
    lhs = parts[0].strip()
    rhs = parts[1].strip()
    if lhs not in lhs_order:
        lhs_order.append(lhs)
    alternatives = [alt.strip() for alt in rhs.split("|")]
    prods = []
    for alt in alternatives:
        tokens = [normalize_sym(tok) for tok in alt.split()]
        if len(tokens) == 0:
            tokens = ["ε"]
        prods.append(tokens)
    grammar_raw.append((lhs, prods))

# Build grammar
grammar = defaultdict(list)
for lhs, prods in grammar_raw:
    grammar[lhs].extend(prods)


terminals = set()
for prods in grammar.values():
    for prod in prods:
        for sym in prod:
            if sym != "ε" and sym not in grammar:
                terminals.add(sym)

# Initialize FIRST and FOLLOW
FIRST = defaultdict(set)
FOLLOW = defaultdict(set)

# FIRST of terminals
for t in terminals:
    FIRST[t].add(t)
FIRST["ε"].add("ε")

for A in grammar:
    FIRST[A] = set()

# Compute FIRST
def first_of_sequence(seq):
    if not seq:
        return {"ε"}
    result = set()
    for sym in seq:
        sym_first = FIRST[sym] if sym in FIRST else {sym}
        result |= (sym_first - {"ε"})
        if "ε" not in sym_first:
            return result
    result.add("ε")
    return result

changed = True
while changed:
    changed = False
    for A, prods in grammar.items():
        for prod in prods:
            prod_first = first_of_sequence(prod)
            before = len(FIRST[A])
            FIRST[A] |= prod_first
            if len(FIRST[A]) != before:
                changed = True

# Compute FOLLOW
start_symbol = lhs_order[0]
FOLLOW[start_symbol].add("$")

changed = True
while changed:
    changed = False
    for A, prods in grammar.items():
        for prod in prods:
            for i, B in enumerate(prod):
                if B in grammar:
                    beta = prod[i + 1:]
                    first_beta = first_of_sequence(beta)
                    before = len(FOLLOW[B])
                    FOLLOW[B] |= (first_beta - {"ε"})
                    if "ε" in first_beta or not beta:
                        FOLLOW[B] |= FOLLOW[A]
                    if len(FOLLOW[B]) != before:
                        changed = True

# Formatting
def format_set(s):
    if not s:
        return "{ }"
    s_list = sorted(s, key=lambda x: (x == "$", x == "ε", x))
    inner = ", ".join("'" + tok + "'" for tok in s_list)
    return "{ " + inner + " }"

# Output (in same order as input)
print("\nFIRST sets:")
for nt in lhs_order:
    print(f"FIRST({nt}) = {format_set(FIRST[nt])}")

print("\nFOLLOW sets:")
for nt in lhs_order:
    print(f"FOLLOW({nt}) = {format_set(FOLLOW[nt])}")
