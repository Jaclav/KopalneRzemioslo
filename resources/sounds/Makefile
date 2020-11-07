run:
	xxd -i button.ogg button.hpp
	xxd -i digging.ogg digging.hpp
	xxd -i gameTheme.ogg gameTheme.hpp
	xxd -i menuTheme.ogg menuTheme.hpp
	xxd -i putting.ogg putting.hpp

	sed -i 's/\<unsigned\>/unsigned const/' *.hpp
	astyle -p *.hpp
	rm *.orig
