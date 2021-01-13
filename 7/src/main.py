from read import read_words
from dictonary import BruteForceDictionary, BinarySearchDictionary, SegmentSearchDictionary
from time import process_time, process_time_ns 
from random import shuffle

def equalDictionary(dictionaryA, dictionaryB):
    keys = set(dictionaryA.keys())
    if keys != set(dictionaryB.keys()):
        return False
    for key in keys:
        if (dictionaryA[key] != dictionaryB[key]):
            return False
    return True

def getTime(key, dictionary, samples = 50):
    t = 0
    for _ in range(samples):
        t_start = process_time()
        res = key in dictionary
        t_end = process_time()
        t += t_end - t_start
    return 1000 * t / samples

def fill_dictionary(dictionary, words):
    for word in words:
        if word not in dictionary:
            dictionary[word] = 1
        else:
            dictionary[word] += 1
    return dictionary

filename = 'data/dalf.txt'
words = read_words(filename)

print(f'count words:  {len(words)}')

#pyDictionary = fill_dictionary(dict(), words) 
bruteForceDictionary = fill_dictionary(BruteForceDictionary(), words) 
binarySearchDictionary = fill_dictionary(BinarySearchDictionary(), words)
segmentSearchDictionary = fill_dictionary(SegmentSearchDictionary(), words)

unique_words = bruteForceDictionary.keys()

# frequency analysis
initialLettersDictionary = fill_dictionary(BinarySearchDictionary(), map(lambda x: x[0], unique_words))
frequency_initial_letters = initialLettersDictionary.keys()
frequency_initial_letters.sort(key=lambda key: initialLettersDictionary[key], reverse=True)
segmentSearchDictionary.sort_segments(frequency_initial_letters)


print(f'unique words: {len(unique_words)}')

test_words = unique_words + ["несуществующееСлово"]
# shuffle(test_words)

test_data = []
for word in test_words:
    t0 = getTime(word, bruteForceDictionary, 1)
    t1 = getTime(word, binarySearchDictionary, 1)
    t2 = getTime(word, segmentSearchDictionary, 1)
    test_data += [(word, t0, t1, t2)]

with open('data/test.dat', 'wt', encoding='UTF-8') as file:
    file.write('word bruteForce binarySearch segmentSearch\n')
    for data in test_data:
        file.write(f'{data[0]:20} ')
        file.write(f'{data[1]:10.6f} ')
        file.write(f'{data[2]:10.6f} ')
        file.write(f'{data[3]:10.6f}\n')

# if not equalDictionary(bruteForceDictionary, binarySearchDictionary):
#     raise Exception('dict not eq')
# 
# if not equalDictionary(binarySearchDictionary, segmentSearchDictionary):
#     raise Exception('dict not eq')

# word = input('Input word: ').strip().lower()
# if word in bruteForceDictionary:
#     print(f'word {word} enters the text {bruteForceDictionary[word]} times')
# else:
#     print(f'word {word} not found')