#!/usr/bin/python
#-*- coding: utf-8 -*-

import re
import sys

filename_end = re.compile('(?<=\w\.)txt$')

mots_dates = ["année", "ans", "mois", "jours", "semaines", "years", "month", "week", "date", "siècle", "century", "longtemps", "depuis", "toujours"]

blanks_between_points = re.compile('(?<=[\!\?\.]) (?=[\!\?\.])')
ending_punctuation = re.compile('[\!\?\.]+')
intermediate_punctuation = re.compile('[\(\])\]\[\,\;\:\"\'\-]+')
whites = re.compile('[\n\r\t ]+')
word_breaks = re.compile('\-[\n\r]+')

def clean_txt(txt):
    txt = word_breaks.sub('', txt)
    txt = intermediate_punctuation.sub('', txt)
    txt = whites.sub('', txt)
    txt = blanks_between_points.sub('', txt)
    return txt


def is_in(w):
	if(w == []):
		return False
	for word in mots_dates:
		if w[0].lower() == word.lower() or w[0].upper() == word.upper(): 
			return True
	return False

def filtre(content, output):
	word = ""
	sentence = []
	c = ''
	string = ""
	
	for c in content:
		if((c != ' ') and (c != '\n') and (c != '\r') and (c != '\t')):
			word += c
		else:
			sentence.append(word)
			sentence.append(c)
			word = ""

	for w in sentence:
		search_format_date = []
		search_format_date2 = []
		search_format_date3 = []
		search_format_date4 = []
		tmp_size = 0
		tmp_string = ""

		if((w != '\n') and (w != '\r')):
			string += w

		else:
			string += w
			search_format_date2 = re.findall(r"(\d{1,2} (?:January|February|March|April|May|June|July|August|September|October|November|December) \d{4})", string)
			search_format_date4 = re.findall(r"((?:January|February|March|April|May|June|July|August|September|October|November|December) \d{1,2}, \d{4})", string)

			if search_format_date2 != []:
				format_date = "<date>" + str(search_format_date2[0]) + "</date>"
				while(tmp_size <= (len(output) - (len(str(search_format_date2[0]))+2))):
					tmp_string += output[tmp_size]
					tmp_size += 1
				output = tmp_string
				output += format_date


			if search_format_date4 != []:
				tmp_size = 0
				tmp_string = ""
				format_date = "<date>" + str(search_format_date4[0]) + "</date>"
				#print((str(search_format_date4[0])))
				while(tmp_size <= (len(output) - (len(str(search_format_date4[0]))+16))):
					tmp_string += output[tmp_size]
					tmp_size += 1
				output = tmp_string
				output += format_date
			string = ""

		search_format_date = re.findall(r"[\d]{1,2}/[\d]{1,2}/[\d]{4}", w)
		#search_format_date = re.findall(r"([\d]{1,2} 0[1-9]|1[0-9]|2[0-9]|3[0-1])(.|-|/)[\d]{1,2}(0[1-9]|1[0-2])(.|-|/)[\d]{4}1[0-9][0-9][0-9][0-9]|2[0-9][0-9][0-9]",w)
		search_format_date3 = re.findall('[\d]{1,2}-[\d]{1,2}-[\d]{2}', w)
		search_format_date5 = re.findall(r"[\d]{1,2}/[\d]{1,2}/[\d]{4}", w)

		if search_format_date != []:
			format_date = "<date>" + str(search_format_date[0]) + "</date>"
			output += format_date

		elif search_format_date3 != []:
			format_date = "<date>" + str(search_format_date3[0]) + "</date>"
			output += format_date


		elif is_in(filter(None, ending_punctuation.split(clean_txt(w)))):
			format_date = "<date>" + w + "</date>"
			output += format_date

		else :
			output += w

	return output

with open(sys.argv[1], 'r', 0) as original_file:
		content = original_file.read()

output = '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>\n\n'

output = filtre(content, output)

with open(filename_end.sub('xml', sys.argv[1]), 'w', 0) as final_file:
		final_file.write(output)

