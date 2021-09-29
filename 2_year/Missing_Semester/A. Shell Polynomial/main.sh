mod=1000000007
# file='input.txt'  
#while read "input.txt" line; do  
	#Reading each line 
sum=0
# x=$(head -n 1 input.txt)
# echo $x
k=1
i=1  
for line in $(cat input.txt)
do
	if [[ $i -eq 1 ]]; then
		x=$line
	else 
		sum=$(((sum+line*k%mod)%mod))
		k=$((k*x%mod))
	fi
	#echo "Line No. $i : $line"  
	i=$((i+1))  
done
#echo $x
echo $sum >output.txt
