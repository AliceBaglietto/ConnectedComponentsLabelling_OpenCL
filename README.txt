                    ##----------------CONNECTED COMPONENTS LABELLING------------------##
                    ##----------------------by Alice Baglietto------------------------##
                    ##---------------Bournemouth University, April 2018---------------##

This is my final year assignment for the Advanced Programming Unit. 
It is an implementation both serial and parallel of the Connected Components Labelling Algorithm.
CCL is used in computer vision to detect connected regions in binary digital images, where the background is usually black {0} 
and the foreground white {1}. The aim of the algorithm is to return a new image where the different connected surfaces in the 
foregrounds are assigned a unique colour. 
To do this the image pixel values are stored in an array of zeros and ones: the CCL algorithm can be split in two passes.

    #input array [10x10]
    0  0  0  0  0  0  0  0  0  0
    0  1  1  0  0  0  1  1  1  0
    0  1  1  0  0  1  1  1  1  0
    0  1  1  0  0  0  1  1  1  0
    0  0  0  0  0  0  0  0  0  0
    0  0  0  0  0  0  1  1  1  0
    0  1  1  1  1  1  1  1  1  0
    0  1  1  0  0  0  1  1  1  0
    0  1  1  0  0  0  0  0  0  0
    0  0  0  0  0  0  0  0  0  0

In the first one, the whole array is checked and the 1 valued elements are labeled with a new value 
(their numeric position in the array).

    #pass one
    0 0  0  0  0  0  0  0  0  0
    0 11 12 0  0  0  16 17 18 0
    0 21 22 0  0  25 26 27 28 0
    0 31 32 0  0  0  36 37 38 0
    0 0  0  0  0  0  0  0  0  0
    0 0  0  0  0  0  56 57 58 0
    0 61 62 63 64 65 66 67 68 0
    0 71 72 0  0  0  76 77 78 0
    0 81 82 0  0  0  0  0  0  0
    0 0  0  0  0  0  0  0  0  0

In the second one, the algorithm analyzes the neighbourhood of each element and re-assignes the current label 
with the smallest one in the neighbourhood.
The final result is a new array where the old groups of 1s are now different groups of same values. 

    #pass two
    0 0  0  0  0  0  0  0  0  0
    0 11 11 0  0  0  16 16 16 0
    0 11 11 0  0  16 16 16 16 0
    0 11 11 0  0  0  16 16 16 0
    0 0  0  0  0  0  0  0  0  0
    0 0  0  0  0  0  61 61 61 0
    0 61 61 61 61 61 61 61 61 0
    0 61 61 0  0  0  61 61 61 0
    0 61 61 0  0  0  0  0  0  0
    0 0  0  0  0  0  0  0  0  0

#Configuration details
It is written in c++ 11.
OpenCL 1.2 was used for the parallel implementation. 
QtImage and QtColor were used to deal with the images and gaphics. 

in cpu version rememeber to change ROW and COL definitions!



###-------------------SERIAL IMPLEMENTATION OF CCL------------------###

. First attempt at the implementation of the serial algorithm based on pseudocode found on:
    - [ https://en.wikipedia.org/wiki/Connected-component_labeling ]
        .two-pass serial version
    - [ http://hpcg.purdue.edu/bbenes/papers/Stava2011CCL.pdf ] ( CCL_chap35 )
        .first part also deals with the serial two-pass version
        .shows how the two-pass version of the ccl algorithm is what is ideal to paralellize later

. BUT it turned out to be too complex. 
    - I found a new analysis of the algorithm both serial and parallel at:
       [ http://ito-lab.naist.jp/~n-sibata/cclarticle/index.xhtml ]
        . This helped me chose to do it in OpenCL instead of CUDA
        . Very nice tutorial that made it easier to understand the steps needed.
        . Still needed to be ported from Java to C++ which was not very straight forward.
    - firstly implemented for arrays only. 
    - In second place, I worked on applying the algorithm to images.
        . I had some issues with QImage in the beginning, but they were easily solved.
        . I am happy with the choice of using QImage: it is pretty straightforeward 
          and worked nicely with the previous structure of the algorithm.
        . The official documentation for both of the classes was very useful and clear to understand:
            [ http://doc.qt.io/archives/qt-4.8/qcolor.html ]
            [ http://doc.qt.io/qt-5/qimage.html            ]

 
 
 ###-----------------PARALLEL IMPLEMENTATION OF CCL-------------------###

 . CUDA or OpenCL?
	- I found that OpenCL can be used to implement this algorithm in parallel. 
        . the tutorial found for the serial version, was very clear and helped me chose OpenCL over CUDA.
            [ http://ito-lab.naist.jp/~n-sibata/cclarticle/index.xhtml ]
	- Jon Macey also suggested in a lecture to use OpenCL because for some aspects is more straight foreward than CUDA.
	- I could still look at the same website that helped with the serial implementation
		. Nice discussion about different versions of the algorithm aimed to make it faster.
        . Implemented those as well: helped in the analysis of not only the time differece between serial and parallel code, 
        but also demonstrate that kernels can also be very differents.
	- Downside: OpenCL doesn not support 2D arrays as an input!
		. Took a while to master how to deal with the original array that needs to be converted to a 1D array in the kernel
		. Sort all operations with manipulation of extremes of the array ( [ROW] [COL] )
		. Not ideal when dealing with 2D arrays storing the pixel values of an image. 
    - I still found OpenCl more similar to c++, so more straighforeward to be implemented. 
        . There is a good amount of official documentation online that helped too. 

            ###--------------------TIME ANALYSIS-----------------------------###

##--------SERIAL VS PARALLEL---------##
Given different sized images as an input, I run some time tests to analyse and compare 
the elapsed timings of the serial and parallel version of the code.

The images used were: 
    "test10.png"   [ 10x10   pixels ]
    "test.png"     [ 160x160 pixels ]   
    "circles.png"  [ 500x500 pixels ]




##--------NAIVE, SLOW AND FAST KERNELS COMPARISON-------##
Given different sized images as an input, I run some time tests to analyse and compare 
the elapsed timings of different parallel versions of the kernels ( naive, slow and fast )

The images used were: 
    "test10.png"   [ 10x10   pixels ]
    "test.png"     [ 160x160 pixels ]   
    "circles.png"  [ 500x500 pixels ]
 
