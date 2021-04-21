###
import csv
import json
careerPathFile = open('output3.csv')
careerPathReader = csv.reader(careerPathFile)
careerPathData = list(careerPathReader)
careerPathData
careerJsonData = json.dumps(careerPathData)

careerPathFile.close()
###

#import pandas as pd
#df = pd.read_csv (r'D:\University\UF\CEN 3031\Final Project\db\pyCFConnect\output3.csv', encoding='cp1252')
#df.to_json (r'D:\University\UF\CEN 3031\Final Project\db\pyCFConnect\output.json')

careerPathFile = open('output3.csv')
careerPathReader = csv.reader(careerPathFile)
file = open('out.json','w') 
file.write('{')
file.write('"entries": [')
for row in careerPathReader:
    file.write('{')
    file.write('"name": ')
    file.write('"')
    file.write(careerPathData[careerPathReader.line_num - 1][1])
    file.write('"')
    file.write(',')

    file.write('"type": ')
    file.write('"')
    file.write(careerPathData[careerPathReader.line_num - 1][0])
    file.write('"')
    file.write(',')

    file.write('"description": ')
    file.write('"')
    file.write(careerPathData[careerPathReader.line_num - 1][8])
    file.write('"')
    file.write(',')

    file.write('"keywords": ')
    file.write('[')
    file.write(']')
    file.write(',')

    file.write('"salary_ranges": ')
    file.write('{')
    file.write('"entry": ')
    file.write(careerPathData[careerPathReader.line_num - 1][3])
    file.write(',')
    file.write('"median": ')
    file.write(careerPathData[careerPathReader.line_num - 1][6])
    file.write(',')
    file.write('"mean": ')
    file.write(careerPathData[careerPathReader.line_num - 1][4])

    file.write('}')
    file.write(',')

    file.write('"growth_rate": ')
    file.write('"')
    file.write(careerPathData[careerPathReader.line_num - 1][5])
    file.write('%')
    file.write('"')
    file.write(',')

    file.write('"education": ')
    file.write('"')
    file.write(careerPathData[careerPathReader.line_num - 1][7])
    file.write('"')
    file.write(',')

    file.write('"important_subjects": ')
    file.write('[')
    file.write(']')

    file.write('}')
    file.write(',')

file.write(']')
file.write('}')
 
file.close()
careerPathFile.close()