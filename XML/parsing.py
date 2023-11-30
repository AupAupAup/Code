import xml.dom.minidom
document = xml.dom.minidom.parse('/home/fnk/Code/Code/XML/deliveries.xml')
deliveries = document.documentElement
article_list = document.getElementsByTagName("article")


name_dict = {}

i=0
for article in article_list:

    supplier = document.getElementsByTagName("supplier")[i].childNodes[0].nodeValue #pull supplier @ index i
    name = document.getElementsByTagName("name")[i].childNodes[0].nodeValue #pull item @ index i

    if supplier not in name_dict:           #if supplier is not yet  present
        name_dict[supplier] = {name}        #add supplier with his item
    elif supplier in name_dict:             #if supplier is already present
        temp = name_dict[supplier]          #save old dict value of item
        temp.add(name)                      #add new value to the set
        name_dict.update({supplier: temp})  #update our dict
    i+=1

supplierlist = name_dict.keys()

outputlist = []

for l in supplierlist:
    sets = name_dict[l]
    if "Hoeller" in l or "Richard" in l:
        temp = []
        for element in sets:
            temp += [element]
        sets = temp
        sets.sort()
        if "Hoeller" in l:
            sets.reverse()
    prod = ""
    for x in sets:
        prod += str(x) + " "
            
    outputlist += [l + " supplies: " + prod]
    
for entry in outputlist:
    if "Reinhardt" in entry:
        print(entry)
for entry in outputlist:
    if "Mertes" in entry:
        print(entry)
for entry in outputlist:
    if "Liebig" in entry:
        print(entry)
for entry in outputlist:
    if "Helbig" in entry:
        print(entry)
for entry in outputlist:
    if "Richard" in entry:
        print(entry)
for entry in outputlist:
    if "Krause" in entry:
        print(entry)
for entry in outputlist:
    if "Hoeller" in entry:
        print(entry)



"""stdout:
Reinhardt Inc. supplies: cabbage 
Mertes Inc. supplies: apple 
Liebig Inc. supplies: apple 
Helbig Inc. supplies: cherries 
Richard Inc. supplies: pineapple cherries 
Krause Inc. supplies: apple cherries 
Hoeller Inc. supplies: cabbage cherries bananas 
"""



#Reinhardt Inc. supplies: cabbage 
#Mertes Inc. supplies: apple 
#Liebig Inc. supplies: apple 
#Helbig Inc. supplies: cherries 
#Richard Inc. supplies: cherries pineapple 
#Krause Inc. supplies: apple cherries 
#Hoeller Inc. supplies: cherries cabbage bananas
