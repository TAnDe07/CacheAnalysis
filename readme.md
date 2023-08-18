# Cache Simulation

This cache simulation calculates hit ratio for Direct Mapped, Fully Associative, and Set Associative Caches. It uses FIFO and LRU replacement policy to calculate hit ratio for Fully Associative, and Set Associative


## Compilation
- To compile the code you will need a trace file with 32 bits hex addresses
- Run the code in the environment of choice
## Running
- The program will prompt you to enter the file name that you want to read
- Enter the name of the file with the extension

  ![](../OneDrive/Pictures/fileName answer.png)
- Next, you will enter the number of bytes in the cache

  ![](../OneDrive/Pictures/bytes in cache.png)
- After, you will be prompted to enter the number of bytes in a line/block

  ![](../OneDrive/Pictures/bytes in blocks.png)
- Next, there will be a menu to select which type of cache you would like to use

  ![](../OneDrive/Pictures/menu for cache.png)
## Direct Mapped Cache
- If direct mapped cache is chosen the program will read the file and create a direct mapped cache
- Once the file has been added to the cache, the program will output the number of hits, misses, total addresses read, and the hit ratio

  ![](../OneDrive/Pictures/DM cache.png)
## Fully Associative Cache
- If fully associative cache is chosen the program will prompt the user to select which replacement policy they would like to use

  ![](../OneDrive/Pictures/FA cache.png)
- Once a replacement policy is chosen, the program will output the cache and replacement policy chosen. Then the program will read the file. Once the file has been added to the cache, the program will output the number of hits, misses, total addresses read, and the hit ratio

  ![](../OneDrive/Pictures/FA RESULTS2.png)
## Set Associative Cache
- If set associative cache is chosen the program will prompt the user to enter the associativity
  select which replacement policy they would like to use

  ![](../OneDrive/Pictures/n value.png)
- Once the associativity is chosen, the program will ask the user to select which replacement policy they would like to use

  ![](../OneDrive/Pictures/FA cache.png)
- Once the replacement policy is entered, the program will output the cache and replacement policy chosen. Then the program will read the file. Once the file has been added to the cache, the program will output the number of hits, misses, total addresses read, and the hit ratio

  ![](../OneDrive/Pictures/set lru.png)