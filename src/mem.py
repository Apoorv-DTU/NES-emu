class Memory:

    def __init__(self):
        self.mem = {}
        self.A = 0
        self.X = 0
        self.Y = 0
        self.S = 0

    def get_A(self):
        return self.A

    def get_X(self):
        return self.X

    def get_Y(self):
        return self.Y

    def get_S(self):
        return self.S

    def __store(self, addr, value, mode, XY=None):
        if mode == "absolute":
            self.mem[addr] = value

    def STA(self, addr, mode):
        self.__store(addr, self.A, mode)
    
    def STX(self, addr, mode):
        self.__store(addr, self.X, mode)

    def STY(self, addr, mode):
        self.__store(addr, self.Y, mode)

    def __load(self, addr, mode):
        try:
            if mode == "absolute":
                return self.mem[addr]
            elif mode == "immediate":
                return addr
        except KeyError:
            print("[WARNING] Loading from unitialized location.")
            return None

    def LDA(self, addr, mode):
        self.A = self.__load(addr, mode)
    
    def LDX(self, addr, mode):
        self.X =self. __load(addr, mode)

    def LDY(self, addr, mode):
        self.Y = self.__load(addr, mode)