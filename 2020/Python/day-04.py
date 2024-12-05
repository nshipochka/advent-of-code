import re

def is_valid_document(fields):
    required_prefixes = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}
    present_keys = {item.split(':')[0] for item in fields}
    
    return required_prefixes.issubset(present_keys)       
        
def is_valid_document_strong(fields):
    present_fields = {item.split(':')[0]: item.split(':')[1] for item in fields}

    required_fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}
    if not required_fields.issubset(present_fields.keys()):
        return False

    byr = present_fields["byr"]
    if not (byr.isdigit() and 1920 <= int(byr) <= 2002):
        return False

    iyr = present_fields["iyr"]
    if not (iyr.isdigit() and 2010 <= int(iyr) <= 2020):
        return False

    eyr = present_fields["eyr"]
    if not (eyr.isdigit() and 2020 <= int(eyr) <= 2030):
        return False

    hgt = present_fields["hgt"]
    if hgt.endswith("cm"):
        height = hgt[:-2]
        if not (height.isdigit() and 150 <= int(height) <= 193):
            return False
    elif hgt.endswith("in"):
        height = hgt[:-2]
        if not (height.isdigit() and 59 <= int(height) <= 76):
            return False
    else:
        return False


    hcl = present_fields["hcl"]
    if not re.fullmatch(r"#[0-9a-f]{6}", hcl):
        return False


    ecl = present_fields["ecl"]
    if ecl not in {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}:
        return False


    pid = present_fields["pid"]
    if not re.fullmatch(r"\d{9}", pid):
        return False

    return True



# def extract_documents(filename):
#     documents = []
#     with open(filename, 'r') as file:
#         current_document = []
#         for line in file:
#             stripped = line.strip()
#             if stripped:
#                 current_document.extend(line.split())
#             else:
#                 current_document.sort()
#                 documents.append(current_document[:])
#                 current_document.clear()

#     if current_document:
#             documents.append(current_document[:])

#     return documents
                

# data = extract_documents("day-04.txt")

# this does the same job
data = open("day-04.txt").read().strip().split("\n\n")
data = [record.split() for record in data]

print(sum(map(is_valid_document, data)))
print(sum(map(is_valid_document_strong, data)))

