#!/usr/bin/python
# codelish.py
# 3.26.2012
def loadAndParseProgramFromFilename(filename):
    def loadFromFilename(filename):
        return open(filename,'r').read()
    def splitTextIntoWords(text, soFar=[]):
        # split recursively
        if text == '':
            return soFar
        elif text[0] == '[':
            match = 1
            while text[match] != ']':
                match += 1
            return splitTextIntoWords(text[match+1:],soFar)
        elif text[0] == "'":
            match = 1
            while text[match] != "'":
                match += 1
            soFar.append(text[:match])
            return splitTextIntoWords(text[match+1:],soFar)
        elif text[0].isspace():
            return splitTextIntoWords(text[1:],soFar)
        else: # elif text[0].isalnum():
            match = 1
            while text[match] != "'" and text[match] != '[' and (not text[match].isspace()):
                match += 1
            soFar.append(text[:match])
            return splitTextIntoWords(text[match:],soFar)
    def groupWordsIntoSentences(words):
        sentences = []
        currentSentence = []
        index = 0
        while index < len(words):
            word = words[index]
            if word[-1] == '.':
                word = word[:-1]
                if (word != ''):
                    currentSentence.append(word)
                sentences.append(currentSentence)
                currentSentence = []
            else:
                currentSentence.append(word)
            index += 1
        return sentences
    return groupWordsIntoSentences(splitTextIntoWords(loadFromFilename(filename)))
    
def executeParsedProgram(sentences):
    thatPair = ['that', 0]
    variableStack = [ thatPair ]
    locationStack = [ ['beginning', 0] ]
    currentPosition = 0
    
    # calculate locationStack.
    for position in range(len(sentences)):
        if len(sentences[position]) == 4 and ' '.join(sentences[position][0:3]) == 'Mark location as':
            locationStack.append([sentences[position][3],position])
    
    # convenience methods for variable lookup.
    def findValueFromToken(token):
        try:
            return int(token)
        except:
            for pair in reversed(variableStack):
                if pair[0] == token:
                    return pair[1]
    def findPairFromToken(token):
        for pair in reversed(variableStack):
            if pair[0] == token:
                return pair
    
    while currentPosition < len(sentences):
        sentence = sentences[currentPosition]
        # --- Variable initialization/assignment ---
        if len(sentence) == 4 and sentence[0] == 'Initialize' and sentence[2] == 'to':
            variableStack.append([sentence[1],int(sentence[3])])
            currentPosition += 1
        elif len(sentence) == 4 and sentence[0] == 'Set' and sentence[2] == 'to':
            findPairFromToken(sentence[1])[1] = findValueFromToken(sentence[3])
            currentPosition += 1
            
        # --- IO ---
        elif len(sentence) == 2 and sentence[0] == 'Announce':
            print(findValueFromToken(sentence[1]))
            currentPosition += 1
            
        # --- Arithmetic ---
        elif len(sentence) == 4 and sentence[0] == 'Add' and sentence[2] == 'and':
            thatPair[1] = findValueFromToken(sentence[1]) + findValueFromToken(sentence[3])
            currentPosition += 1
            
        # --- Conditionals, and branching ---
        elif len(sentence) == 9 and sentence[0] == 'If' and ' '.join(sentence[2:5]) == 'is less than' and ' '.join(sentence[6:8]) == 'then goto':
            # sentence[5] may end with a comma.
            if sentence[5][-1] == ',':
                sentence[5] = sentence[5][-1]
            if findValueFromToken(sentence[1]) < findValueFromToken(sentence[5]):
                currentPosition = sentence[8]
            else:
                currentPosition += 1
        elif len(sentence) == 4 and ' '.join(sentence[:3]) == 'Mark location as':
            # marking locations should have been processed before the main execution loop.
            currentPosition += 1
            
        # --- Unknown commands ---
        else:
            print("Unknown comamnd: %s" % ' '.join(sentence)+'.')
            currentPosition += 1
    
def main():
    from sys import argv
    if len(argv) < 2:
        print ("usage: %s [filename]" % argv[0])
    else:
        executeParsedProgram(loadAndParseProgramFromFilename(argv[1]))
    
if __name__ == '__main__':
    main()