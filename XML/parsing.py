import xml.dom.minidom
document = xml.dom.minidom.parse('deliveries.xml')
article_list = document.getElementsByTagName("article")

print(article_list)
