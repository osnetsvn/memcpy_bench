#This python code takes "exec_time" as argument and convert it into csv format. 



import csv
def convert(string):
        list_var=list(string.split("\t"))
        return list_var

def convert_string_float(str_list):
        float_list=[]
        #float_list.append(int(str_list[0]))
        for i in str_list:
            float_list.append(float(i))
        return float_list


file_name=input("Enter the trace's file name:")
f=open(file_name,"r")
output=open('final_output.csv', 'a+')
final_list=[]
while True:
    content=f.readline()
    if not content:
        break
    values=convert(content)
    values.pop()
    print convert_string_float(values)
    final_list.append( convert_string_float(values))
with output:
    write=csv.writer(output)
    write.writerows(final_list)

