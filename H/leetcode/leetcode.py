class Solution:
    def romanToInt(self, s: str) -> int:
        dict = {
            "I": 1,
            "V": 5,
            "X": 10,
            "L": 50,
            "C": 100,
            "D": 500,
            "M": 1000
        }
        
        #LVIII = 58
        #54

        value = 0
        buffer = "I"
        for roman in s:
            if (dict[roman] > dict[buffer]):
                value -= dict[buffer]
                calc = dict[roman] - dict[buffer]
                value += calc
            else:

                temp = dict[roman]
                value += temp
                buffer = roman

        return value
           
               
        
    