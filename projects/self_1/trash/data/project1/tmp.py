import re
str = " ".join(open("main.cpp","r").readlines())
print(str);
print(re.findall(r"/\*[\s\S]*\*/",str))
