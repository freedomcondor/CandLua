require("icey");

icey = Icey.new();
print(type(icey));

print(getmetatable(icey))
getmetatable(icey).angry()
print(icey.temper);

icey:angry();
