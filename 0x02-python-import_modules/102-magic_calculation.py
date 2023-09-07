#!/usr/bin/python3

def magic_calculation(a, b):
    add, sub = (None, None)

    if a < b:
        add, sub = (lambda x, y: x + y, lambda x, y: x - y)
        c = add(a, b)

        for i in range(4, 6):
            c = add(c, i)

        return c
    else:
        sub = lambda x, y: x - y
        return sub(a, b)

