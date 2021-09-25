import os

libs = list()
headers = list()

for file in os.listdir("."):
    if file.endswith(".c") and file != "main.c":
        libs.append(file)
        
for file in libs:
    hname = str(file)
    hname.replace(".c", ".h")
    fp = open(hname, 'r+', encoding='ascii')
    fp.close()
    headers.append(hname)
    
for file in libs:
    pass


    
