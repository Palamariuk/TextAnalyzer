def load_words():
    with open('words.txt') as word_file:
        valid_words = set(word_file.read().split())

    return sorted(valid_words)


if __name__ == '__main__':
    english_words = load_words()
    with open('proper_names.txt', 'w') as proper_names:
    	for word in english_words:
    		if (word.capitalize() == word) and (word.isalpha()): 
    			proper_names.write(word+"\n") 
    
