run:
	rm *.hpp
	xxd -i BlueHighwayPixielated-G8Mm.ttf BlueHighwayPixielated-G8Mm.hpp
	xxd -i currentItem.png currentItem.hpp
	xxd -i cursor.png cursor.hpp
	xxd -i inventoryBar.png inventoryBar.hpp
	xxd -i playerX.png playerX.hpp

	sed -i 's/\<unsigned\>/unsigned const/' *.hpp
	astyle -p -z2 -n *.hpp
