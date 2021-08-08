import FreeCAD as App
import Draft
#import importDXF
import importSVG
import math
from variables import *

doc = App.newDocument()

rad1 = (r1-rh)/2+(4*(b1+r1-ro)**2)/(8*(r1-rh))
end1 = math.asin((b1+r1-ro)/rad1)*180/math.pi
#print(end1)

zaxis = App.Vector(0, 0, 1)
p100 = App.Vector(5, rh+rad1, 0)
place1 = App.Placement(p100, App.Rotation(zaxis, 0))
p101 = App.Vector(5, ro+r1-ro, 0)
place2 = App.Placement(p101, App.Rotation(zaxis, 0))

p1 = App.Vector(0, 0, 0)
p2 = App.Vector(0, rh, 0)
p3 = App.Vector(0, ro, 0)
p4 = App.Vector(5, rh, 0)
p5 = App.Vector(5, ro, 0)
p6 = App.Vector(5+b1+(r1-ro), r1, 0)
p7 = App.Vector(5+b1+(r1-ro), r2, 0)
p8 = App.Vector(5+b1+(r1-ro)-b1, r1, 0)
p9 = App.Vector(5+b1+(r1-ro)+2, r2, 0)
p10 = App.Vector(5+b1+(r1-ro)+2, 0, 0)
p11 = App.Vector(0, rh-3, 0)
p12 = App.Vector(5+b1+(r1-ro)+2,rh-3, 0)
p13 = App.Vector(5+b1+(r1-ro)-b2, r2, 0)

line1 = Draft.make_line(p1, p3)
line2 = Draft.make_line(p2, p4)
line3 = Draft.make_line(p3, p5)
line4 = Draft.make_line(p6, p7)
line5 = Draft.make_line(p6, p8)
line6 = Draft.make_line(p7, p9)
line7 = Draft.make_line(p9, p10)
line8 = Draft.make_line(p11, p12)
line9 = Draft.make_line(App.Vector(-5, 0, 0), App.Vector(5+b1+(r1-ro)+2+5, 0, 0))
line10 = Draft.make_line(p8, p13)
line11 = Draft.make_line(p7, p13)
arc1 = Draft.make_circle(rad1, placement=place1, startangle=-90, endangle=-(90-end1))
arc2 = Draft.make_circle(r1-ro, placement=place2, startangle=-90, endangle=0)

objects = [line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, arc1, arc2]

doc.recompute()

#importDXF.export(objects, "test.dxf")
importSVG.export(objects, "impeler.svg")
