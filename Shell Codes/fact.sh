echo "Enter a number"
read num
fact=1
i=1
if [ $num != 0 ]
then
    while [ $i -le $num ]
    do
      fact=$(($fact*$i))
      i=$(($i+1))
    done
    echo "Factorial of $num is: $fact"    
else
    echo "Factorial of 0 is: 0"
fi

echo "Enter a number"
read n
for i in 1 2 3 4 5 6 7 8 9 10
#for i in {1..10..1}
#for (( i=0; i<=10; i++ ))
do
echo "$n * $i = $((n*i))"
i=$((i+1))
done
