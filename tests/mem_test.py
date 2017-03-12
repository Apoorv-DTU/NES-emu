from mem import *
from nose.tools import *

m = Memory()

def test_LDX_immediate():
    m.LDX(10, "immediate")
    assert m.X == 10

def test_LDY_immediate():
    m.LDY(6, "immediate")
    assert m.Y == 6

def test_LDA_immediate():
    m.LDA(16, "immediate")
    assert m.A == 16

def test_STX_absolute():
    m.STX(4, "absolute")
    assert m.mem[4] == 10

def test_STY_absolute():
    m.STY(6, "absolute")
    assert m.mem[6] == 6

def test_STX_absolute():
    m.STX(4, "absolute")
    assert m.mem[4] == 10

def test_STA_absolute():
    m.STA(6, "absolute")
    assert m.mem[6] == 16

def test_LDY_absolute():
    m.LDY(4, "absolute")
    assert m.Y == 10
    m.LDY(40, "absolute")
    assert m.Y == None

def test_LDX_absolute():
    m.LDX(6, "absolute")
    assert m.X == 16
    m.LDX(40, "absolute")
    assert m.X == None

def test_LDA_absolute():
    m.LDA(70, "absolute")
    assert m.A == None