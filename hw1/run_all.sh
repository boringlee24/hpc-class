#!/bin/bash

# echo "start factorial"
# for i in {1..10}
# do
#     echo "running ${i}th time"
#     ./compiled/factorial.out &&
# done

# echo "start product"
# for i in {1..10}
# do
#     echo "running ${i}th time"
#     ./compiled/product.out &&
# done

# echo "start fibonacci"
# for i in {1..10}
# do
#     echo "running ${i}th time"
#     ./compiled/fibonacci.out &&
# done
# for i in {1..10}
# do
#     echo "running ${i}th time"
#     ./compiled/factorial.out
# done
# for i in {1..10}
# do
#     echo "running ${i}th time"
#     ./compiled/product.out
# done
for i in {1..10}
do
    echo "running ${i}th time"
    ./compiled/fibonacci.out
done
echo "finished"