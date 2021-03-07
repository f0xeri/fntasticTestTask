input_string = input().lower()
output_string = ''.join([')' if input_string.count(x) > 1 else '(' for x in input_string])
print(output_string)
