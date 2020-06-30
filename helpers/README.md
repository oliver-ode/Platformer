# Random cave/map generation algorithms

Listed below is a list of all of the different algorithms for random generation I have tried and their respective results

If you want to try them out run the `randomMap_X.py` file first and then run `mapToImage.py` to convert it into an easy to read image. Feel free to play around with the algorithms and constants.

## [Cellular automata](https://imgur.com/a/wui47qo)

This was the first attempt and with some tweaking to some of the constants it was able to get to a relatively good looking generation. The only problem was that since there is most likely not going to be block breaking and placing, there may be issues with getting stuck in rooms and some rooms that are entirely not accessible. 

## [Cellular automata w/ bias](https://imgur.com/a/jpEbAXI)

The idea behind this was that it may be possible to implement a bias to try and encourage generation of horizontal and diagonal caves. I gave it some trial and error and some of the generations that it makes look quite cool. The only problem is that I can't really call it "caves" as it is often very wide open. Also, with the implementation of a super basic rule for horizontal bias, there are some open air gaps that will never disappear. 

## [Simplex](https://imgur.com/a/PtKPrLp)

As I was writing this I thought this one was terrible as I was using x value to x value which meant that the noise generation would shift values so quickly that it was basically randomly filling up the map. I added a `RESOLUTION` variable which allows for closer x and y values (all it does is divide the input x value so the simplex noise function gets closer values together).