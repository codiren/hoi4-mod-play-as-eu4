def replace_values(source_file, target_file):
    # Read the source file and create a dictionary
    replacements = {}
    with open(source_file, 'r') as source:
        for line in source:
            left, right = line.strip().split(' ')
            replacements[left] = right

    # Read the target file and perform replacements
    modified_lines = []
    with open(target_file, 'r') as target:
        for line in target:
            for left, right in replacements.items():
                line = line.replace(left, right)
            modified_lines.append(line)

    # Write the modified contents back to the target file
    with open(target_file, 'w') as target:
        target.writelines(modified_lines)

# Example usage
source_file = 'realreal.txt'  # Replace with the path to your source file
target_file = 'countries_l_english.yml'  # Replace with the path to your target file
replace_values(source_file, target_file)
