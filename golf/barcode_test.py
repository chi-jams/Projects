import barcode as b

def case(num, expected):
    n = [int(i) for i in num]
    print str(num) + " " + ("True" if b.fn(n) else "False")

case("20378240", True)
case("33765129", True)
case("77234575", True)
case("00000000", True)

case("21034984", False)
case("69165430", False)
case("11965421", False)
case("12345678", False)
