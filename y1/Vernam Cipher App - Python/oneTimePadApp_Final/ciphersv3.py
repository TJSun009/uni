def decToBin(decimal):
    num = ''
    power = 7
    while power >= 0:
        if decimal >= pow(2, power):
            decimal -= pow(2, power)
            num += '1'
        else:
            num +='0'
        power -= 1
    return num

#Task 12

def strToBin(string):
    binary = ''
    
    for i in string:
        charNum = ord(i)
        binary += decToBin(charNum)
    return binary

#Task 13

def binToStr(binary):
    string = ''
    char = ''
    i = 0
    while i < len(binary):
        while len(char) < 8:
            char += binary[i]
            i+=1
        charNum = int(char, 2)
        string += chr(charNum)
        char = ''
    return string

import random

class one_time_pad:

    def __init__(self, plaintext, ciphertext = "", pad = ""):

        self.plaintext = plaintext
        self.ciphertext = ciphertext
        self.pad = pad
                
    def encrypt(self):
        binPlaintext = strToBin(self.plaintext)

        #generating a pad
        for digit in binPlaintext: 
            self.pad += str(random.randint(0,1))

        i = 0
        for digit in binPlaintext:   
            if (int(self.pad[i]) ^ int(digit)) == True:
                self.ciphertext += '1'
            else:
                self.ciphertext += '0'

            i+=1

            

        self.pad = binToStr(self.pad)    
        self.ciphertext = binToStr(self.ciphertext)
        
        return self.ciphertext, self.pad
    
    def decrypt(self):
        j = 0
        
        self.ciphertext = strToBin(self.ciphertext)
        self.pad = strToBin(self.pad)

        try:
            for digit in self.pad:
                if (int(digit) ^ int(self.ciphertext[j])) == True:
                    self.plaintext += '1'
                else:
                    self.plaintext += '0'
                    
                j+=1
        except:
            return "Error: The pad and ciphertext must be the same length"
    
        self.plaintext = binToStr(self.plaintext)
        return self.plaintext
