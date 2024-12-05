import itertools

def binary_search(lower_bound, upper_bound, directions, first_half, second_half):
    for d in directions:
        mid = (upper_bound + lower_bound) // 2  # integer division
        if d == first_half:
            upper_bound = mid  
        elif d == second_half:
            lower_bound = mid + 1 

    return lower_bound

def find_row(row_info):
    return binary_search(0, 127, row_info, 'F', 'B')    

def find_seat(seat_info):
    return binary_search(0, 7, seat_info, 'L', 'R')

def get_seat_id(row, seat):
    return row * 8 + seat

def find_pass(boarding_passes, combinations):
    for i in range(len(combinations) - 2):
        prev = combinations[i]
        curr = combinations[i + 1]
        next = combinations[i + 2]
        if prev in boarding_passes and curr not in boarding_passes and next in boarding_passes:
            return curr 

data = open("day-05.txt").read().strip().split("\n")

# Part 1
print(max([get_seat_id(find_row(d[0:7]), find_seat(d[7:])) for d in data]))

# Part 2
boarding_passes = [tuple((find_row(d[0:7]), find_seat(d[7:]))) for d in data]
print(boarding_passes)

# Generate all possible rows and seats
rows = range(128)  # Rows 0 to 127
seats = range(8)   # Seats 0 to 7

# Create all combinations of row and seat
combinations = list(itertools.product(rows, seats))

bp = find_pass(boarding_passes, combinations)
print(get_seat_id(bp[0], bp[1]))


