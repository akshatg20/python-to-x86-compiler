FILE="test6"  # No spaces around the equal sign for variable assignment

cd ../src/
make clean
make all
if [ -f x.txt ]; then
    rm x.txt
fi
# If you want to keep the following line as a comment, it's okay, otherwise remove the '#' to execute it
# ./cs335 --input ../testcases/simple1.py --3ac ../output/debug3ac/simple1.3ac --parse b.pdf >> x.txt
./cs335 --input ../testcases/${FILE}.py --3ac ../output/3ac/${FILE}.3ac --parse ../output/3ac/${FILE}.pdf --full
