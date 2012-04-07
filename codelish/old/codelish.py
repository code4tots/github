#!/usr/bin/python

# --> Model.
class Model:
    def __init__(self):
        pass
    
    # static methods
    @staticmethod
    def breakTextIntoSentences(text):
        def textBeginsWith(text,s):
            return len(text) >= len(s) and text[:len(s)]==s
            
        def f(text,sentencesSoFar=[], currentSentence=''):
            if text=='':
                return sentencesSoFar
            elif textBeginsWith(text,'.'):
                sentencesSoFar.append(currentSentence)
                return f(text[1:],sentencesSoFar,'')
            elif textBeginsWith(text,"\nBegin Literal Block\n"):
                VAR = {}
                VAR['cutoutindex'] = None
                for i in range(len(text)):
                    if textBeginsWith(text[i:],"\nEnd Literal Block\n"):
                        VAR['cutoutindex'] = i+len("\nEnd Literal Block\n")
                        break
                return f(text[VAR['cutoutindex']:],sentencesSoFar,currentSentence+text[:VAR['cutoutindex']])
            else:
                return f(text[1:],sentencesSoFar,currentSentence+text[0])
        
        return f(text)
        
    @staticmethod
    def breakSentenceIntoTokens(sentence):
        pass
    
    @staticmethod
    def unify(call, signature):
        ret = None
        if len(call) != len(signature):
            ret = None
        else:
            length = len(call)
            ret = {}
            for i in range(length):
                if signature[i][0] == '@':
                    if ret != None:
                        ret[signature[i][1:]] = call[i]
                elif signature[i] != call[i]:
                    ret = None
        return ret

#print(Model.breakTextIntoSentences(''))

m = Model.breakTextIntoSentences("Hello World. Another sentence. Yet another sentence. This one has \nBegin Literal Block\n A LITERAL BLOCK...\nEnd Literal Block\n some weird literal block.")
for x in m:
    print(x)
#print(Model.unify(['hey','world'],['hey','@whatToSay']))