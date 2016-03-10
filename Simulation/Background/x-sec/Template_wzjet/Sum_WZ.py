# Program to find a summation of xsec of WZ+jet processes

import numpy as np 

def format_e(n):
    a = '%E' % n
    return a.split('E')[0].rstrip('0').rstrip('.') + 'E' + a.split('E')[1]



ins = open( "X-sec_wzjet_Diff_numb.txt", "r" )
data = []
for line in ins:
    number_strings = line.split() # Split the line on runs of whitespace
    numbers = [float(n) for n in number_strings] # Convert to integers
    data.append(numbers) # Add the "row" to your list.
sum_data = np.sum(data,axis=1)*1e9
sum_resh = np.reshape(sum_data,(-1,3)) 

print sum_resh

output_file =open('X-sec_wzjet_Diff_Used.txt','w')

#for i in range(0,16):
output_file.write(str(sum_resh)+"\n") 


ins.close()
output_file.close()
