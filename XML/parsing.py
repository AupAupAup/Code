import xml.dom.minidom
document = xml.dom.minidom.parse('/home/fnk/Code/Code/XML/deliveries.xml')
article_list = document.getElementsByTagName("article")

i=0
for article in article_list:
    supplier = document.getElementsByTagName("supplier")[i].childNodes[0].nodeValue
    name = document.getElementsByTagName("name")[i].childNodes[0].nodeValue
    print(f"{supplier} supplies: {name}")
    i += 1