#Author:ryt
#!/usr/bin/python

print("*****This is sum program,please input two digit*****")
a=input("input first digit:")
a=str(a)
while not a.isdigit():
	print("The input is not invalid!Please input a digit")
	a=input("input first digit:")
a=int(a)
b=input("input second digit:")
b=str(b)
while not b.isdigit():
	print("The input is not invalid!Please input a digit")
	b=input("input the second digit:")
b=int(b)
print("result:%f"%(a+b))
exit(0)
