from mem import *
from nose.tools import *

m = Memory()

def test_LDX_immediate():
    m.LDX(0x10, "immediate")
    assert m.X == 0x10

def test_LDY_immediate():
    m.LDY(0x0, "immediate")
    assert m.Y == 0x0
    assert m.P_get_Z()

def test_LDA_immediate():
    m.LDA(0x80, "immediate")
    assert m.A == 0x80
    assert m.P_get_N()

def test_STX_absolute():
    m.mem = {}
    m.LDX(0x10, "immediate")
    m.STX(0x0f, "absolute")
    assert m.mem[0x0f] == 0x10

def test_STY_absolute():
    m.mem = {}
    m.LDY(0x0, "immediate")
    m.STY(0xc, "absolute")
    assert m.mem[0xc] == 0x0

def test_STA_absolute():
    m.mem = {}
    m.LDA(0x80, "immediate")
    m.STA(0x06, "absolute")
    assert m.mem[0x06] == 0x80

def test_LDY_absolute():
    m.mem = {0x6a: 0x4f}
    m.LDY(0x6a, "absolute")
    assert m.Y == 0x4f

    m.LDY(0x40, "absolute")
    assert m.Y == None

def test_LDX_absolute():
    m.mem = {0xb6: 0x41}
    m.LDX(0xb6, "absolute")
    assert m.X == 0x41
    
    m.LDX(0x40, "absolute")
    assert m.X == None

def test_LDA_absolute():
    m.mem = {0x70: 0x69}
    m.LDA(0x70, "absolute")
    assert m.A == 0x69

    m.LDA(0x4a, "absolute")
    assert m.A == None