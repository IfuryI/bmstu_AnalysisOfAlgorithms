from dictonary import BruteForceDictionary, BinarySearchDictionary, SegmentSearchDictionary

bruteForceDictionary = BruteForceDictionary()
binarySearchDictionary = BinarySearchDictionary()
segmentSearchDictionary = SegmentSearchDictionary()

def convert(value):
    if value is None:
        return 'Не найдено'
    return value

key = '1'
print('bruteForceDictionary    = { }',  'word: ', key, 'value:', convert(bruteForceDictionary[key]))
print('binarySearchDictionary  = { }',  'word: ', key, 'value:', convert(binarySearchDictionary[key]))
print('segmentSearchDictionary = { }', 'word: ', key, 'value:', convert(segmentSearchDictionary[key]))
print()

bruteForceDictionary['1'] = 2
binarySearchDictionary['1'] = 2
segmentSearchDictionary['1'] = 2

key = '1'
print("bruteForceDictionary    = {'1': 2 }", 'word: ', key, 'value:', convert(bruteForceDictionary[key]))
print("binarySearchDictionary  = {'1': 2 }", 'word: ', key, 'value:', convert(binarySearchDictionary[key]))
print("segmentSearchDictionary = {'1': 2 }", 'word: ', key, 'value:', convert(segmentSearchDictionary[key]))
print()

bruteForceDictionary['2'] = 1
binarySearchDictionary['2'] = 1
segmentSearchDictionary['2'] = 1

key = '1'
print("bruteForceDictionary    = {'2':1, '1': 2 }", 'word: ', key, 'value:', convert(bruteForceDictionary[key]))
print("binarySearchDictionary  = {'2':1, '1': 2 }", 'word: ', key, 'value:', convert(binarySearchDictionary[key]))
print("segmentSearchDictionary = {'2':1, '1': 2 }", 'word: ', key, 'value:', convert(segmentSearchDictionary[key]))
print()

key = '3'
print("bruteForceDictionary    = {'2':1, '1': 2 }", 'word: ', key, 'value:', convert(bruteForceDictionary[key]))
print("binarySearchDictionary  = {'2':1, '1': 2 }", 'word: ', key, 'value:', convert(binarySearchDictionary[key]))
print("segmentSearchDictionary = {'2':1, '1': 2 }", 'word: ', key, 'value:', convert(segmentSearchDictionary[key]))
print()