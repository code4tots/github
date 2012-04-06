#!/usr/bin/python
# 3.28.2012
# Simple ray casting with Python.
#
# Pretend that the only source of light is located at eye, and
# the only objects in the scene are spheres.

# Model.
class Model:
    def __init__(self):
        # Individual spheres have form [(x,y,z), radius]
        # i.e. [ center, radius ]
        self.spheres = []
        
        # Screen is always set to be perpendicular to z-axis.
        # [ (width, height), z ]
        # i.e. [ dimensionsOfImage, distanceFromEye ]
        self.screen = [ (256,256), 128 ]
        
    # Some helper methods
    @staticmethod
    def lengthOfVector(vector):
        from math import sqrt
        return sqrt(sum([ x**2 for x in vector]))
        
    @staticmethod
    def normalizeVector(vector):
        l = Model.lengthOfVector(vector)
        
        if l == 0:
            print("Tried to normalize zero vector!")
            return None
            
        return tuple([x/l for x in vector])
    @staticmethod
    def dotProduct(v1,v2):
        return sum([x*y for (x,y) in zip(v1,v2)])
    @staticmethod
    def cosOfAngleBetweenVectors(v1,v2):
        dot = Model.dotProduct(v1,v2)
        return dot / (Model.lengthOfVector(v1)*Model.lengthOfVector(v2))
    @staticmethod
    def sinOfAngleBetweenVectors(v1,v2):
        from math import sqrt
        return sqrt(1 - cosOfAngleBetweenVectors(v1,v2)**2)
    @staticmethod
    def lengthOfPerpendicularFromFirstToSecondVector(v1,v2):
        
        

# Methods for saving data to actual image file (View?).
def saveDataToFile(data, fileName, width, height):
    import Image
    im = Image.new("RGB", (width, height) )
    im.putdata(data)
    im.save(fileName)
def saveTwoDimensionalArrayToFile(twoDimensionalArray, fileName):
    from itertools import product
    width = len(twoDimensionalArray)
    height = len(twoDimensionalArray[0])
    data = [ twoDimensionalArray[x][y] for (x,y) in product(range(width),range(height)) ]
    saveDataToFile(data, fileName, width, height)


# Execution (Controller?).
def main():
    ar = [ [(0,x,0)] * 128 for x in range(512) ]
    saveTwoDimensionalArrayToFile(ar, "some2.bmp")
    print( Model.normalizeVector( (5,12,0) ))
    
if __name__ == '__main__':
    main()