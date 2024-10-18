## Usage:
To print out mispelled words along with statistics  
`./speller dictionaries/large {path_to_text_file}.txt`

## Examples:
- Spell check texts/shakespeare.txt  
`./speller dictionaries/large texts/shakespeare.txt`


- Spell check texts/frankenstein.txt  
`./speller dictionaries/large texts/frankenstein.txt`

## Example Output:  
```  
misspelled_word_1
misspelled_word_2
misspelled_word_3

WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.06
TIME IN check:        0.03
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.10
```
