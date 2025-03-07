# Program should read input characters one by one and update its current state as specified by the DFA M
# Once the input string has been read completely the program should check the current state and report "accept" or "reject"
# You should implement the transition function and then use it in a loop. In each iteration one character will be read and transition function will be called to update the current state.
# Demonstrate that your program works by running it on some test cases. Include accept and reject cases and don't forget edge cases (like empty input)
class automaton:
    def __init__(self, first_name, last_name):
        self.first_name = first_name
        self.last_name = last_name
        self.first_name_len = len(first_name)
        self.last_name_len = len(last_name)
        self.start_state = 0
        self.current_state = self.start_state
        self.num_of_states = (self.first_name_len + self.last_name_len)
        self.first_name_accepted = False
        self.last_name_accepted = False

        
    def parse(self, test_string):
        # For each letter in test string
        if test_string == "":
            return "REJECTED"
        for letters in test_string:
            # Send each letter to transition function
            result = self.transition(letters)
            
        self.start_state = 0
        self.current_state = 0
        self.first_name_accepted = False
        self.last_name_accepted = False
        return result

    def transition(self, letter):
        # transition function compares letter of the test_string to first name first
        # compare first name with letters
        if (self.first_name_accepted == False) and (self.current_state < self.first_name_len):
            if (letter == self.first_name[self.current_state]):
                self.current_state += 1
                
                # if first name is found then we move onto the last name
                if (self.current_state) == self.first_name_len:
                    
                    self.first_name_accepted = True
                    self.start_state = self.first_name_len + 1
                    self.current_state += 1  
                
        # if first name is found compare letters and last name
        elif (self.first_name_accepted == True) and (self.current_state < self.num_of_states):
            
            if ((letter == self.last_name[self.current_state - self.first_name_len - 1]) and (self.last_name_accepted == False)):
                self.current_state += 1
                
                # if last name is found then we update last name flag
                if (self.current_state + 1) == self.last_name_len:
                    self.last_name_accepted = True

        # go back to start if we don't find the first name
        else:
            self.current_state == self.start_state
            
        if self.current_state == self.num_of_states:
            return "ACCEPTED"
        else:
            return "REJECTED"
           
        
def main():

   auto = automaton("samuel", "lara") 
   
   test_cases = [
    "xed samuel dex lara dfef",  #  ACCEPTED 
    "samuel xyz lara",           #  ACCEPTED 
    "samuellara",                #  ACCEPTED 
    "xxsamuelxxlara",            #  ACCEPTED 
    "samuel yyy lara",           #  ACCEPTED 
    "xxsamuelyyylaraxx",         #  ACCEPTED 
    "samuel samuel lara lara",   #  ACCEPTED 
    "samuell larax",             #  ACCEPTED 
    "abcdesamuellaraxyz",        #  ACCEPTED 
    
    "lara samuel",               #  REJECTED (wrong order)
    "samuel",                    #  REJECTED (missing last name)
    "lara",                      #  REJECTED (missing first name)
    "",                          #  REJECTED (empty input)
    "samuella",                  #  REJECTED (last name not fully matched)
    "samue lara",                #  REJECTED (first name is incomplete)
    ]


   for tests in test_cases:
       result = auto.parse(tests)
       print(f"{tests:<30} {result:<10}")
       

if __name__ == "__main__":
    main()
