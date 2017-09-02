
import inflect

def word_to_digits(word):
    
p = inflect.engine()

#numbers = [1, 3, 6, 10, 14, 13]
numbers = [12, 10, 9]

for number in numbers:
    print("%d: %s" % (number, sum(word_to_digits(p.number_to_words(number))) % 26))