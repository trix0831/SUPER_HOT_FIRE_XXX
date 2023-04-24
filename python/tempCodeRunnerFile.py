def hexTOstr(num):
    tmpStr = [0]*8
    numtmp = 0
    
    for i in range(7, -1, -1):
        if num % 16 < 10:
            tmpStr[i] = str(int(num%16))
        elif num % 16 == 10:
            tmpStr[i] = "A"
        elif num % 16 == 11:
            tmpStr[i] = "B"
        elif num % 16 == 12:
            tmpStr[i] = "C"
        elif num % 16 == 13:
            tmpStr[i] = "D"
        elif num % 16 == 14:
            tmpStr[i] = "E"
        elif num % 16 == 15:
            tmpStr[i] = "F"
        
        print(tmpStr[i])
            
        num -= num%16
        num /= 16

    return tmpStr[0] + tmpStr[1] + tmpStr[2] + tmpStr[3] + tmpStr[4] + tmpStr[5] + tmpStr[6] + tmpStr[7]

print(hexTOstr(0x50335F7E))