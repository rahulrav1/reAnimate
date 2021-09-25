# README

### Final Project Presentation
[](https://user-images.githubusercontent.com/70488221/134759165-07fb3727-3353-40ed-b26a-b63749915dc7.mp4)

### Data
    Default data is given in the Data/Dragon_Force directory.

    For importing and using your own data, you should be able to specify the location using the command line.
    In order to obtain the best results, keep your data small in terms of the number of images, or it will be quite slow, and keep the size of the largest image to a minimum for the same reason.
    It is also best that all images be approximatley the same size, and be inherently well interpolated, in the sense that having part of your data set vastly seprated from the rest will make it neccesarily difficult to find a good path between the disconnected parts. empty or duplicate images may also cause problems, so please remove them from the data set before use
### Usage
    You can specify via the command line the size of the Ball that determines whether 2 Nodes are Neighbors, as this will vary between data sets. 2 * the number of pixels in the average image is a good approximation, but higher is much safer than lower, lower can lead to undefined behavior

    you can then specify which image you would like to be animated to which other image based on their postion in the Directory

    It should output 2 gif files, whose names you specify (please do not include the .gif at the end), one which gives the algorithims solution, and one which gives a control version based on an MST to compare. The MST Filename should be appended with MST.
### Building and Running
    The code can be built by running the command make or make main, which will build the main output sytem, and make test for the tests. the executable for the main system is ./main, and for the tests is ./test
    you may needto run module load llvm/6.0.1 first on FASTX
### Tests
    Tests can be compiled and executed following instructions above. Tests for Matrix, Graph, and LLE classes are included in the /Tests directory. 
