run:
	xxd -i bedrock.png bedrock.hpp
	xxd -i dirt.png dirt.hpp
	xxd -i grass.png grass.hpp
	xxd -i grassDirt.png grassDirt.hpp
	xxd -i ledder.png ledder.hpp
	xxd -i notFound.png notFound.hpp
	xxd -i plank.png plank.hpp
	xxd -i stone.png stone.hpp
	xxd -i wood.png wood.hpp

	sed -i 's/\<unsigned\>/unsigned const/' *.hpp
	astyle -p -z2 -n *.hpp
