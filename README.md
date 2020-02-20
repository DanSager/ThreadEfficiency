<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Algorithms](#usage)
* [Usage](#usage)
  * [Required Arguments](#prerequisites)
  * [Optional Arguments](#installation)
* [Roadmap](#roadmap)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)

<!-- * [Built With](#built-with) -->
<!-- * [Contributing](#contributing) -->

<!-- ABOUT THE PROJECT -->
## About The Project

<!--[![Product Name Screen Shot][product-screenshot]](https://example.com) -->

The project found in this repository is a self motivated endever to better understand algorithms and multithreading using 
C++ on a linux operating system. To do this, a wide variety of algorithms have been implemented and will be implemented in 
the future so that automated testing can observe the difference that different algorithms can make and their expandability.
The coins algorithm featured for example runs in O(n) time and that is very evident as when the sample size increased 10 fold
the total execution time increases in the sample manner. However, a devide and conquer algorithm such as merge sort, will
increase in runtime disproportionately to it's sample size because it's time complexity is O(nlogn) time.This project is 
used to observe those differences.

In addition, this project is used as a testing grounds to determine the effect of using a thread pool in a variety of 
different algorithms and sample sizes.

<!-- ### Built With
*** To begin, this project requires a Linux based operating system as there are implementations of Linux libraries.
*** All code has been developed and tested on Ubuntu 18.04.
*** * [G++](https://gcc.gnu.org/) 
-->


<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.


### Prerequisites

To begin, this project requires a Linux based operating system as there are implementations of Linux libraries.
All code has been developed and tested on Ubuntu 18.04.

### Installation

1. Clone the repo
```sh
git clone https://github.com/DanSager/ThreadEfficiency.git
```
2. Install GCC
```sh
sudo apt install g++
```
3. Build the project
```sh
make
```
4. Execution (See Usage for argument usage protocol.)
```sh
./ThreadEfficiency
```

## Algorithms

In order to get an understanding of a variety of different algorithm types, the algorithm's included is a key point 
of interest in this project.

### Twelve Coins

Based on the Twelve Coin in which there exist twelve coins, eleven or twelve of which are identical. The only way to 
determine if a coin is different from the rest is using a balance to see if it is lighter or heavier than the others.
The balance may only be used three times to determine if there is a unique coin and if there is, to isolate it and determine 
it's position and weight relative to the others.

The algorithm has a time complexity of O(n) and that is evident in it's execution times as the sample increases.

Single-threading remains more efficient for this algorithm as it is so simple that it is not worth the time setting 
up the threads necessary.

Further information can be found at https://en.wikipedia.org/wiki/Balance_puzzle#Twelve-coin_problem.

### Merge Sort

"Merge sort is a divide-and-conquer algorithm based on the idea of breaking down a list into several sub-lists until each 
sublist consists of a single element and merging those sublists in a manner that results into a sorted list." 
(hackerearth.com).

Merge sort has a time complexity of O(nlogn) which results in a point where the sample size becomes large enough that 
single-threading becomes less efficient than multi-threading.

Further information can be found at https://www.hackerearth.com/practice/algorithms/sorting/merge-sort/tutorial/.

### Multi-Threaded Merge Sort

Similar to regular merge sort, however, the work-load is broken down and distributed to worker threads so that concurrent 
sorting can occur.

<!-- USAGE EXAMPLES -->
## Usage

This project can be executed in a variety of different ways using command-line arguments to specify the desired settings

<!-- REQUIRED ARGUMENTS -->
### Required Arguments

These arguments must be specified at execution otherwise the program will return.

#### Algorithm

In order to specify the algorithm the user wants the program to execute, the algorithm argument must be specified.

User's can specify their desired algorithm by typing '-algo' followed by a space and the algorithm they would like to use.

Algorithms include 'coins', 'merge', and 'mergeMulti'. The following shows an example of execution using the coins algorithm.

```sh
./ThreadEfficiency -algo coins
```

#### Count

In order for the program to know the number of times the user would like the given algorithm to execute, the user 
must specify the count argument.

Count can be any integer value (within reason), and shown below is telling the program to execute the algorithm 1000 times.

```sh
./ThreadEfficiency -count 1000
```

<!-- OPTIONAL ARGUMENTS -->
### Optional Arguments

These arguments are optional as successful execution of the program can exist without specifying these arguments.

#### Threads

Since this program is focused around multithreading, the command-line arguments allows the user to specify
the number of threads they would like the program to use.

This can be any number 1 to 12 (1 being default) and below is an example to execute using 8 threads.

```sh
./ThreadEfficiency -threads 8
```

#### Thread Pool

For certain algorithms in this program, a thread pool can be used to further multithreading's increased efficiency
when a large number of threads are being used.

By default, using a thread pool is disabled but can be enabled with the following command-line argument.

```sh
./ThreadEfficiency -threadpool
```

#### Generate

In certain scenarios, using the same input test after test is preferable. However, other times, using a new randomly 
generated input can prove preferable and therefore, the command-line argument generate earned it's rightful place.

By default, new input's are not generated with each execution of the algorithm however, that can be swapped by using the 
following argument.

```sh
./ThreadEfficiency -generate
```

### All Put Together

The following demonstrates executing the program running the coins algorithm, on 100000 different inputs, using 8 
threads in a threadpool and with a newly generated input sample.

```sh
./ThreadEfficiency -algo coins -count 100000 -threads 8 -threadpool -generate
```

<!-- ROADMAP -->
## Roadmap

Future versions will hopefully include additional algorithms and optimizations.
In addition, a python automating script to run the rests with a variety of different arguments.
This is to allow for a higher level of analysis to better understand the effects of multithreading and utilizing a threadpool.


<!-- CONTRIBUTING -->
<!-- ## Contributing
<!--
Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.
<!--
1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request -->



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Dan Sager - [LinkedIn](https://www.linkedin.com/in/daniel-sager/) - sagerdanw@gmail.com

Project Link: [https://github.com/DanSager/ThreadEfficiency](https://github.com/DanSager/ThreadEfficiency)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [C++11 ThreadPool](https://github.com/mtrebi/thread-pool)
* [C++11 Vector Merge Sort](https://www.bogotobogo.com/Algorithms/mergesort.php)
* [Twelve Coin Problem](https://en.wikipedia.org/wiki/Balance_puzzle#Twelve-coin_problem)
* [Merge Sort Info](https://www.hackerearth.com/practice/algorithms/sorting/merge-sort/tutorial/)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=flat-square
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=flat-square
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=flat-square
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=flat-square
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=flat-square
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
