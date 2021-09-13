

#### PART 1 ####
#consts:#
ID_LEN=8
ID_INDEX=0
NAME_INDEX=1
SEMESTER_INDEX=2
HOMEWORK_AVG=3
AVERAGE_DIVIDE=2
DISTANCE_TWO_DIGITS_FROM_ID_END=6
MAX_HOMEWORK_AVG=100
MIN_HOMEWORK_AVG=51


#helper functions:#

#check if an id is legal and return truth value accordingly
def check_id(id: int) ->bool :
    string_id=str(id)
    length=len(string_id)
    if length!= ID_LEN:
        return False
    if string_id[0]==0:
        return False
    return True

#check if a name is legal and return truth value accordingly
def check_name(name: str) ->bool :
    if all(letter.isalpha() or letter.isspace() for letter in name):
       return True
    return False

#check the validity of a line's elements and return truth value accordingly
def check_input_legality(id :int, name: str, semester :int, homework_avg : int) -> bool:
    if check_id(id)==False:
        return False
    if check_name(name) == False :
        return False
    if semester < 1 :
        return False
    if homework_avg < MIN_HOMEWORK_AVG or homework_avg > MAX_HOMEWORK_AVG :
        return False
    return True

#return a new list without duplicated elements with same id,
#while the new including the last duplicate of each element
def create_list_without_duplicates_of_element(list: list) ->list: 
    list.reverse()
    new_list=[]
    for item in list:
        for elem in new_list:
            if elem[ID_INDEX]==item[ID_INDEX]:
                continue
        new_list.append(item)
    return new_list

#define the key in order to sort a list by id
def take_id(element: int):
    return element[ID_INDEX]


#### PART 1 ####
# final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
# rows from the input file) into the file in `output_path`. Returns the average of the grades.
#   input_path: Path to the file that contains the input
#   output_path: Path to the file that will contain the output
def final_grade(input_path: str, output_path: str) -> int:
    input_file=open(input_path,'r')  
    input_list=[]
    for line in input_file:
        input_list.append(line.rstrip('\n').split(','))                             
    legal_list=[]  #will contain legal lines, may have duplicates
    for elem in input_list:
        if check_input_legality(int(elem[ID_INDEX]),elem[NAME_INDEX],int(elem[SEMESTER_INDEX]),int(elem[HOMEWORK_AVG])) == True:
            legal_list.append(elem) 
    list_without_duplicates=create_list_without_duplicates_of_element(legal_list)
    list_without_duplicates.sort(key=take_id)
    input_file.close()
    output_file=open(output_path, 'w')
    number_of_student = 0
    sum_of_grades = 0
    for elem in list_without_duplicates :
        id="".join(str(elem[ID_INDEX]).split())
        homework_avg="".join(str(elem[HOMEWORK_AVG]).split())
        final_digits=(elem[ID_INDEX])[DISTANCE_TWO_DIGITS_FROM_ID_END : ID_LEN]  
        final_grade= (int(final_digits) + int(homework_avg))//AVERAGE_DIVIDE
        sum_of_grades += final_grade
        number_of_student+=1
        output_file.write(id + ", " + homework_avg + ", " + str(final_grade) + "\n")
    output_file.close()
    if number_of_student!=0:
        return sum_of_grades//number_of_student
    return 0
    

#### PART 2 ####

#const:#
ABC=ord('z')-ord('a')+1
LOWER_LETTER=ord('a')


#### PART 2 ####
# check_strings: Checks if `s1` can be constructed from `s2`'s characters.
#   s1: The string that we want to check if it can be constructed
#   s2: The string that we want to construct s1 from
def check_strings(s1: str, s2: str) -> bool:
    s2_lower_case=s2.lower()
    s1_lower_case=s1.lower()
    histo_s2_lower_case = [0] * (ABC) #will not hold the correct histogram after the check
    for letter in s2_lower_case:
        histo_s2_lower_case[ord(letter) - LOWER_LETTER]+=1
    for letter in s1_lower_case:
        if histo_s2_lower_case[ord(letter)-LOWER_LETTER]<=0:
            return False
        histo_s2_lower_case[ord(letter)-LOWER_LETTER]-=1
    return True
    
