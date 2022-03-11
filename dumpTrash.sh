RANDOM=$$
for i in `seq 5`
do
	head -c 10 /dev/urandom > /tmp/trash/$RANDOM".trash"
done
