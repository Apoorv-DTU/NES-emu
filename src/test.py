from mem import *
m = Memory()
m.LDX(420, "immediate")
m.LDY(69, "immediate")

m.STX(4, "absolute")
m.STY(6, "absolute")

m.LDY(4, "absolute")
m.LDX(6, "absolute")

m.LDA(70, "absolute")

if m.get_X() == 69 and m.get_Y() == 420:
    print("ALL TESTS ARE GO!!")