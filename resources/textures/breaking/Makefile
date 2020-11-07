run:
	xxd -i breaking1.png breaking1.hpp
	xxd -i breaking2.png breaking2.hpp
	xxd -i breaking3.png breaking3.hpp
	xxd -i breaking4.png breaking4.hpp
	xxd -i breaking5.png breaking5.hpp
	xxd -i breaking6.png breaking6.hpp

	sed -i 's/\<unsigned\>/unsigned const/' *.hpp
	astyle -p *.hpp
	rm *.orig
