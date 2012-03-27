#!/usr/bin/python
#
# codelish.py
#

# Load entire program text in one piece.
def loadFullTextFromFilename(filename):
    return open(filename,'r').read()

# Break up text into words, by whitespace.
def splitTextIntoWords(text):
    return text.split()
    
# Then parse words into sentences.
def groupWordsIntoSentences(words):
    ret = []
    currentSentence = []
    currentPosition = 0
    
    while currentPosition < len(words):
        word = words[currentPosition]
        
        # Handle possibility of comment
        if word[0] == '[':
            while words[currentPosition][-1] != ']' and currentPosition < len(words):
                currentPosition += 1
            currentPosition += 1
        # Othwerise, add to currentSentence
        else:
            # Before adding word, check to see if it is the end of a sentence.
            if word[-1] == '.':
                word = word[:-1]
                if word != '':
                    currentSentence.append(word)
                ret.append(currentSentence)
                currentSentence = []
            # If it's not the end of a sentence, it's safe to just add it.
            else:
                currentSentence.append(word)
                
            currentPosition += 1
    # Any trailing words without periods are lost.
    return ret

# Now execute the parsed program.
def executeProgram(sentences):
    that = 0
    
    variableStack = [ ['that', that] ]
    locationStack = [ ['beginning', 0] ]
    currentPosition = 0
    
    # Process marked locations.
    for position in range(len(sentences)):
        if ' '.join(sentences[position][0:3]) == "Mark location as":
            locationStack.append([sentences[position][3],position])\
    
    def findValueFromKey(key):
        try:
            return int(key)
        except:
            pass
            
        for pair in reversed(variableStack):
            if pair[0] == key:
                return pair[1]
        print("%s: undeclared variable\n" % key)
    def findPairFromKey(key):
        for pair in reversed(variableStack):
            if pair[0] == key:
                return pair
        print("%s: undeclared variable\n" % key)
    def findLocationFromName(name):
        for pair in reversed(locationStack):
            if pair[0] == name:
                return pair[1]
        print("%s: unknown location\n" % name)
    
    running = True
    while running and currentPosition < len(sentences):
        sentence = sentences[currentPosition]
        # print( "sentence: %s" % ' '.join(sentence)+'.')
        
        if sentence[0] == "Declare" and sentence[2] == "to":
            variableStack.append( [sentence[1], int(sentence[3])] )
            currentPosition += 1
        elif sentence[0] == "Set" and sentence[2] == "to":
            pair = findPairFromKey(sentence[1])
            pair[1] = findValueFromKey(sentence[3])
            currentPosition += 1
        elif sentence[0] == "Add" and sentence[2] == "and":
            x = findValueFromKey(sentence[1])
            y = findValueFromKey(sentence[3])
            findPairFromKey('that')[1] = x + y
            currentPosition += 1
        elif sentence[0] == "Multiply" and sentence[2] == "and":
            x = findValueFromKey(sentence[1])
            y = findValueFromKey(sentence[3])
            findPairFromKey('that')[1] = x * y
            currentPosition += 1
        elif sentence[0] == "Print":
            print( findValueFromKey(sentence[1]) )
            currentPosition += 1
        elif sentence[0] == "Announce":
            print( ("%s = " % sentence[1]) + str(findValueFromKey(sentence[1])) )
            currentPosition += 1
        elif ' '.join(sentence[0:3]) == "Mark location as":
            # Marked locations should have been processed before beginning execution loop.
            currentPosition += 1
        elif sentence[0] == "If" and ' '.join(sentence[2:5]) == "is less than" and ' '.join(sentence[6:8]) == "then goto":
            # sentence[5] may end with a comma.
            if sentence[5][-1] == ',':
                sentence[5] = sentence[5][:-1]
            if findValueFromKey(sentence[1]) < findValueFromKey(sentence[5]):
                currentPosition = findLocationFromName(sentence[8])
            else:
                currentPosition += 1
        elif sentence[0] == "If" and sentence[2] == "is" and ' '.join(sentence[4:6]) == "then goto":
            # sentence[3] may end with a comma.
            if sentence[3][-1] == ',':
                sentence[3] = sentence[3][:-1]
            if findValueFromKey(sentence[1]) == findValueFromKey(sentence[3]):
                currentPosition = findLocationFromName(sentence[6])
            else:
                currentPosition += 1
        elif sentence[0] == "Finish":
            running = False
            currentPosition = len(sentences)
        else:
            print( "Unknown command: %s" % (' '.join(sentence))+'.' )
            currentPosition += 1
    
executeProgram(groupWordsIntoSentences(splitTextIntoWords(loadFullTextFromFilename("prog.lish"))))