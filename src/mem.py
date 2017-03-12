class Memory:

    def __init__(self):
        self.mem = {}
        self.stack = [0]*256
        self.A = None
        self.X = None
        self.Y = None
        self.S = 0xff
        self.P = 0

    # getter methods
    def get_A(self):
        return self.A

    def get_X(self):
        return self.X

    def get_Y(self):
        return self.Y

    def get_S(self):
        return self.S

    # functions to set various bits of status flag
    def P_set_N(self):
        self.P |= 128
    
    def P_set_V(self):
        self.P |= 64

    def P_set_B(self):
        self.P |= 16

    def P_set_D(self):
        self.P |= 8

    def P_set_I(self):
        self.P |= 4

    def P_set_Z(self):
        self.P |= 2
    
    def P_set_C(self):
        self.P |= 1


    def P_unset_N(self):
        self.P &= ~128
    
    def P_unset_V(self):
        self.P &= ~64

    def P_unset_B(self):
        self.P &= ~16

    def P_unset_D(self):
        self.P &= ~8

    def P_unset_I(self):
        self.P &= ~4

    def P_unset_Z(self):
        self.P &= ~2
    
    def P_unset_C(self):
        self.P &= ~1

    #functions to get various bits of status flag
    def P_get_N(self):
        return (self.P >> 7) & 1
    
    def P_get_V(self):
        return (self.P >> 6) & 1
    
    def P_get_B(self):
        return (self.P >> 4) & 1

    def P_get_D(self):
        return (self.P >> 3) & 1

    def P_get_I(self):
        return (self.P >> 2) & 1
    
    def P_get_Z(self):
        return (self.P >> 1) & 1
    
    def P_get_C(self):
        return self.P & 1

    # helper functions    
    def P_set_signs(self, value):
        if (value >> 7) & 1 == 1:
            self.P_set_N()
        elif value == 0:
            self.P_set_Z()

    def __store(self, addr, value, mode, XY=None):
        if mode == "absolute":
            self.mem[addr] = value

    def __load(self, addr, mode):
        value = None
        try:
            if mode == "absolute":
                value = self.mem[addr]
            elif mode == "immediate":
                value = addr
        except KeyError:
            print("[WARNING] Loading from unitialized location.")
        else:
            self.P_set_signs(value)
        return value

    # loading and storing commands
    def STA(self, addr, mode):
        self.__store(addr, self.A, mode)
    
    def STX(self, addr, mode):
        self.__store(addr, self.X, mode)

    def STY(self, addr, mode):
        self.__store(addr, self.Y, mode)

    def LDA(self, addr, mode):
        self.A = self.__load(addr, mode)
    
    def LDX(self, addr, mode):
        self.X =self. __load(addr, mode)

    def LDY(self, addr, mode):
        self.Y = self.__load(addr, mode)

    #register transfer commands
    def TAX(self):
        self.P_set_signs(self.A)
        self.X = self.A

    def TAY(self):
        self.P_set_signs(self.A)
        self.Y = self.A

    def TXA(self):
        self.P_set_signs(self.X)
        self.A = self.X

    def TYA(self):
        self.P_set_signs(self.Y)
        self.A = self.Y

    # processor flag commands
    def CLC(self):
        self.P_unset_C()

    def SEC(self):
        self.P_set_C()
    
    def CLD(self):
        self.P_unset_D()
    
    def SED(self):
        self.P_set_D()

    def CLI(self):
        self.P_unset_I()

    def SEI(self):
        self.P_set_I()

    def CLV(self):
        self.P_unset_V()