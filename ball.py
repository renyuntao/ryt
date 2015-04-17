#2015-4-17
#!/usr/bin/python
import math

g=10.0
h=input("Please input the height:")
t=input("Please input the time you want to calculate:")
h=float(h)
t=float(t)
t_half=math.sqrt(2*h/g)
T=2*t_half
t=t%T

if t>t_half:
	t=T-t
	h_temp=0.5*g*t*t
	result=h-h_temp
else:
	h_temp=0.5*g*t*t
	result=h-h_temp
result=str(result)
print("Result:"+result)
