run:
	xxd -i leaves1.png leaves1.hpp
	xxd -i leaves2.png leaves2.hpp

	sed -i 's/\<unsigned\>/unsigned const/' *.hpp
	astyle -p -z2 -n *.hpp
