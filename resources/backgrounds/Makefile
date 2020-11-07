run:
	xxd -i dirtBackground.png dirtBackground.hpp
	xxd -i mntBackground.png mntBackground.hpp
	xxd -i startBackground.png startBackground.hpp

	sed -i 's/\<unsigned\>/unsigned const/' *.hpp
	astyle -p *.hpp
	rm *.orig
