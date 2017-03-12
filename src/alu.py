# Logical operations
def AND(r, value):
    r.A &= value
    r.P_set_signs(r.A)

def EOR(r, value):
    r.A ^= value
    r.P_set_signs(r.A)

def ORA(r, value):
    r.A |= value
    r.P_set_signs(r.A)

def BIT(r, value):
    result = r.A & value
    if result == 0:
        r.P_set_Z()

    if (result >> 6) & 1 == 1:
        r.P_set_V()
    else:
        r.P_unset_V()
    
    if (value >> 7) & 1 == 1:
        r.P_set_N()
    else:
        r.P_unset_N()

    if (value >> 6) & 1 == 1:
        r.P_set_V()
    else:
        r.P_unset_V()

# Arithmetic Operations
def ADC(r, value):
    r.A += value + r.P_get_C() # Not implementing decimal mode since NES does not support it 
    r.P_set_signs(r.A)
    if r.A > 0xff:
        r.P_set_C()
    else:
        r.P_unset_C()

def SBC(r, value):
    ADC(r, ~value)

# Helper functions
def __compare(r, val1, val2):
    result = val1 - val2

    if result == 0:
        r.P_set_C()
        r.P_set_Z()
    else result >= 0x80:
        r.P_set_N()
    else:
        r.P_set_C()

# Compare Functions
def CMP(r, value):
    __compare(r, r.A, value)

def CMX(r, value):
    __compare(r, r.X, value)

def CMY(r, value):
    __compare(r, r.Y, value)

# Increments and Decrements
def INX(r):
    r.X += 1
    r.P_set_signs(r.X)

def DEX(r):
    r.X -= 1
    r.P_set_signs(r.X)

def INY(r):
    r.Y += 1
    r.P_set_signs(r.Y)

def DEY(r):
    r.Y -= 1
    r.P_set_signs(r.Y)

def INC(r, loc):
    pass

def DEC(r, loc):
    pass

# Shifts and Rotations
def ASL(r, **kwargs):
    pass

def LSR(r, **kwargs):
    pass

def ROL(r, **kwargs):
    pass

def ROR(r, **kwargs):
    pass