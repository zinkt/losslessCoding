DEP=*.h

encode: encode.cpp $(DEP)
	g++ encode.cpp -std=c++11 -lc++ -o encode.out

decode: decode.cpp $(DEP)
	g++ decode.cpp -std=c++11 -lc++ -o decode.out

clean:
	rm -f *.out *.cps *.dcps