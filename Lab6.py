import re

class TACGenerator:
    def __init__(self):
        self.temp_count = 1
        self.code = []

    def new_temp(self):
        t = f"T{self.temp_count}"
        self.temp_count += 1
        return t

    def generate(self, expr):
        expr = expr.replace("×", "*").replace(" ", "")
        val = self.handle_expr(expr)
        return val

    def handle_expr(self, expr):
        expr = expr.strip()

        # Process innermost parentheses
        while "(" in expr:
            inner = re.findall(r"\([^()]*\)", expr)
            for sub in inner:
                val = self.handle_expr(sub[1:-1])
                expr = expr.replace(sub, val, 1)

        # Unary minus at the start
        if expr.startswith("-"):
            val = self.handle_expr(expr[1:])
            t = self.new_temp()
            self.code.append(f"{t} = uminus {val}")
            return t

        # Handle binary ops in precedence order
        # Multiplication first
        if "*" in expr:
            parts = expr.split("*", 1)
            left = self.handle_expr(parts[0])
            right = self.handle_expr(parts[1])
            t = self.new_temp()
            self.code.append(f"{t} = {left} x {right}")
            return t

        # Addition and subtraction next
        # We split only on the first + or - (left to right)
        for op in ["+", "-"]:
            # skip unary minus already handled
            if op in expr[1:]:
                idx = expr[1:].find(op) + 1
                left = self.handle_expr(expr[:idx])
                right = self.handle_expr(expr[idx + 1:])
                t = self.new_temp()
                if op == "+":
                    self.code.append(f"{t} = {left} + {right}")
                else:
                    self.code.append(f"{t} = {left} - {right}")
                return t

        # Base case (variable)
        return expr


if __name__ == "__main__":
    expr = input("Enter expression: ")
    gen = TACGenerator()
    result = gen.generate(expr)

    print("\nThree Address Code:")
    for i, line in enumerate(gen.code, 1):
        print(f"({i}) {line}")
    print(f"( {len(gen.code)+1} ) T{len(gen.code)+1} = {result}")
