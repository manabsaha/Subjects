
echo "Enter a number"
read num
i=2
prime=1
while [ $i -le $((num/2)) ]
do
if [ $((num%i)) -eq 0 ]
then
prime=0
break
fi
i=$((i+1))
done
if [ $prime -eq 0 ]
then
echo "Non prime"
else
echo "Prime"
fi
