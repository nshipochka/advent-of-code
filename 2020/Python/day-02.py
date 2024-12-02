lines = []
with open("day-02.txt") as file:
    lines = [line.strip() for line in file]

def is_valid_password_1(line):
    tokens = line.split(' ')
    
    min = int(tokens[0].split('-')[0])
    max = int(tokens[0].split('-')[1])
    character = tokens[1].strip(':')
    password = tokens[2]
    
    if min <= password.count(character) <= max:
        return True
    
    return False

def is_valid_password_2(line):
    tokens = line.split(' ')
    
    i = int(tokens[0].split('-')[0]) - 1
    j = int(tokens[0].split('-')[1]) - 1
    character = tokens[1].strip(':')
    password = tokens[2]

    return (password[i] == character) ^ (password[j] == character)

print(sum(map(is_valid_password_1, lines)))
print(sum(map(is_valid_password_2, lines)))



