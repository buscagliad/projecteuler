import math

class Fract:
    def __init__(self, n, d):
        self.orig_numerator = n
        self.orig_denominator = d
        # Handle signs: make denominator positive
        sign = 1
        if d < 0:
            sign = -1
            n = -n
            d = -d
        if n < 0:
            sign = -sign
            n = -n
        common_factor = math.gcd(n, d)
        self.red_numerator = sign * (n // common_factor)
        self.red_denominator = d // common_factor
        self.related_value = 0
        
    def setrv(self, rv):
        self.related_value = rv
    
    def getrv(self):
        return self.related_value
    
    def strid(self):
        return str(self.red_numerator) + '/' + str(self.red_denominator)

    def out(self, with_original=False):
        if with_original:
            print(f"Original: {self.orig_numerator} / {self.orig_denominator}")
        print(f"Reduced: {self.red_numerator} / {self.red_denominator}")

    def to_str(self):
        return f"{self.red_numerator} / {self.red_denominator}"

    def __neg__(self):
        return Fract(-self.red_numerator, self.red_denominator)

    def __mul__(self, other):
        return Fract(self.red_numerator * other.red_numerator, self.red_denominator * other.red_denominator)

    def __add__(self, other):
        return Fract(self.red_numerator * other.red_denominator + self.red_denominator * other.red_numerator,
                     self.red_denominator * other.red_denominator)

    def __sub__(self, other):
        return self + (-other)

    def __truediv__(self, other):
        return Fract(self.red_numerator * other.red_denominator, self.red_denominator * other.red_numerator)

    def __mod__(self, other):
        # Fraction modulo: a/b % c/d = (a*d % b*c) / (b*d) assuming positive integers
        return Fract((self.red_numerator * other.red_denominator) % (self.red_denominator * other.red_numerator),
                     self.red_denominator * other.red_denominator)

    def __lt__(self, other):
        return self.red_numerator * other.red_denominator < self.red_denominator * other.red_numerator

    def __eq__(self, other):
        return self.red_numerator == other.red_numerator and self.red_denominator == other.red_denominator

    def __ne__(self, other):
        return not self == other

    def __le__(self, other):
        return self == other or self < other

    def __gt__(self, other):
        return not (self == other or self < other)

    def __ge__(self, other):
        return self == other or self > other

    def __imul__(self, other):
        return self * other

    def __iadd__(self, other):
        return self + other

    def __itruediv__(self, other):
        return self / other

    def __imod__(self, other):
        return self % other

    def __str__(self):
        return self.to_str()

    def __repr__(self):
        return f"Fract({self.orig_numerator}, {self.orig_denominator})"

# Example usage
if __name__ == "__main__":
    f1 = Fract(4, 6)
    f2 = Fract(1, 3)
    f1.out(with_original=True)
    print(f1 + f2)
    print(f1 - f2)
    print(f1 * f2)
    print(f1 / f2)
    print(f1 % f2)
    print(f1 < f2)
    print(f1 == Fract(2, 3))
    print(f1 > f2)
