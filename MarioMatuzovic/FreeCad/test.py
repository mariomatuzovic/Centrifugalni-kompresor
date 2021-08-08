import FreeCAD as App
import Draft
#import importDXF
import importSVG

doc = App.newDocument()

p1 = App.Vector(0, 0, 0)
p2 = App.Vector(1000, 500, 0)
p3 = App.Vector(-250, -500, 0)
p4 = App.Vector(500, 1000, 0)

line1 = Draft.make_line(p1, p2)
line2 = Draft.make_line(p3, p4)

objects = [line1, line2]

doc.recompute()


#importDXF.export(objects, "test.dxf")
importSVG.export(objects, "test.svg")
