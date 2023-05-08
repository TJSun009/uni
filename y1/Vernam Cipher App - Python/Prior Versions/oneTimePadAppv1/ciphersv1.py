def decToBin(decimal):
    if decimal in range(0,256):
        power = 7
        num = ''
        while power >= 0:
            if decimal >= pow(2,power):
                decimal -=pow(2,power)
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

def one_time_pad(string, mode, padCode):
    import random
    binary = strToBin(string)
    pad = ''
    ciphertext = ''
    plaintext = ''
    
    
    if mode.lower() == 'e':
        i = 0
    
        while i < len(binary):
            digit = random.randint(0,1)
            pad += str(digit)

            if digit ^ int(binary[i]) == True:
                ciphertext += '1'
            else:
                ciphertext += '0'

            i+=1

        padCode = binToStr(pad)    
        ciphertext = binToStr(ciphertext)
        return ciphertext, padCode
    
    elif mode.lower() == 'd':
        i = 0
        
        pad = strToBin('{}'.format(padCode))

        while i < len(pad-1):
            if (int(binary[i]) ^ int(pad[i])) == True:
                plaintext += '1'
            else:
                plaintext += '0'
                
            i+=1
    
        plaintext = binToStr(plaintext)
        return plaintext
    else:
        return "Error, setup mode"
        
    




