#!/usr/bin/python
# 3.29.2012

# Ray casting model.
class Sphere:
    def __init__(self, centerVector, radius):
        self.c = centerVector
        self.r = radius
    
class Vector:
    def __init__(self, coordinates):
        self.c = tuple(coordinates)
    def __sub__(self, other):
        return Vector(tuple([ x - y for (x,y) in zip(self.c,other.c) ]))
    def __add__(self, other):
        return Vector(tuple([ x + y for (x,y) in zip(self.c,other.c) ]))
    def __mul__(self, number):
        return Vector(tuple([ number * x for x in self.c]))
    def __rmul__(self, number):
        return self*number
    def sqrlen(self):
        return sum([x*x for x in self.c])
    def len(self):
        from math import sqrt
        return sqrt(sum([ float(x*x) for x in self.c]))
    def __str__(self):
        return '<' + ' '.join([str(x) for x in self.c]) + '>'
    def __repr__(self):
        return str(self)
        
class Line:
    # Constructors
    def __init__(self, pointVector, directionVector):
        self.p = pointVector
        self.d = directionVector
    
    @staticmethod
    def fromTwoPoints(self, p1, p2):
        return Line(p1, p2-p1)
        
    # If p+td is a position on the line, and q is the other point,
    # then the distance from the point on the line to q is |p + td - q|.
    # The t that minimizes this, also minimizes |p + td - q|^2.
    # d/dt ( |p + td - q|^2 )
    # = d/dt ( sum ( pi + tdi - qi )^2 )
    # = sum( 2(pi-qi + tdi)(di) )
    # = sum(2(pi-qi)di) + 2*t*sum(di^2) = 0 -->
    # so we have t = sum(-2(pi-qi)di) / sum(2di^2)
    def distanceFromPoint(self, point_q):
        t_numerator = sum([ -1*(pi-qi)*di for (pi,di,qi) in zip(self.p.c,self.d.c,point_q.c)])
        t_denominator = sum([di*di for di in self.d.c])
        #print(self.d)
        t = float(t_numerator) / float(t_denominator)
        p = self.p + (t*self.d)
        return (p-point_q).len()
        
#print(Vector([0,0]))
line = Line(Vector([0,0]), Vector([1,1]))
print(line.distanceFromPoint(Vector([1,0]))**2)
#print(2*Vector([1,2]))
#print(Vector([1,2])*2)