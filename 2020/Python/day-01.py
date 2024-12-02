def two_sum(xs, sum):
    num_dict = {}
    for index, x in enumerate(xs):
        complement = sum - x
        if complement in num_dict:
            return [num_dict[complement], index]
        
        num_dict[x] = index
    
    return []

def three_sum(xs, sum):
    n = len(xs)
    xs.sort()
    for i in range(n - 2):
        l = i + 1
        r = n - 1

        while(l < r):
            curr_sum = xs[i] + xs[l] + xs[r]
            if curr_sum == sum:
                return [i, l, r]
            elif curr_sum < sum:
                l += 1
            else:
                r -= 1
    return []          

lines = []
with open("day-01.txt") as file:
    lines = [line.strip() for line in file]

numbers = [int(line.strip()) for line in lines]

two_sum_indices = two_sum(numbers, 2020)
print(numbers[two_sum_indices[0]] * numbers[two_sum_indices[1]])

three_sum_indices = three_sum(numbers, 2020)
print(numbers[three_sum_indices[0]] * numbers[three_sum_indices[1]] * numbers[three_sum_indices[2]])