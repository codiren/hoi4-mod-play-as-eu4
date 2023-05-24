import csv

def replace_false_with_true(definition_file, coaltals_file):
    with open(definition_file, 'r') as csvfile:
        definitions = list(csv.reader(csvfile, delimiter=';'))
    
    with open(coaltals_file, 'r') as coaltals:
        coaltals_content = coaltals.read()
    
    for definition in definitions:
        first_number = definition[0]
        if first_number in coaltals_content:
            definition[5] = 'true'
    
    with open(definition_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=';')
        writer.writerows(definitions)

# Provide the file paths for definition.csv and coaltals.txt
replace_false_with_true('definition.csv', 'coaltals.txt')
