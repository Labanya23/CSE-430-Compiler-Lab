class Symbol:
    def __init__(self, name, typ, size, dim, line, addr):
        self.name = name
        self.typ = typ
        self.size = size
        self.dim = dim
        self.line = line
        self.addr = addr

class SymbolTable:
    def __init__(self, bucket_size=10):
        self.bucket_size = bucket_size
        self.table = [[] for _ in range(bucket_size)]

    def hash_func(self, key):
        return sum(ord(c) for c in key) % self.bucket_size

    def insert(self, symbol):
        index = self.hash_func(symbol.name)
        # Check if symbol exists, update instead
        for sym in self.table[index]:
            if sym.name == symbol.name:
                print(f"Symbol '{symbol.name}' already exists. Use update instead.")
                return
        self.table[index].append(symbol)
        print(f"Inserted symbol '{symbol.name}' in bucket {index}")

    def search(self, name):
        index = self.hash_func(name)
        for sym in self.table[index]:
            if sym.name == name:
                return sym
        return None

    def delete(self, name):
        index = self.hash_func(name)
        for i, sym in enumerate(self.table[index]):
            if sym.name == name:
                self.table[index].pop(i)
                print(f"Deleted symbol '{name}' from bucket {index}")
                return
        print(f"Symbol '{name}' not found for deletion")

    def update(self, name, typ, size, dim, line, addr):
        sym = self.search(name)
        if not sym:
            print(f"Symbol '{name}' not found for update")
            return
        sym.typ = typ
        sym.size = size
        sym.dim = dim
        sym.line = line
        sym.addr = addr
        print(f"Updated symbol '{name}'")

    def display(self):
        cols = [("Bucket", 8), ("Name", 12), ("Type", 12), ("Size", 6), ("Dim", 6), ("Line", 6), ("Address", 14)]
        header = " | ".join(f"{col[0]:<{col[1]}}" for col in cols)
        print(header)
        print("-" * len(header))
        for bkt_no, bucket in enumerate(self.table):
            for sym in bucket:
                print(f"{bkt_no:<8} | {sym.name:<12} | {sym.typ:<12} | {sym.size:<6} | {sym.dim:<6} | {sym.line:<6} | {sym.addr:<14}")

def get_symbol_input(existing_name=None):
    if existing_name:
        name = existing_name
        print(f"Updating symbol '{name}' (name cannot be changed)")
    else:
        name = input("Name: ").strip()
    typ = input("Type: ").strip()
    size = int(input("Size: "))
    dim = int(input("Dimension: "))
    line = int(input("Line number: "))
    addr = input("Address: ").strip()
    return Symbol(name, typ, size, dim, line, addr)

def main():
    st = SymbolTable()
    while True:
        print("\nMenu:")
        print("1. Insert")
        print("2. Search")
        print("3. Delete")
        print("4. Update")
        print("5. Show")
        print("6. Exit")
        choice = input("Choose an option (1-6): ").strip()

        if choice == '1':
            print("Insert new symbol:")
            sym = get_symbol_input()
            st.insert(sym)

        elif choice == '2':
            name = input("Enter name to search: ").strip()
            sym = st.search(name)
            if sym:
                print("Symbol found:")
                print(f"Name: {sym.name}, Type: {sym.typ}, Size: {sym.size}, Dim: {sym.dim}, Line: {sym.line}, Addr: {sym.addr}")
            else:
                print(f"Symbol '{name}' not found")

        elif choice == '3':
            name = input("Enter name to delete: ").strip()
            st.delete(name)

        elif choice == '4':
            name = input("Enter name to update: ").strip()
            if st.search(name):
                sym = get_symbol_input(existing_name=name)
                st.update(sym.name, sym.typ, sym.size, sym.dim, sym.line, sym.addr)
            else:
                print(f"Symbol '{name}' not found")

        elif choice == '5':
            st.display()

        elif choice == '6':
            print("Exiting...")
            break

        else:
            print("Invalid choice. Please enter a number between 1 and 6.")

if __name__ == "__main__":
    main()
