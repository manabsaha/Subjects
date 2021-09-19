echo "Hello World"
echo "Input two numbers:"
read a
read b

sum=$(($a+$b))
diff=$(($a-$b))
prod=$(($a*$b))

#conditional if-elif-else
if [ $b -eq 0 ]
then
    mod="undefined"
    quo="undefined"
else
    quo=$(($a/$b)) 
    mod=$(($a%$b))
fi

echo "The sum of $a and $b is: $sum"
echo "The difference of $a and $b is: $diff"
echo "The product of $a and $b is: $prod"
echo "The quotient of $a and $b is: $quo"
echo "The remainder of $a and $b is: $mod"

#for loop
for i in hello 1 2 goodbye 
do
  echo "Looping ... i is set to $i"
done

#while loop
INPUT_STRING=hello
while [ "$INPUT_STRING" != "bye" ]
do
  echo "Please type something in (bye to quit)"
  read INPUT_STRING
  echo "You typed: $INPUT_STRING"
done



