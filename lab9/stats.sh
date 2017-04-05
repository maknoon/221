#!/bin/bash

for i in `seq $2 $3 $4`
do
	./avl $1 $i
done