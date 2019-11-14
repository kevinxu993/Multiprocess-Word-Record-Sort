# multiprocess-word-record-sort

🍴the word records based on frequency counts.

## Getting Started

### Prerequisites

* GCC
* Shell (Bash is recommended)

### Download source code and compile
The following instructions are presented using Bash in macOS:
```
# Change to HOME directory
$ cd ~

# Clone this repo and 'cd' into it
$ git clone https://github.com/kevinxu993/Multiprocess-Word-Record-Sort.git
$ cd Multiprocess-Word-Record-Sort/

# Let's compile.
$ make
gcc -Wall -g -std=gnu99  -c psort.c
gcc -Wall -g -std=gnu99  -c helper.c
gcc -Wall -g -std=gnu99  -o psort psort.o helper.o
gcc -Wall -g -std=gnu99  -c mkwords.c
gcc -Wall -g -std=gnu99  -o mkwords mkwords.o -lm
```

### Usage
```
Usage: psort -n <number of processes> -f <inputfile> -o <outputfile>
Usage: mkwords -f <input file name> -o <output file name>
```

## Merging process
![Merging process](https://user-images.githubusercontent.com/25379724/54893419-21be0500-4e8c-11e9-88f8-616302e608a1.png)

## Examples
```
$ ./psort -n 8 -f 8-words.b -o demo.b
[elephant] 889
[hippopotamus] 1537
[monkey] 2326
[cat] 7378
[mouse] 17670
[tarantula] 24218
[dog] 24983
[horse] 25611
$ xxd demo.b 
00000000: 7903 0000 656c 6570 6861 6e74 0000 7573  y...elephant..us
00000010: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000020: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
00000030: 0106 0000 6869 7070 6f70 6f74 616d 7573  ....hippopotamus
00000040: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000050: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
00000060: 1609 0000 6d6f 6e6b 6579 0000 0000 7573  ....monkey....us
00000070: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000080: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
00000090: d21c 0000 6361 7400 000c 4000 0000 0000  ....cat...@.....
000000a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000b0: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
000000c0: 0645 0000 6d6f 7573 6500 0000 0000 7573  .E..mouse.....us
000000d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000e0: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
000000f0: 9a5e 0000 7461 7261 6e74 756c 6100 0073  .^..tarantula..s
00000100: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000110: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
00000120: 9761 0000 646f 6700 0070 6f74 616d 7573  .a..dog..potamus
00000130: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000140: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
00000150: 0b64 0000 686f 7273 6500 0074 616d 7573  .d..horse..tamus
00000160: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000170: a00c 4000 0000 0000 0009 4000 0000 0000  ..@.......@.....
```

## Make new word binaries for testing
```
$ ./mkwords -f dictionary.txt -o dictionary-words.b
$ ls -l dictionary-words.b
-rw-r--r--  1 kevinxu993  staff  6102144 24 Mar 23:30 dictionary-words.b
$ xxd dictionary-words.b | head
00000000: 9f2d 0000 6161 0000 0000 0000 0000 0000  .-..aa..........
00000010: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000020: 0000 0000 0000 0000 700a 9fe1 fe7f 0000  ........p.......
00000030: 0d61 0000 6161 6800 0000 0000 0000 0000  .a..aah.........
00000040: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000050: 0000 0000 0000 0000 700a 9fe1 fe7f 0000  ........p.......
00000060: 3a3d 0000 6161 6865 6400 0000 0000 0000  :=..aahed.......
00000070: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000080: 0000 0000 0000 0000 700a 9fe1 fe7f 0000  ........p.......
00000090: e337 0000 6161 6869 6e67 0000 0000 0000  .7..aahing......
```

## Author(s)

| Name                    | GitHub                                     | Email
| ----------------------- | ------------------------------------------ | -------------------------
| Xinzheng (Kevin) Xu     | [kevinxu993](https://github.com/kevinxu993)| xuxinzheng24@gmail.com

## Thoughts and future improvements

* Since this is a rather simple beginner's project, no further improvements will be made.

## Contributing to this project

1. Fork it [![GitHub forks](https://img.shields.io/github/forks/kevinxu993/Multiprocess-Word-Record-Sort.svg?style=social&label=Fork&maxAge=2592000&)](https://github.com/kevinxu993/Multiprocess-Word-Record-Sort/fork)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -m 'Add some feature'`)
4. Push to your feature branch (`git push origin my-new-feature`)
5. Create a new Pull Request

Details are described [here](https://git-scm.com/book/en/v2/GitHub-Contributing-to-a-Project).

## Bug Reporting [![GitHub issues](https://img.shields.io/github/issues/kevinxu993/Multiprocess-Word-Record-Sort.svg?)](https://github.com/kevinxu993/Multiprocess-Word-Record-Sort/issues/)

Please click `issue` button above↑ to report any issues related to this project  
OR you can shoot an email to <xuxinzheng24@gmail.com>

## License
This project is released under GNU General Public License v3.0 - see [LICENSE](LICENSE) file for more details.
