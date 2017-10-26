a = require("icey");

for i,v in pairs(Icey) do
	print(i,type(v))
end

icey = Icey.new();
print("print",icey);

icey:angry();
icey:angry();
icey:angry();
icey:angry();
icey:angry();
icey:angry();
icey:angry();
icey:angry();
icey:angry();

icey = nil
Icey = nil
a = nil
collectgarbage("collect");

print("after that\n");


-------------- __gc test  -------------
a = {__gc = function () print("gc") end}
b = {c = 1}
setmetatable(b,a)
b = nil
collectgarbage("collect");
print("after that\n");
