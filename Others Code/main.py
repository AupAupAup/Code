# dual2dec: Umwandlung einer Dualzahl in eine Dezimalzahl
# Die Dualzahl n wird als Liste angebenen, z.B. [1,0,0,1,1,1,1,1]
# Der Rückgabewert der Funktion ist eine ganze Zahl.

def any2dec (n,b):
    result = 0
    for d in n:
        result = result * b
        result = result + d
    return result

# dec2dual: Umwandlung einer Dezimalzahl in eine Dualzahl
# Die Dezimalzahl n wird als ganze Zahl übergeben
# Der Rückgabewert ist eine Liste der Dual-Ziffern .

def dec2any (n,b):
    result = []
    while n>0:
        r = n % b  # % ist Modulo-Operator, d.h. Rest bei Division
        n = n//b   # // ist Ganzzahldivision
        result.insert(0, r)
    return result

loop: bool = True
while loop == True:
    zahlenliste = []
    elements = int(input("Wieviele Ziffern hat die Zahl?"))
    for i in range(0, elements):
        zahl = int(input("Zahl einzeln:"))
        zahlenliste.append(zahl)
    start = int(input ("Was für eine Basis ist das?"))

    dezi = any2dec(zahlenliste,start)

    ziel = []
    elements = int(input("Wieviele Basen brauchst du?"))
    for i in range(0,elements):
        zieleinz = int(input("Basen einzeln:"))
        ziel.append(zieleinz)

    for b in ziel:
        print(dec2any(dezi,b))

    temp = input("q für exit / e für weiter")
    if temp == "e":
        loop = True
    else:
        loop = False
