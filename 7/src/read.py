import PyPDF2
import textract
import pymorphy2
import re

morph = pymorphy2.MorphAnalyzer()

#with open(filename, 'rb') as file:
#    pdfReader = PyPDF2.PdfFileReader(file)
#    num_pages = pdfReader.numPages 
#    count = 0
#    #The while loop will read each page.
#    while count < num_pages:
#        pageObj = pdfReader.getPage(count)
#        count +=1
#        text += pageObj.extractText()

def read_words(namefile: str) -> list:
    text = ""
    with open(namefile, 'rt', encoding='UTF-8') as file:
        for line in file:
            text += line

    text = text.replace("'", "")
    # получить слова
    words = re.findall(r'\w+', text)

    words = list(map(lambda word: word.lower(), words))

    # нормализовать слова
    # words = list(map(lambda word: morph.parse(word)[0].normal_form, words))

    return words