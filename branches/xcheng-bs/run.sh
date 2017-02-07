#!/bin/sh

# this script runs some jobs concurrently

MATLAB="matlab -nodisplay"

echo "main('obj_ackley', 50, 20, 10, 100);" | $MATLAB &
echo "main('obj_ackley', 200, 20, 10, 300);" | $MATLAB &
echo "main('obj_ackley', 200, 40, 10, 300);" | $MATLAB &
echo "main('obj_ackley', 200, 40, 20, 300);" | $MATLAB &
echo "main('obj_ackley', 200, 40, 30, 300);" | $MATLAB &
echo "main('obj_griewank', 200, 40, 20, 300);" | $MATLAB &
echo "main('obj_rastrigrin', 200, 40, 20, 300);" | $MATLAB &
echo "main('obj_rosenbrock', 200, 40, 20, 300);" | $MATLAB &

